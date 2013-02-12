/* Copyright (c) 2012
 * Christian Heinrich, National Center for Supercomputing Applications
 *                     University of Illinois <cheinric@illinois.edu>
 * All rights reserved
 */

/* This program is free software; you can redistribute it and/or modify it
 * under the terms of the license (GNU LGPL) which comes with this package. */

#include "surf_routing_private.h"
#include "assert.h"
inline int* rankId_to_coords(int, xbt_dynar_t);

/* Global vars */

XBT_LOG_NEW_DEFAULT_SUBCATEGORY(surf_route_torus, surf, "Routing part of surf");

/* This routing is specifically setup to represent toruss, aka homogeneous sets of machines
 * Note that a router is created, easing the interconnexion with the rest of the world.
 */

/* Business methods */
static void torus_get_route_and_latency(AS_t as,
    sg_routing_edge_t src, sg_routing_edge_t dst,
    sg_platf_route_cbarg_t route, double *lat) {

    XBT_DEBUG("torus_get_route_and_latency from '%s'[%d] to '%s'[%d]",
              src->name,src->id,
              dst->name,dst->id);

    as_torus_t torusAS = (as_torus_t) as;

    if (src->id == dst->id) {
        void* link = xbt_dynar_get_as(torusAS->links,src->id*(xbt_dynar_length(torusAS->dimensions)+1), void*);
        xbt_dynar_push(route->link_list, &link);

        s_surf_parsing_link_up_down_t info = xbt_dynar_get_as(torusAS->links,src->id*(xbt_dynar_length(torusAS->dimensions)+1), s_surf_parsing_link_up_down_t);

        xbt_dynar_push_as(route->link_list,void*,info.link_down);

        return;
    }

    /**
     * Dimension based routing routes through each dimension consecutively
     * TODO Change to dynamic assignment
     */
    int j, cur_dim, dim_product   = 1;
    long unsigned current_node    = src->id;
    long unsigned next_node       = 0;
    /**
     * Arrays that hold the coordinates of the current node and
     * the target; comparing the values at the i-th position of
     * both arrays, we can easily assess whether we need to route
     * into this dimension or not.
     */
    int* myCoords, *targetCoords;
    myCoords     = rankId_to_coords(src->id, torusAS->dimensions);
    targetCoords = rankId_to_coords(dst->id, torusAS->dimensions);
    /**
     * linkOffset describes the offset where the link
     * we want to use is stored
     * (+1 is added because each node has a link from itself to itself,
     * which can only be the case if src->id == dst->id -- see above
     * for this special case)
     */
    long linkOffset = (xbt_dynar_length(torusAS->dimensions)+1)*src->id;
    bool use_lnk_up          = false; // Is this link of the form "cur -> next" or "next -> cur"?
                                      // false means: next -> cur
    while (current_node != dst->id) {
      dim_product = 1; // First, we will route in x-dimension
      for (j = 0; j < xbt_dynar_length(torusAS->dimensions); j++) {
          cur_dim = xbt_dynar_get_as(torusAS->dimensions, j, int);

          // current_node/dim_product = position in current dimension
          if ((current_node/dim_product) % cur_dim != (dst->id/dim_product) % cur_dim) {

              if (( targetCoords[j] > myCoords[j] && targetCoords[j] <= myCoords[j]+cur_dim/2) // Is the target node on the right, without the wrap-around?
                  || ( myCoords[j] > cur_dim/2 && (myCoords[j]+cur_dim/2)%cur_dim >= targetCoords[j] )) { // Or do we need to use the wrap around to reach it?
                if ((current_node / dim_product) % cur_dim == cur_dim-1)
                    next_node = (current_node+dim_product-dim_product*cur_dim);
                else
                    next_node = (current_node+dim_product);

                // HERE: We use *CURRENT* node for calculation (as opposed to next_node)
                linkOffset = current_node*(xbt_dynar_length(torusAS->dimensions)+1)+j+1;
                use_lnk_up = true;
                assert(linkOffset >= 0);
              }
              else { // Route to the left
                if ((current_node / dim_product) % cur_dim == 0)
                    next_node = (current_node-dim_product+dim_product*cur_dim);
                else
                    next_node = (current_node-dim_product);

                // HERE: We use *next* node for calculation (as opposed to current_node!)
                linkOffset = next_node*(xbt_dynar_length(torusAS->dimensions)+1)+j+1;
                use_lnk_up = false;

                assert(linkOffset >= 0);
              }
              XBT_DEBUG("torus_get_route_and_latency - current_node: %lu, next_node: %lu, linkOffset is %lu",
              current_node, next_node, linkOffset);

              break;
          }

          dim_product *= cur_dim;
      }

      s_surf_parsing_link_up_down_t info = xbt_dynar_get_as(torusAS->links,linkOffset, s_surf_parsing_link_up_down_t);

      if (use_lnk_up == false)
          xbt_dynar_push_as(route->link_list,void*,info.link_down);
      else
          xbt_dynar_push_as(route->link_list,void*,info.link_up);

      current_node = next_node;
      next_node = 0;
    }
    free(myCoords);
    free(targetCoords);
}

static void model_torus_finalize(AS_t as) {
  /*xbt_dynar_free(&((as_torus_t)as)->dimensions);*/
  xbt_dynar_free(&((as_torus_t)as)->links);
  model_generic_finalize(as);
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

inline int* rankId_to_coords(int rankId, xbt_dynar_t dimensions) {

    int i = 0, cur_dim_size = 1, dim_size_product = 1;
    int* coords = malloc(xbt_dynar_length(dimensions)*sizeof(int));
    for (i = 0; i < xbt_dynar_length(dimensions); i++) {
        cur_dim_size = xbt_dynar_get_as(dimensions, i, int);
        coords[i] = (rankId / dim_size_product) % cur_dim_size;
        dim_size_product *= cur_dim_size;
    }

    return coords;
}
