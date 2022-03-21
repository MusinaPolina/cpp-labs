#include "clist.h"
#include <assert.h>
#include <stdlib.h>

void init_list(intrusive_list_t *list) {
  list->head = NULL;
}

void add_node(intrusive_list_t *list, intrusive_node_t *node) {
  if (list->head) {
    list->head->prev = node;
  }
  node->next = list->head;
  list->head = node;
}

intrusive_node_t * remove_node(intrusive_list_t *list, intrusive_node_t *node) {
  intrusive_node_t *prev = node->prev;
  if (prev) {
    prev->next = node->next;
  } else {
    assert(list->head == node);
    list->head = node->next;
  }
  if (node->next) {
    node->next->prev = prev;
  }
  node->prev = node->next = NULL;
  return node;
}

int get_length(intrusive_list_t *list) {
  int length = 0;
  intrusive_node_t *node = list->head;
  while (node) {
    length++;
    node = node->next;
  }
  return length;
}
