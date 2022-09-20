#pragma once
#include "clist.h"

#ifndef POINT_LIST_H_
#define POINT_LIST_H_

typedef struct point {
  int x, y;
  intrusive_node_t node;
} point_t;

void add_point(intrusive_list_t *list, int x, int y);	

int count_points(intrusive_list_t *list);

void remove_all_points(intrusive_list_t *list);

point_t * get_point(intrusive_node_t *node);

#endif
