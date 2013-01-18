/* Copyright (c) 2012
 * Christian Heinrich, National Center for Supercomputing Applications
 *                     University of Illinois <cheinric@illinois.edu>
 * All rights reserved
 */

/* This program is free software; you can redistribute it and/or modify it
 * under the terms of the license (GNU LGPL) which comes with this package. */

#include "surf_routing_private.h"
#include "assert.h"

/* Global vars */

XBT_LOG_NEW_DEFAULT_SUBCATEGORY(surf_route_torus, surf, "Routing part of surf");

/* This routing is specifically setup to represent toruss, aka homogeneous sets of machines
 * Note that a router is created, easing the interconnexion with the rest of the world.
 */

/* Business methods */
static void torus_get_route_and_latency(AS_t as,
    sg_routing_edge_t src, sg_routing_edge_t dst,
    sg_platf_route_cbarg_t route, double *lat) {

    /*s_surf_parsing_link_up_down_t info;*/
    /*XBT_DEBUG("torus_get_route_and_latency from '%s'[%d] to '%s'[%d]",*/
              /*src->name,src->id,*/
              /*dst->name,dst->id);*/

    printf("torus_get_route_and_latency from'%s'[%d] to '%s'[%d]\n",
           src->name,src->id,
           dst->name,dst->id);

    as_torus_t torusAS = (as_torus_t) as;

    char* link_name;
    if (src->id == dst->id) {
        /*link_name = bprintf("*/
        link_name = bprintf("link_from_%i_to_%i", src->id, src->id);
        printf("src and dst are equal... adding loop\n");
        void *link = xbt_lib_get_or_null(link_lib, link_name, SURF_LINK_LEVEL);
        xbt_dynar_push(route->link_list, &link);
        printf("Leaving route_torus_latency...\n");
        free(link_name);

        return;
    }

    /**
     * Dimension based routing routes through each dimension consecutively
     * TODO Change to dynamic assignment
     */
    int x                         = xbt_dynar_get_as(torusAS->dimensions, 0, int);
    int y                         = xbt_dynar_get_as(torusAS->dimensions, 1, int);
    int z                         = xbt_dynar_get_as(torusAS->dimensions, 2, int);
    printf("x=%i,y=%i,z=%i\n", x, y, z);
    int current_node              = src->id;
    int next_node                 = 0;
    int myCoords[3]               = {src->id % x, ( src->id / x) % y, (src->id / x*y) % z};
    int targetCoords[3]           = {dst->id % x, ( dst->id / x) % y, (dst->id / x*y) % z};
    bool use_lnk_from_cur_to_next = false;
    while (current_node != dst->id) {
      // First, we will route in x-dimension
      printf("Current node: %i, src: %i, dst: %i \n", current_node, src->id, dst->id);
      if (current_node % x != dst->id % x) {
         // Route to the right
         if (( targetCoords[0] > myCoords[0] && targetCoords[0] <= myCoords[0]+x/2) // Are we on the right, without the wrap-around?
             || ( myCoords[0] > x/2 && (myCoords[0]+x/2)%x >= targetCoords[0] )) { // Or do we need to use the wrap around?
            if (current_node % x == x-1)
                next_node = (current_node+1-x);
            else
                next_node = (current_node+1);

            use_lnk_from_cur_to_next = true;
         }
         else { // route to the left
            if (current_node % x == 0)
                next_node = current_node - 1 + x;
            else
                next_node = current_node - 1;

            use_lnk_from_cur_to_next = false;
         }
         /*printf("Routing in x dimension: Next node: %i\n", next_node);*/
      }
      else if ((current_node / x ) % y != (dst->id / x) % y) {
        if (( targetCoords[1] > myCoords[1] && targetCoords[1] <= myCoords[1]+y/2) // Is the target node above us, without having to use the wrap-around?
            || ( myCoords[1] > y/2 && (myCoords[1]+y/2)%y >= targetCoords[1] )) {
           if ( (current_node / x) % y == y-1)
               next_node = current_node + x - x*y;
           else
               next_node = current_node + x;

           use_lnk_from_cur_to_next = true;
        }
        else {
            if ( (current_node / x) % y == 0) // Use wrap around from bottom to top
                next_node = current_node - x + x*y;
            else // Route down
                next_node = current_node - x;

            use_lnk_from_cur_to_next = false;
        }
        /*printf("Routing in y dimension: Next node: %i\n", next_node);*/
      }
      else if ((current_node / (x*y) ) % z != (dst->id / (x*y)) % z) {
        if (( targetCoords[2] > myCoords[2] && targetCoords[2] <= myCoords[2]+z/2) // Is the target node above us, without having to use the wrap-around?
                  || ( myCoords[2] > z/2 && (myCoords[2]+z/2)%z >= targetCoords[2] )) {
           if ( (current_node / x) % y == y-1)
               next_node = current_node + x*y - x*y*z;
           else
               next_node = current_node + x*y;

           use_lnk_from_cur_to_next = true;
        }
        else {
            if ( (current_node / (x*y)) % z == 0) // Use wrap around from bottom to top
                next_node = current_node - x*y + x*y*z;
            else // Route down
                next_node = current_node - x*y;

            use_lnk_from_cur_to_next = false;
        }

        /*printf("Routing in z dimension: Next node: %i\n", next_node);*/
      }

      printf("Current node is %i\n", current_node);

      assert(next_node >= 0);

      if (use_lnk_from_cur_to_next)
        link_name = bprintf("link_from_%i_to_%i", current_node, next_node);
      else
        link_name = bprintf("link_from_%i_to_%i", next_node, current_node);

      printf("Adding link %s to the route\n", link_name);
      void *link = xbt_lib_get_or_null(link_lib, link_name, SURF_LINK_LEVEL);
      xbt_dynar_push(route->link_list, &link);

      current_node = next_node;
      next_node = -1;
    }
    free(link_name);


    /*route = generic_new_extended_route(as->hierarchy, route_tmp, 1);*/

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
  model_none_finalize(as);
}

static int torus_parse_PU(AS_t rc, sg_routing_edge_t elm) {
  XBT_DEBUG("Load process unit \"%s\"", elm->name);
  xbt_dynar_push_as(rc->index_network_elm,sg_routing_edge_t,elm);
  return xbt_dynar_length(rc->index_network_elm)-1;
}

static int torus_parse_AS(AS_t rc, sg_routing_edge_t elm) {
  XBT_DEBUG("Load Autonomous system \"%s\"", elm->name);
  xbt_dynar_push_as(rc->index_network_elm,sg_routing_edge_t,elm);
  return xbt_dynar_length(rc->index_network_elm)-1;
}

/* Creation routing model functions */
AS_t model_torus_create(void)
{
  AS_t result = model_generic_create_sized(sizeof(s_as_torus_t));
  result->get_route_and_latency = torus_get_route_and_latency;
  result->finalize = model_torus_finalize;
  result->parse_AS = torus_parse_AS;
  result->parse_PU = torus_parse_PU;

  return (AS_t) result;
}
