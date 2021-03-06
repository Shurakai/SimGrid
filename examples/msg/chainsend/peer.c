#include "peer.h"

XBT_LOG_NEW_DEFAULT_CATEGORY(msg_peer,
                             "Messages specific for the peer");

/*******************************************************
 *                     Peer                            *
 *******************************************************/

void peer_init_chain(peer_t peer, message_t msg)
{
  peer->prev = msg->prev_hostname;
  peer->next = msg->next_hostname;
  peer->init = 1;
}

static void peer_forward_msg(peer_t peer, message_t msg)
{
  msg_task_t task = task_message_data_new(peer->me, peer->next, NULL, 0);
  msg_comm_t comm = NULL;
  XBT_DEBUG("Sending (isend) from %s into mailbox %s", peer->me, peer->next);
  comm = MSG_task_isend(task, peer->next);
  queue_pending_connection(comm, peer->pending_sends);
}

int peer_execute_task(peer_t peer, msg_task_t task)
{
  int done = 0;
  message_t msg = MSG_task_get_data(task);
  
  XBT_DEBUG("Peer %s got message of type %d\n", peer->me, msg->type);
  switch (msg->type) {
    case MESSAGE_BUILD_CHAIN:
      peer_init_chain(peer, msg);
      break;
    case MESSAGE_SEND_DATA:
      xbt_assert(peer->init, "peer_execute_task() failed: got msg_type %d before initialization", msg->type);
      if (peer->next != NULL)
        peer_forward_msg(peer, msg);
      peer->pieces++;
      break;
    case MESSAGE_END_DATA:
      xbt_assert(peer->init, "peer_execute_task() failed: got msg_type %d before initialization", msg->type);
      done = 1;
      XBT_DEBUG("%d pieces receieved", peer->pieces);
      break;
  }

  MSG_task_execute(task);

  return done;
}

msg_error_t peer_wait_for_message(peer_t peer)
{
  msg_error_t status;
  msg_comm_t comm = NULL;
  msg_task_t task = NULL;
  int done = 0;

  while (!done) {
    if (comm == NULL) // FIXME I should have a recv queue
      comm = MSG_task_irecv(&task, peer->me);

    if (MSG_comm_test(comm)) {
      status = MSG_comm_get_status(comm);
      XBT_DEBUG("peer_wait_for_message: error code = %d", status);
      xbt_assert(status == MSG_OK, "peer_wait_for_message() failed");
      MSG_comm_destroy(comm);
      comm = NULL;
      done = peer_execute_task(peer, task);
      task_message_delete(task);
      task = NULL;
    } else {
      process_pending_connections(peer->pending_sends);
      MSG_process_sleep(0.01);
    }
  }

  return status;
}

void peer_init(peer_t p, int argc, char *argv[])
{
  p->init = 0;
  p->prev = NULL;
  p->next = NULL;
  p->pieces = 0;
  p->close_asap = 0;
  p->pending_sends = xbt_dynar_new(sizeof(msg_comm_t), NULL);
  p->me = xbt_new(char, HOSTNAME_LENGTH);
  /* Set mailbox name: use host number from argv or hostname if no argument given */
  if (argc > 1) {
    snprintf(p->me, HOSTNAME_LENGTH, "host%s", argv[1]);
  } else {
    strncpy(p->me, MSG_host_get_name(MSG_host_self()), HOSTNAME_LENGTH);
  }
}

void peer_shutdown(peer_t p)
{
  float start_time = MSG_get_clock();
  float end_time = start_time + PEER_SHUTDOWN_DEADLINE;

  XBT_INFO("Waiting for sends to finish before shutdown...");
  while (xbt_dynar_length(p->pending_sends) && MSG_get_clock() < end_time) {
    process_pending_connections(p->pending_sends);
    MSG_process_sleep(1);
  }

  xbt_assert(xbt_dynar_length(p->pending_sends) == 0, "Shutdown failed, sends still pending after deadline");
  xbt_dynar_free(&p->pending_sends);
  xbt_free(p->me);

  xbt_free(p);
}

/** Peer function  */
int peer(int argc, char *argv[])
{
  peer_t p = xbt_new(s_peer_t, 1);
  msg_error_t status;

  XBT_INFO("peer");

  peer_init(p, argc, argv);
  status = peer_wait_for_message(p);
  peer_shutdown(p);

  return status;
}                               /* end_of_receiver */


