/* Copyright (c) 2012. The SimGrid Team.
 * All rights reserved.                                                     */

/* This program is free software; you can redistribute it and/or modify it
 * under the terms of the license (GNU LGPL) which comes with this package. */

#include <msg/msg.h>
#include <simgrid/modelchecker.h>
#include "mc/mc.h"

XBT_LOG_NEW_DEFAULT_CATEGORY(snapshot_comparison_liveness2, "Debug information for snasphot comparison liveness2 test example");

int test(int argc, char **argv);

int test(int argc, char **argv){

  MSG_process_sleep(1);

  XBT_INFO("**** Start test ****");
  XBT_INFO("Malloc after first snapshot");

  void *snap1 = MC_snapshot();

  MSG_process_sleep(1);

  XBT_INFO("First snapshot");

  char *toto = xbt_malloc(5);
  XBT_INFO("Toto allocated");

  void *snap2 = MC_snapshot();

  MSG_process_sleep(1);

  XBT_INFO("Second snapshot");

  XBT_INFO("Test result : %d (0 = state equality, 1 = different states)", MC_compare_snapshots(snap1, snap2));
  
  XBT_INFO("**** End test ****");

  xbt_free(toto);

  return 0;
}

int main(int argc, char **argv){
  MSG_init(&argc, argv);

  MSG_config("model-check/property","promela");

  MSG_create_environment("snapshot_comparison_platform.xml");

  MSG_function_register("test", test);

  MSG_launch_application("deploy_snapshot_comparison.xml");

  MSG_main();

  return 0;
}