#include "clist.h"
#include <assert.h>
#include <stdlib.h>

void init_list(intrusive_list_t *list) {
  assert(list);
  list->head = NULL;
  list->tail = NULL;
}

void add_node(intrusive_list_t *list, intrusive_node_t *node) {
  assert(list);
  assert(node);
  if (list->tail) {
    list->tail->next = node;
  } else {
    list->head = node;
  }
  node->prev = list->tail;
  list->tail = node;
}

intrusive_node_t * remove_node(intrusive_list_t *list, intrusive_node_t *node) {
  assert(list);
  assert(node);
  intrusive_node_t *prev = node->prev;
  if (prev) {
    prev->next = node->next;
  } else {
    list->head = node->next;
  }
  intrusive_node_t *next = node->next;
  if (next) {
    next->prev = node->prev;
  } else {
    list->tail = node->prev;
  }
  node->prev = node->next = NULL;
  return node;
}

void apply(intrusive_list_t *list, void (*op)(intrusive_node_t *node, void *data), void *data) {
  assert(list);
  intrusive_node_t *node = list->head;
  while (node) {
    intrusive_node_t *next = node->next;
    op(node, data);
    node = next;
  }
}
