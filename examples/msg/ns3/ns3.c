/* Copyright (c) 2007, 2008, 2009, 2010. The SimGrid Team.
 * All rights reserved.                                                     */

/* This program is free software; you can redistribute it and/or modify it
 * under the terms of the license (GNU LGPL) which comes with this package. */

#include <stdio.h>
#include <stdlib.h>
#include "msg/msg.h"
#include "xbt/log.h"
#include "xbt/asserts.h"

XBT_LOG_NEW_DEFAULT_CATEGORY(msg_test,
                             "Messages specific for this msg example");

int master(int argc, char *argv[]);
int slave(int argc, char *argv[]);
int timer(int argc, char *argv[]);
MSG_error_t test_all(const char *platform_file,
                     const char *application_file);

int timer_start = 1;

typedef enum {
  PORT_22 = 0,
  MAX_CHANNEL
} channel_t;

//keep a pointer to all surf running tasks.
#define NTASKS 1500
int bool_printed = 0;
double start_time, end_time, elapsed_time;
double gl_data_size[NTASKS];
m_task_t gl_task_array[NTASKS];
const char *slavenames[NTASKS];
const char *masternames[NTASKS];
int gl_task_array_id = 0;
int count_finished = 0;

#define FINALIZE ((void*)221297)        /* a magic number to tell people to stop working */

/** master */
int master(int argc, char *argv[])
{
  char *slavename = NULL;
  double task_comm_size = 0;
  m_task_t todo;
  char id_alias[10];
  //unique id to control statistics
  int id = -1;

  if (argc != 4) {
    XBT_INFO("Strange number of arguments expected 3 got %d", argc - 1);
  }

  /* data size */
  int read;
  read = sscanf(argv[1], "%lg", &task_comm_size);
  xbt_assert(read, "Invalid argument %s\n", argv[1]);

  /* slave name */
  slavename = argv[2];
  id = atoi(argv[3]);
  sprintf(id_alias, "flow_%d", id);
  slavenames[id] = slavename;
  TRACE_category(id_alias);

  masternames[id] = MSG_host_get_name(MSG_host_self());

  {                             /*  Task creation.  */
    char sprintf_buffer[64] = "Task_0";
    todo = MSG_task_create(sprintf_buffer, 100*task_comm_size, task_comm_size, NULL);
    TRACE_msg_set_task_category(todo, id_alias);
    //keep track of running tasks
    gl_task_array[id] = todo;
    gl_data_size[id] = task_comm_size;
  }

  {                             /* Process organisation */
    MSG_get_host_by_name(slavename);
  }

  count_finished++;

  /* time measurement */
  sprintf(id_alias, "%d", id);
  start_time = MSG_get_clock();
  //MSG_task_execute(todo);
  MSG_task_send(todo, id_alias);
  end_time = MSG_get_clock();


  return 0;
}                               /* end_of_master */


/** Timer function  */
int timer(int argc, char *argv[])
{
  int sleep_time;
  int first_sleep;

  if (argc != 3) {
    XBT_INFO("Strange number of arguments expected 2 got %d", argc - 1);
  }

  sscanf(argv[1], "%d", &first_sleep);
  sscanf(argv[2], "%d", &sleep_time);

  if(first_sleep){
      MSG_process_sleep(first_sleep);
  }

  while(timer_start){
      MSG_process_sleep(sleep_time);
  }

  return 0;
}

/** Receiver function  */
int slave(int argc, char *argv[])
{

  m_task_t task = NULL;
  int a = MSG_OK;
  int id = 0;
  char id_alias[10];

  if (argc != 2) {
    XBT_INFO("Strange number of arguments expected 1 got %d", argc - 1);
  }

  id = atoi(argv[1]);
  sprintf(id_alias, "%d", id);

  a = MSG_task_receive(&(task), id_alias);

  count_finished--;
  if(count_finished == 0){
      timer_start = 0;
  }



  if (a != MSG_OK) {
    XBT_INFO("Hey?! What's up?");
    xbt_die("Unexpected behavior.");
  }

  elapsed_time = MSG_get_clock() - start_time;
  
  XBT_INFO("FLOW[%d] : Receive %.0f bytes from %s to %s",
		  id,
		  MSG_task_get_data_size(task),
       masternames[id],
       slavenames[id]);

  MSG_task_destroy(task);

  return 0;
}                               /* end_of_slave */

/** Test function */
MSG_error_t test_all(const char *platform_file,
                     const char *application_file)
{
  MSG_error_t res = MSG_OK;

  /* MSG_config("workstation/model", "GTNETS"); */
  /* MSG_config("workstation/model","KCCFLN05"); */
  {                             /*  Simulation setting */
    MSG_set_channel_number(MAX_CHANNEL);
    MSG_create_environment(platform_file);
  }

  TRACE_declare_mark("endmark");

  {                             /*   Application deployment */
    MSG_function_register("master", master);
    MSG_function_register("slave", slave);
    MSG_function_register("timer", timer);

    MSG_launch_application(application_file);
  }
  res = MSG_main();
  return res;
}                               /* end_of_test_all */

/** Main function */
int main(int argc, char *argv[])
{
  MSG_error_t res = MSG_OK;
  bool_printed = 0;

  MSG_global_init(&argc, argv);
  if (argc < 3) {
    printf("Usage: %s platform_file deployment_file\n", argv[0]);
    exit(1);
  }

  res = test_all(argv[1], argv[2]);

  MSG_clean();

  if (res == MSG_OK)
    return 0;
  else
    return 1;
}                               /* end_of_main */