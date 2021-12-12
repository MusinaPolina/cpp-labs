#include "point_list.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

static void init_point(point_t *pnt, int x, int y) {
  pnt->x = x;
  pnt->y = y;
  pnt->node.prev = pnt->node.next = NULL;
}

void add_point(intrusive_list_t *list, int x, int y) {
  assert(list);
  point_t *pnt = malloc(sizeof(struct point));
  assert(pnt);
  init_point(pnt, x, y);
  add_node(list, &pnt->node);
}	

static void count(intrusive_node_t *node, void *data) {
  if (node) {
    ++*(int *)data;
  }
}

int count_points(intrusive_list_t *list) {
  assert(list);
  int cnt = 0;
  apply(list, &count, &cnt);
  return cnt;
}

static point_t * get_point(intrusive_node_t *node) {
  return container_of(node, point_t, node);
}

static void free_point(intrusive_node_t * node) {
  point_t *pnt = get_point(node);
  free(pnt);
}


void remove_all_points(intrusive_list_t *list) {
  while (list->head) {
    free_point(remove_node(list, list->head));
  }
}

static void print_point(intrusive_node_t *node, void *data) {
  if (node) {
    point_t *point = get_point(node);
    assert(data);
    printf((char *)data, point->x, point->y);
  }
}

void print(intrusive_list_t *list, char *fmt) {
  assert(list);
  apply(list, &print_point, fmt);
}

static void print_pointft(intrusive_node_t *node, void *data) {
  if (node) {
    point_t *point = get_point(node);
    assert(data);
    fprintf((FILE *)data, "%d %d\n", point->x, point->y);
  }
}

void printft(intrusive_list_t *list, FILE *file) {
  assert(list);
  apply(list, &print_pointft, file);
}

static void print_pointfb(intrusive_node_t *node, void *data) {
  if (node) {
    point_t *point = get_point(node);
    int byte_size = 255;
    unsigned char buffer[6] = { point->x & byte_size, (point->x >> 8) & byte_size, (point->x >> 16) & byte_size, 
                                point->y & byte_size, (point->y >> 8) & byte_size, (point->y >> 16) & byte_size };
    assert(data);
    fwrite(buffer, sizeof(buffer[0]), 6, (FILE *)data);
  }
}

void printfb(intrusive_list_t *list, FILE *file) {
  assert(list);
  apply(list, &print_pointfb, file);
}
