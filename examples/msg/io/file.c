/* Copyright (c) 2008, 2009, 2010. The SimGrid Team.
 * All rights reserved.                                                     */

/* This program is free software; you can redistribute it and/or modify it
 * under the terms of the license (GNU LGPL) which comes with this package. */

/** @addtogroup MSG_examples
 * 
 * @subsection MSG_ex_resources Other resource kinds
 * 
 * This section contains some sparse examples of how to use the other
 * kind of resources, such as disk or GPU. These resources are quite
 * experimental for now, but here we go anyway.
 * 
 * - <b>io/file.c</b> Example with the disk resource
 */

#define FILENAME "/home/user/Install/simgrid/doc/simgrid/examples/cxx/basic/basic_platform.xml"

#include <stdio.h>
#include <stdlib.h>
#include "msg/msg.h"
#include "surf/surf_private.h"

int host(int argc, char *argv[]);

XBT_LOG_NEW_DEFAULT_CATEGORY(io_file,
                             "Messages specific for this io example");

int host(int argc, char *argv[])
{
  m_file_t file;
  char* mount = bprintf("C:");

  file = MSG_file_open(mount,FILENAME,"rw");
  XBT_INFO("Host '%s' open %p",MSG_host_get_name(MSG_host_self()), file);

  size_t read = MSG_file_read(mount,NULL,0,0,file);
  XBT_INFO("Host '%s' read %zu", MSG_host_get_name(MSG_host_self()), read);

  size_t write = MSG_file_write(mount,NULL,0,0,file);
  XBT_INFO("Host '%s' write %zu", MSG_host_get_name(MSG_host_self()), write);

  int res = MSG_file_stat(mount,0,NULL);
  XBT_INFO("Host '%s' stat %d",MSG_host_get_name(MSG_host_self()), res);

  res = MSG_file_close(mount,file);
  XBT_INFO("Host '%s' close %d",MSG_host_get_name(MSG_host_self()), res);

  free(mount);
  return 0;
}

int main(int argc, char **argv)
{
    int i,res;
  MSG_global_init(&argc, argv);
  MSG_create_environment(argv[1]);
  xbt_dynar_t hosts =  MSG_hosts_as_dynar();
  MSG_function_register("host", host);

  XBT_INFO("Number of host '%lu'",xbt_dynar_length(hosts));
  for(i = 0 ; i<xbt_dynar_length(hosts); i++)
  {
    char* name_host = bprintf("%d",i);
    MSG_process_create( name_host, host, NULL, xbt_dynar_get_as(hosts,i,m_host_t) );
    free(name_host);
  }
  xbt_dynar_free(&hosts);

  res = MSG_main();
  XBT_INFO("Simulation time %g", MSG_get_clock());
  MSG_clean();
  if (res == MSG_OK)
    return 0;
  else
    return 1;

}