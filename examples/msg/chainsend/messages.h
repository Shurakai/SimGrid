#ifndef KADEPLOY_MESSAGES_H
#define KADEPLOY_MESSAGES_H

#include "msg/msg.h"
#include "xbt/sysdep.h"

#define MESSAGE_SIZE 1

/* Messages enum */
typedef enum {
  MESSAGE_BUILD_CHAIN = 0,
  MESSAGE_SEND_DATA,
  MESSAGE_END_DATA
} e_message_type;

/* Message struct */
typedef struct s_message {
  e_message_type type;
  const char *issuer_hostname;
  const char *mailbox;
  const char *prev_hostname;
  const char *next_hostname;
  const char *data_block;
  unsigned int data_length;
} s_message_t, *message_t;

/* Message methods */
msg_task_t task_message_new(e_message_type type, const char *issuer_hostname, const char *mailbox);
msg_task_t task_message_chain_new(const char *issuer_hostname, const char *mailbox, const char* prev, const char *next);
msg_task_t task_message_data_new(const char *issuer_hostname, const char *mailbox, const char *block, unsigned int len);
msg_task_t task_message_end_data_new(const char *issuer_hostname, const char *mailbox);
void task_message_delete(void *);

#endif /* KADEPLOY_MESSAGES_H */