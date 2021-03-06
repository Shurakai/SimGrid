/* Copyright (c) 2010. The SimGrid Team.
 * All rights reserved.                                                     */

/* This program is free software; you can redistribute it and/or modify it
  * under the terms of the license (GNU LGPL) which comes with this package. */

#ifndef INSTR_PRIVATE_H_
#define INSTR_PRIVATE_H_

#include "simgrid_config.h"

#ifdef HAVE_TRACING

/* Need to define function drand48 for Windows */
#ifdef _WIN32
#  define drand48() (rand()/(RAND_MAX + 1.0))
#endif

#define INSTR_DEFAULT_STR_SIZE 500

#include "instr/instr.h"
#include "msg/msg.h"
#include "simdag/private.h"
#include "simix/smx_private.h"
#include "xbt/graph_private.h"

typedef enum {
  PAJE_DefineContainerType,
  PAJE_DefineVariableType,
  PAJE_DefineStateType,
  PAJE_DefineEventType,
  PAJE_DefineLinkType,
  PAJE_DefineEntityValue,
  PAJE_CreateContainer,
  PAJE_DestroyContainer,
  PAJE_SetVariable,
  PAJE_AddVariable,
  PAJE_SubVariable,
  PAJE_SetState,
  PAJE_PushState,
  PAJE_PopState,
  PAJE_ResetState,
  PAJE_StartLink,
  PAJE_EndLink,
  PAJE_NewEvent
} e_event_type;

typedef enum {
  TYPE_VARIABLE,
  TYPE_LINK,
  TYPE_CONTAINER,
  TYPE_STATE,
  TYPE_EVENT
} e_entity_types;

typedef struct s_type *type_t;
typedef struct s_type {
  char *id;
  char *name;
  char *color;
  e_entity_types kind;
  struct s_type *father;
  xbt_dict_t children;
  xbt_dict_t values; //valid for all types except variable and container
}s_type_t;

typedef struct s_val *val_t;
typedef struct s_val {
  char *id;
  char *name;
  char *color;
  type_t father;
}s_val_t;

typedef enum {
  INSTR_HOST,
  INSTR_LINK,
  INSTR_ROUTER,
  INSTR_AS,
  INSTR_SMPI,
  INSTR_MSG_PROCESS,
  INSTR_MSG_TASK
} e_container_types;

typedef struct s_container *container_t;
typedef struct s_container {
  sg_routing_edge_t net_elm;
  char *name;     /* Unique name of this container */
  char *id;       /* Unique id of this container */
  type_t type;    /* Type of this container */
  int level;      /* Level in the hierarchy, root level is 0 */
  e_container_types kind; /* This container is of what kind */
  struct s_container *father;
  xbt_dict_t children;
}s_container_t;

extern xbt_dict_t created_categories;
extern xbt_dict_t declared_marks;
extern xbt_dict_t user_host_variables;
extern xbt_dict_t user_link_variables;
extern double TRACE_last_timestamp_to_dump;

/* instr_paje_header.c */
void TRACE_header(int basic);

/* from paje.c */
void TRACE_paje_start(void);
void TRACE_paje_end(void);
void TRACE_paje_dump_buffer (int force);
void new_pajeDefineContainerType(type_t type);
void new_pajeDefineVariableType(type_t type);
void new_pajeDefineStateType(type_t type);
void new_pajeDefineEventType(type_t type);
void new_pajeDefineLinkType(type_t type, type_t source, type_t dest);
void new_pajeDefineEntityValue (val_t type);
void new_pajeCreateContainer (container_t container);
void new_pajeDestroyContainer (container_t container);
void new_pajeSetVariable (double timestamp, container_t container, type_t type, double value);
void new_pajeAddVariable (double timestamp, container_t container, type_t type, double value);
void new_pajeSubVariable (double timestamp, container_t container, type_t type, double value);
void new_pajeSetState (double timestamp, container_t container, type_t type, val_t value);
void new_pajePushState (double timestamp, container_t container, type_t type, val_t value);
void new_pajePopState (double timestamp, container_t container, type_t type);
void new_pajeResetState (double timestamp, container_t container, type_t type);
void new_pajeStartLink (double timestamp, container_t container, type_t type, container_t sourceContainer, const char *value, const char *key);
void new_pajeEndLink (double timestamp, container_t container, type_t type, container_t destContainer, const char *value, const char *key);
void new_pajeNewEvent (double timestamp, container_t container, type_t type, val_t value);

/* declaration of instrumentation functions from msg_task_instr.c */
void TRACE_msg_set_task_category(msg_task_t task, const char *category);
void TRACE_msg_task_create(msg_task_t task);
void TRACE_msg_task_execute_start(msg_task_t task);
void TRACE_msg_task_execute_end(msg_task_t task);
void TRACE_msg_task_destroy(msg_task_t task);
void TRACE_msg_task_get_start(void);
void TRACE_msg_task_get_end(double start_time, msg_task_t task);
int TRACE_msg_task_put_start(msg_task_t task);    //returns TRUE if the task_put_end must be called
void TRACE_msg_task_put_end(void);

/* declaration of instrumentation functions from msg_process_instr.c */
char *instr_process_id (msg_process_t proc, char *str, int len);
char *instr_process_id_2 (const char *process_name, int process_pid, char *str, int len);
void TRACE_msg_process_change_host(msg_process_t process, msg_host_t old_host,
                                   msg_host_t new_host);
void TRACE_msg_process_create (const char *process_name, int process_pid, msg_host_t host);
void TRACE_msg_process_destroy (const char *process_name, int process_pid, msg_host_t host);
void TRACE_msg_process_kill(msg_process_t process);
void TRACE_msg_process_suspend(msg_process_t process);
void TRACE_msg_process_resume(msg_process_t process);
void TRACE_msg_process_sleep_in(msg_process_t process);   //called from msg/gos.c
void TRACE_msg_process_sleep_out(msg_process_t process);
void TRACE_msg_process_end(msg_process_t process);

/* from surf_instr.c */
void TRACE_surf_alloc(void);
void TRACE_surf_release(void);
void TRACE_surf_host_set_power(double date, const char *resource, double power);
void TRACE_surf_link_set_bandwidth(double date, const char *resource, double bandwidth);
void TRACE_surf_link_set_latency(double date, const char *resource, double latency);
void TRACE_surf_action(surf_action_t surf_action, const char *category);

//for tracing gtnets
void TRACE_surf_gtnets_communicate(void *action, void *src, void *dst);

/* from smpi_instr.c */
void TRACE_internal_smpi_set_category (const char *category);
const char *TRACE_internal_smpi_get_category (void);
void TRACE_smpi_alloc(void);
void TRACE_smpi_release(void);
void TRACE_smpi_init(int rank);
void TRACE_smpi_finalize(int rank);
void TRACE_smpi_collective_in(int rank, int root, const char *operation);
void TRACE_smpi_collective_out(int rank, int root, const char *operation);
void TRACE_smpi_computing_init(int rank);
void TRACE_smpi_computing_out(int rank);
void TRACE_smpi_computing_in(int rank);
void TRACE_smpi_ptp_in(int rank, int src, int dst, const char *operation);
void TRACE_smpi_ptp_out(int rank, int src, int dst, const char *operation);
void TRACE_smpi_send(int rank, int src, int dst);
void TRACE_smpi_recv(int rank, int src, int dst);

/* from instr_config.c */
int TRACE_start (void);
int TRACE_end (void);
int TRACE_needs_platform (void);
int TRACE_is_enabled(void);
int TRACE_platform(void);
int TRACE_platform_topology(void);
int TRACE_is_configured(void);
int TRACE_smpi_is_enabled(void);
int TRACE_smpi_is_grouped(void);
int TRACE_smpi_is_computing(void);
int TRACE_categorized (void);
int TRACE_uncategorized (void);
int TRACE_msg_process_is_enabled(void);
int TRACE_buffer (void);
int TRACE_onelink_only (void);
int TRACE_disable_destroy (void);
int TRACE_basic (void);
char *TRACE_get_comment (void);
char *TRACE_get_comment_file (void);
char *TRACE_get_filename(void);
char *TRACE_get_viva_uncat_conf (void);
char *TRACE_get_viva_cat_conf (void);
void TRACE_global_init(int *argc, char **argv);
void TRACE_help(int detailed);
void TRACE_generate_viva_uncat_conf (void);
void TRACE_generate_viva_cat_conf (void);
void instr_pause_tracing (void);
void instr_resume_tracing (void);

/* from resource_utilization.c */
void TRACE_surf_host_set_utilization(const char *resource,
                                     const char *category,
                                     double value,
                                     double now,
                                     double delta);
void TRACE_surf_link_set_utilization(const char *resource,
                                     const char *category,
                                     double value,
                                     double now,
                                     double delta);
void TRACE_surf_resource_utilization_alloc(void);
void TRACE_surf_resource_utilization_release(void);

/* instr_paje.c */
extern xbt_dict_t trivaNodeTypes;
extern xbt_dict_t trivaEdgeTypes;
long long int instr_new_paje_id (void);
void PJ_container_alloc (void);
void PJ_container_release (void);
container_t PJ_container_new (const char *name, e_container_types kind, container_t father);
container_t PJ_container_get (const char *name);
container_t PJ_container_get_or_null (const char *name);
container_t PJ_container_get_root (void);
void PJ_container_set_root (container_t root);
void PJ_container_free (container_t container);
void PJ_container_free_all (void);
void PJ_container_remove_from_parent (container_t container);

/* instr_paje_types.c */
void PJ_type_alloc (void);
void PJ_type_release (void);
type_t PJ_type_get_root (void);
type_t PJ_type_container_new (const char *name, type_t father);
type_t PJ_type_event_new (const char *name, type_t father);
type_t PJ_type_variable_new (const char *name, const char *color, type_t father);
type_t PJ_type_link_new (const char *name, type_t father, type_t source, type_t dest);
type_t PJ_type_state_new (const char *name, type_t father);
type_t PJ_type_get (const char *name, const type_t father);
type_t PJ_type_get_or_null (const char *name, type_t father);
void PJ_type_free (type_t type);
void PJ_type_free_all (void);

/* instr_paje_values.c */
val_t PJ_value_new (const char *name, const char *color, type_t father);
val_t PJ_value_get_or_new (const char *name, const char *color, type_t father);
val_t PJ_value_get (const char *name, const type_t father);
void PJ_value_free (val_t value);

/* instr_routing.c */
void instr_routing_define_callbacks (void);
void instr_new_variable_type (const char *new_typename, const char *color);
void instr_new_user_variable_type  (const char *father_type, const char *new_typename, const char *color);
void instr_new_user_state_type (const char *father_type, const char *new_typename);
void instr_new_value_for_user_state_type (const char *typename, const char *value, const char *color);
int instr_platform_traced (void);
xbt_graph_t instr_routing_platform_graph (void);
void instr_routing_platform_graph_export_graphviz (xbt_graph_t g, const char *filename);

#endif /* HAVE_TRACING */

#ifdef HAVE_JEDULE
#include "instr/jedule/jedule_sd_binding.h"
#endif

#endif /* INSTR_PRIVATE_H_ */
