/* Copyright (c) 2004, 2005, 2006, 2007, 2008, 2009, 2010. The SimGrid Team.
 * All rights reserved.                                                     */

/* This program is free software; you can redistribute it and/or modify it
 * under the terms of the license (GNU LGPL) which comes with this package. */

#include "xbt/ex.h"
#include "xbt/dict.h"
#include "portable.h"
#include "surf_private.h"
#include "storage_private.h"
#include "surf/surf_resource.h"

typedef struct workstation_CLM03 {
  s_surf_resource_t generic_resource;   /* Must remain first to add this to a trace */
  void *cpu;
  void *net_elm;
  xbt_dynar_t storage;
} s_workstation_CLM03_t, *workstation_CLM03_t;

XBT_LOG_NEW_DEFAULT_SUBCATEGORY(surf_workstation, surf,
                                "Logging specific to the SURF workstation module");

surf_model_t surf_workstation_model = NULL;

static void workstation_new(sg_platf_host_cbarg_t host)
{
  workstation_CLM03_t workstation = xbt_new0(s_workstation_CLM03_t, 1);

  workstation->generic_resource.model = surf_workstation_model;
  workstation->generic_resource.name = xbt_strdup(host->id);
  workstation->cpu = xbt_lib_get_or_null(host_lib, host->id, SURF_CPU_LEVEL);
  workstation->storage = xbt_lib_get_or_null(storage_lib,host->id,ROUTING_STORAGE_HOST_LEVEL);
  workstation->net_elm = xbt_lib_get_or_null(host_lib,host->id,ROUTING_HOST_LEVEL);
  XBT_DEBUG("Create workstation %s with %ld mounted disks",host->id,xbt_dynar_length(workstation->storage));
  xbt_lib_set(host_lib, host->id, SURF_WKS_LEVEL, workstation);
}

static int ws_resource_used(void *resource_id)
{
  THROW_IMPOSSIBLE;             /* This model does not implement parallel tasks */
  return -1;
}

static void ws_parallel_action_cancel(surf_action_t action)
{
  THROW_UNIMPLEMENTED;          /* This model does not implement parallel tasks */
}

static int ws_parallel_action_free(surf_action_t action)
{
  THROW_UNIMPLEMENTED;          /* This model does not implement parallel tasks */
  return -1;
}

static int ws_action_unref(surf_action_t action)
{
  if (action->model_type == surf_network_model)
    return surf_network_model->action_unref(action);
  else if (action->model_type == surf_cpu_model)
    return surf_cpu_model->action_unref(action);
  else if (action->model_type == surf_workstation_model)
    return ws_parallel_action_free(action);
  else
    DIE_IMPOSSIBLE;
  return 0;
}

static void ws_action_cancel(surf_action_t action)
{
  if (action->model_type == surf_network_model)
    surf_network_model->action_cancel(action);
  else if (action->model_type == surf_cpu_model)
    surf_cpu_model->action_cancel(action);
  else if (action->model_type == surf_workstation_model)
    ws_parallel_action_cancel(action);
  else
    DIE_IMPOSSIBLE;
  return;
}

static void ws_action_state_set(surf_action_t action,
                                e_surf_action_state_t state)
{
  if (action->model_type == surf_network_model)
    surf_network_model->action_state_set(action, state);
  else if (action->model_type == surf_cpu_model)
    surf_cpu_model->action_state_set(action, state);
  else if (action->model_type == surf_workstation_model)
    surf_action_state_set(action, state);
  else
    DIE_IMPOSSIBLE;
  return;
}

static double ws_share_resources(double now)
{
  return -1.0;
}

static void ws_update_actions_state(double now, double delta)
{
  return;
}

static void ws_update_resource_state(void *id,
                                     tmgr_trace_event_t event_type,
                                     double value, double date)
{
  THROW_IMPOSSIBLE;             /* This model does not implement parallel tasks */
}

static surf_action_t ws_execute(void *workstation, double size)
{
  void *cpu = ((workstation_CLM03_t) workstation)->cpu;
  return ((surf_resource_t) cpu)->model->extension.cpu.execute(cpu, size);
}

static surf_action_t ws_action_sleep(void *workstation, double duration)
{
  return surf_cpu_model->extension.cpu.
      sleep(((workstation_CLM03_t) workstation)->cpu, duration);
}

static void ws_action_suspend(surf_action_t action)
{
  if (action->model_type == surf_network_model)
    surf_network_model->suspend(action);
  else if (action->model_type == surf_cpu_model)
    surf_cpu_model->suspend(action);
  else
    DIE_IMPOSSIBLE;
}

static void ws_action_resume(surf_action_t action)
{
  if (action->model_type == surf_network_model)
    surf_network_model->resume(action);
  else if (action->model_type == surf_cpu_model)
    surf_cpu_model->resume(action);
  else
    DIE_IMPOSSIBLE;
}

static int ws_action_is_suspended(surf_action_t action)
{
  if (action->model_type == surf_network_model)
    return surf_network_model->is_suspended(action);
  if (action->model_type == surf_cpu_model)
    return surf_cpu_model->is_suspended(action);
  DIE_IMPOSSIBLE;
  return -1;
}

static void ws_action_set_max_duration(surf_action_t action,
                                       double duration)
{
  if (action->model_type == surf_network_model)
    surf_network_model->set_max_duration(action, duration);
  else if (action->model_type == surf_cpu_model)
    surf_cpu_model->set_max_duration(action, duration);
  else
    DIE_IMPOSSIBLE;
}

static void ws_action_set_priority(surf_action_t action, double priority)
{
  if (action->model_type == surf_network_model)
    surf_network_model->set_priority(action, priority);
  else if (action->model_type == surf_cpu_model)
    surf_cpu_model->set_priority(action, priority);
  else
    DIE_IMPOSSIBLE;
}

#ifdef HAVE_TRACING
static void ws_action_set_category(surf_action_t action, const char *category)
{
  if (action->model_type == surf_network_model)
    surf_network_model->set_category(action, category);
  else if (action->model_type == surf_cpu_model)
    surf_cpu_model->set_category(action, category);
  else
    DIE_IMPOSSIBLE;
}
#endif

#ifdef HAVE_LATENCY_BOUND_TRACKING
static int ws_get_latency_limited(surf_action_t action)
{
  if (action->model_type == surf_network_model)
    return surf_network_model->get_latency_limited(action);
  else
    return 0;
}
#endif

static double ws_action_get_remains(surf_action_t action)
{
  if (action->model_type == surf_network_model)
    return surf_network_model->get_remains(action);
  if (action->model_type == surf_cpu_model)
    return surf_cpu_model->get_remains(action);
  DIE_IMPOSSIBLE;
  return -1.0;
}

static surf_action_t ws_communicate(void *workstation_src,
                                    void *workstation_dst, double size,
                                    double rate)
{
  workstation_CLM03_t src = (workstation_CLM03_t) workstation_src;
  workstation_CLM03_t dst = (workstation_CLM03_t) workstation_dst;
  return surf_network_model->extension.network.
      communicate(src->net_elm,
                  dst->net_elm, size, rate);
}

static e_surf_resource_state_t ws_get_state(void *workstation)
{
  return surf_cpu_model->extension.cpu.
      get_state(((workstation_CLM03_t) workstation)->cpu);
}

static double ws_get_speed(void *workstation, double load)
{
  return surf_cpu_model->extension.cpu.
      get_speed(((workstation_CLM03_t) workstation)->cpu, load);
}

static double ws_get_available_speed(void *workstation)
{
  return surf_cpu_model->extension.cpu.
      get_available_speed(((workstation_CLM03_t)
                           workstation)->cpu);
}

static surf_action_t ws_execute_parallel_task(int workstation_nb,
                                              void **workstation_list,
                                              double *computation_amount,
                                              double *communication_amount,
                                              double rate)
{
  THROW_UNIMPLEMENTED;          /* This model does not implement parallel tasks */
  return NULL;
}


/* returns an array of network_link_CM02_t */
static xbt_dynar_t ws_get_route(void *workstation_src, void *workstation_dst)
{
  XBT_DEBUG("ws_get_route");
  workstation_CLM03_t src = (workstation_CLM03_t) workstation_src;
  workstation_CLM03_t dst = (workstation_CLM03_t) workstation_dst;
  return surf_network_model->extension.
      network.get_route(src->net_elm,
                  dst->net_elm);
}

static double ws_get_link_bandwidth(const void *link)
{
  return surf_network_model->extension.network.get_link_bandwidth(link);
}

static double ws_get_link_latency(const void *link)
{
  return surf_network_model->extension.network.get_link_latency(link);
}

static int ws_link_shared(const void *link)
{
  return surf_network_model->extension.network.link_shared(link);
}

static void ws_finalize(void)
{
  surf_model_exit(surf_workstation_model);
  surf_workstation_model = NULL;
}

static xbt_dict_t ws_get_properties(const void *ws)
{
  return surf_resource_properties(((workstation_CLM03_t) ws)->cpu);
}

static storage_t find_storage_on_mount_list(void *workstation,const char* storage)
{
  storage_t st = NULL;
  s_mount_t mnt;
  unsigned int cursor;
  xbt_dynar_t storage_list = ((workstation_CLM03_t) workstation)->storage;

  XBT_DEBUG("Search for storage name '%s' on '%s'",storage,((workstation_CLM03_t) workstation)->generic_resource.name);
  xbt_dynar_foreach(storage_list,cursor,mnt)
  {
    XBT_DEBUG("See '%s'",mnt.name);
    if(!strcmp(storage,mnt.name)){
      st = mnt.id;
      break;
    }
  }
  if(!st) xbt_die("Can't find mount '%s' for '%s'",storage,((workstation_CLM03_t) workstation)->generic_resource.name);
  return st;
}

static surf_action_t ws_action_open(void *workstation, const char* mount, const char* path, const char* mode)
{
  storage_t st = find_storage_on_mount_list(workstation, mount);
  XBT_DEBUG("OPEN on disk '%s'",st->generic_resource.name);
  surf_model_t model = st->generic_resource.model;
  return model->extension.storage.open(st, mount, path, mode);
}

static surf_action_t ws_action_close(void *workstation, surf_file_t fp)
{
  storage_t st = find_storage_on_mount_list(workstation, fp->storage);
  XBT_DEBUG("CLOSE on disk '%s'",st->generic_resource.name);
  surf_model_t model = st->generic_resource.model;
  return model->extension.storage.close(st, fp);
}

static surf_action_t ws_action_read(void *workstation, void* ptr, size_t size, size_t nmemb, surf_file_t stream)
{
  storage_t st = find_storage_on_mount_list(workstation, stream->storage);
  XBT_DEBUG("READ on disk '%s'",st->generic_resource.name);
  surf_model_t model = st->generic_resource.model;
  return model->extension.storage.read(st, ptr, (double)size, nmemb, stream);
}

static surf_action_t ws_action_write(void *workstation, const void* ptr, size_t size, size_t nmemb, surf_file_t stream)
{
  storage_t st = find_storage_on_mount_list(workstation, stream->storage);
  XBT_DEBUG("WRITE on disk '%s'",st->generic_resource.name);
  surf_model_t model = st->generic_resource.model;
  return model->extension.storage.write(st,  ptr, size, nmemb, stream);
}

static surf_action_t ws_action_stat(void *workstation, surf_file_t stream)
{
  storage_t st = find_storage_on_mount_list(workstation, stream->storage);
  XBT_DEBUG("STAT on disk '%s'",st->generic_resource.name);
  surf_model_t model = st->generic_resource.model;
  return model->extension.storage.stat(st,  stream);
}

static surf_action_t ws_action_unlink(void *workstation, surf_file_t stream)
{
  storage_t st = find_storage_on_mount_list(workstation, stream->storage);
  XBT_DEBUG("UNLINK on disk '%s'",st->generic_resource.name);
  surf_model_t model = st->generic_resource.model;
  return model->extension.storage.unlink(st,  stream);
}

static surf_action_t ws_action_ls(void *workstation, const char* mount, const char *path)
{
  XBT_DEBUG("LS on mount '%s' and file '%s'",mount, path);
  storage_t st = find_storage_on_mount_list(workstation, mount);
  surf_model_t model = st->generic_resource.model;
  return model->extension.storage.ls(st, path);
}

static void surf_workstation_model_init_internal(void)
{
  surf_workstation_model = surf_model_init();

  surf_workstation_model->name = "Workstation";
  surf_workstation_model->action_unref = ws_action_unref;
  surf_workstation_model->action_cancel = ws_action_cancel;
  surf_workstation_model->action_state_set = ws_action_state_set;

  surf_workstation_model->model_private->resource_used = ws_resource_used;
  surf_workstation_model->model_private->share_resources =
      ws_share_resources;
  surf_workstation_model->model_private->update_actions_state =
      ws_update_actions_state;
  surf_workstation_model->model_private->update_resource_state =
      ws_update_resource_state;
  surf_workstation_model->model_private->finalize = ws_finalize;

  surf_workstation_model->suspend = ws_action_suspend;
  surf_workstation_model->resume = ws_action_resume;
  surf_workstation_model->is_suspended = ws_action_is_suspended;
  surf_workstation_model->set_max_duration = ws_action_set_max_duration;
  surf_workstation_model->set_priority = ws_action_set_priority;
#ifdef HAVE_TRACING
  surf_workstation_model->set_category = ws_action_set_category;
#endif
  surf_workstation_model->get_remains = ws_action_get_remains;
#ifdef HAVE_LATENCY_BOUND_TRACKING
  surf_workstation_model->get_latency_limited = ws_get_latency_limited;
#endif

  surf_workstation_model->extension.workstation.execute = ws_execute;
  surf_workstation_model->extension.workstation.sleep = ws_action_sleep;
  surf_workstation_model->extension.workstation.get_state = ws_get_state;
  surf_workstation_model->extension.workstation.get_speed = ws_get_speed;
  surf_workstation_model->extension.workstation.get_available_speed =
      ws_get_available_speed;

  surf_workstation_model->extension.workstation.communicate =
      ws_communicate;
  surf_workstation_model->extension.workstation.get_route = ws_get_route;
  surf_workstation_model->extension.workstation.execute_parallel_task =
      ws_execute_parallel_task;
  surf_workstation_model->extension.workstation.get_link_bandwidth =
      ws_get_link_bandwidth;
  surf_workstation_model->extension.workstation.get_link_latency =
      ws_get_link_latency;
  surf_workstation_model->extension.workstation.link_shared =
      ws_link_shared;
  surf_workstation_model->extension.workstation.get_properties =
      ws_get_properties;

  surf_workstation_model->extension.workstation.open = ws_action_open;
  surf_workstation_model->extension.workstation.close = ws_action_close;
  surf_workstation_model->extension.workstation.read = ws_action_read;
  surf_workstation_model->extension.workstation.write = ws_action_write;
  surf_workstation_model->extension.workstation.stat = ws_action_stat;
  surf_workstation_model->extension.workstation.unlink = ws_action_unlink;
  surf_workstation_model->extension.workstation.ls = ws_action_ls;
}

void surf_workstation_model_init_current_default(void)
{
  surf_workstation_model_init_internal();
  xbt_cfg_setdefault_int(_surf_cfg_set, "network/crosstraffic", 1);
  surf_cpu_model_init_Cas01();
  surf_network_model_init_LegrandVelho();

  xbt_dynar_push(model_list, &surf_workstation_model);
  sg_platf_host_add_cb(workstation_new);
//  sg_platf_postparse_add_cb(create_workstations);
}

void surf_workstation_model_init_compound()
{

  xbt_assert(surf_cpu_model, "No CPU model defined yet!");
  xbt_assert(surf_network_model, "No network model defined yet!");
  surf_workstation_model_init_internal();
  xbt_dynar_push(model_list, &surf_workstation_model);
  sg_platf_host_add_cb(workstation_new);
//  sg_platf_postparse_add_cb(create_workstations);
}
