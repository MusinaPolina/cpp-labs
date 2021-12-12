#pragma once
#include "clist.h"
#include <stdio.h>

typedef struct point {
  int x, y;
  intrusive_node_t node;
} point_t;

void add_point(intrusive_list_t *list, int x, int y);	

int count_points(intrusive_list_t *list);

void remove_all_points(intrusive_list_t *list);

void print(intrusive_list_t *list, char *fmt);

void printft(intrusive_list_t *list, FILE *file);

void printfb(intrusive_list_t *list, FILE *file);
