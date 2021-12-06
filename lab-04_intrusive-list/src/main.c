#include "clist.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct point {
  int x, y;
  intrusive_node_t node;
} point_t;

void init_point(point_t *pnt, int x, int y) {
  pnt->x = x;
  pnt->y = y;
  pnt->node.prev = pnt->node.next = NULL;
}

void add_point(intrusive_list_t *list, int x, int y) {
  point_t *pnt = malloc(sizeof(struct point));
  assert(pnt);
  init_point(pnt, x, y);
  add_node(list, &pnt->node);
}

point_t * get_point(intrusive_node_t *node) {
  return container_of(node, point_t, node);
}	

void free_point(intrusive_node_t * node) {
  point_t *pnt = get_point(node);
  free(pnt);
}

void remove_point(intrusive_list_t *list, int x, int y) { // removes all (x, y) pairs
  intrusive_node_t *node = list->head;
  while (node) {
    point_t *pnt = get_point(node);
    intrusive_node_t *copy = node;
    node = node->next;
    if (pnt->x == x && pnt->y == y) {
      free_point(remove_node(list, copy));
    }
  }
}

void show_point(point_t *pnt) {
  printf("(%d %d)", pnt->x, pnt->y);
}

void show_all_points(intrusive_list_t *list) {
  if (list->head) {
    show_point(get_point(list->head));
    intrusive_node_t *node = list->head->next;
    while (node) {
      printf(" ");
      show_point(get_point(node));
      node = node->next;
    }
  }
  printf("\n");
}

void remove_all_points(intrusive_list_t *list) {
  while (list->head) {
    free_point(remove_node(list, list->head));
  }
}

int main() {
  char cmd[11] = "";
  intrusive_list_t l;
  init_list(&l);
  while (1) {
    scanf("%10s", cmd);
    if (strcmp(cmd, "add") == 0 || strcmp(cmd, "rm") == 0) {
      int x, y;
      scanf("%d %d", &x, &y);
      if (strcmp(cmd, "rm") == 0) {
        remove_point(&l, x, y);
      } else {
        add_point(&l, x, y);
      }
    } else if (strcmp(cmd, "print") == 0) {
      show_all_points(&l);
    } else if (strcmp(cmd, "rma") == 0) {
      remove_all_points(&l);
    } else if (strcmp(cmd, "len") == 0) {
      printf("%d\n", get_length(&l));
    } else if (strcmp(cmd, "exit") == 0) {
      break;
    } else {
      printf("Unknown command\n");
    }
  }
  remove_all_points(&l);
  return 0;
}
