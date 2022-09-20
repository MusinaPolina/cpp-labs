#include "point_list.h"
#include <assert.h>
#include <stdlib.h>


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

point_t * get_point(intrusive_node_t *node) {
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
