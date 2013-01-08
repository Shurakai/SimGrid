/* Copyright (c) 2012
 * Christian Heinrich, National Center for Supercomputing Applications
 *                     University of Illinois <cheinric@illinois.edu>
 * All rights reserved
 */

/* This program is free software; you can redistribute it and/or modify it
 * under the terms of the license (GNU LGPL) which comes with this package. */

#include "surf_routing_private.h"

/* Global vars */

XBT_LOG_NEW_DEFAULT_SUBCATEGORY(surf_route_torus, surf, "Routing part of surf");

/* This routing is specifically setup to represent toruss, aka homogeneous sets of machines
 * Note that a router is created, easing the interconnexion with the rest of the world.
 */

/* Business methods */
static void torus_get_route_and_latency(AS_t as,
    sg_routing_edge_t src, sg_routing_edge_t dst,
    sg_platf_route_cbarg_t route, double *lat) {

    s_surf_parsing_link_up_down_t info;
    XBT_DEBUG("torus_get_route_and_latency from '%s'[%d] to '%s'[%d]",
              src->name,src->id,
              dst->name,dst->id);

    printf("torus_get_route_and_latency from '%s'[%d] to '%s'[%d]",
           src->name,src->id,
           dst->name,dst->id);

    static int i = 0;
    static s_sg_platf_link_cbarg_t link;
    if (i == 0) {
        memset(&link, 0, sizeof(link));
        link.id = bprintf("link_%i", i);
        link.bandwidth = 1000000; //torus->bw;
        link.latency = 1; //torus->lat;
        link.state = SURF_RESOURCE_ON;
        /*link.policy = torus->sharing_policy;*/
        sg_platf_new_link(&link);
        i++;
    }


    sg_platf_route_cbarg_t route_tmp;
    sg_platf_route_begin(route_tmp);
    /*route->gw_src = src;*/
    /*route->gw_dst = dst;*/
    /*xbt_dynar_push_as(route->link_list, sg_routing_link_t, link);*/
    sg_platf_route_add_link("link_1", route_tmp);
    printf("Anzahl der Links eins: %lu\n", xbt_dynar_length(route->link_list));
    xbt_assert(!xbt_dynar_is_empty(route->link_list), "Ja, ist leer!");
    sg_platf_route_end(route_tmp);

    void *link2 = xbt_lib_get_or_null(link_lib, "link_0", SURF_LINK_LEVEL);
    xbt_dynar_push(route->link_list, &link2);

    /*route = generic_new_extended_route(as->hierarchy, route_tmp, 1);*/

    printf("End of model_torus_route_and_latency()\n");

    /**lat = 100;*/

    /*if(src->rc_type != SURF_NETWORK_ELEMENT_ROUTER){ // No specific link for router*/
        /*info = xbt_dynar_get_as(as->link_up_down_list,src->id,s_surf_parsing_link_up_down_t);*/
        /*if(info.link_up) { // link up*/
          /*xbt_dynar_push_as(route->link_list,void*,info.link_up);*/
        /*if (lat)*/
          /**lat += surf_network_model->extension.network.get_link_latency(info.link_up);*/
        /*}*/
    /*}*/

    /*if(dst->rc_type != SURF_NETWORK_ELEMENT_ROUTER){ // No specific link for router*/
        /*info = xbt_dynar_get_as(as->link_up_down_list,dst->id,s_surf_parsing_link_up_down_t);*/
        /*if(info.link_down) { // link down*/
          /*xbt_dynar_push_as(route->link_list,void*,info.link_down);*/
        /*if (lat)*/
          /**lat += surf_network_model->extension.network.get_link_latency(info.link_down);*/
        /*}*/
    /*}*/
}

static void model_torus_finalize(AS_t as) {
  printf("End of model-torus_finalize()\n");
  model_none_finalize(as);
}

static int torus_parse_PU(AS_t rc, sg_routing_edge_t elm) {
  XBT_DEBUG("Load process unit \"%s\"", elm->name);
  xbt_dynar_push_as(rc->index_network_elm,sg_routing_edge_t,elm);
  printf("End of model-torus_parse_PU()\n");
  return xbt_dynar_length(rc->index_network_elm)-1;
}

static int torus_parse_AS(AS_t rc, sg_routing_edge_t elm) {
  XBT_DEBUG("Load Autonomous system \"%s\"", elm->name);
  xbt_dynar_push_as(rc->index_network_elm,sg_routing_edge_t,elm);
  printf("End of model-torus_parse_AS()\n");
  return xbt_dynar_length(rc->index_network_elm)-1;
}

/* Creation routing model functions */
AS_t model_torus_create(void)
{
  AS_t result = model_generic_create_sized(sizeof(s_as_t));
  result->get_route_and_latency = torus_get_route_and_latency;
  result->finalize = model_torus_finalize;
  result->parse_AS = torus_parse_AS;
  result->parse_PU = torus_parse_PU;

  printf("End of model-torus_create()\n");
  return (AS_t) result;
}
