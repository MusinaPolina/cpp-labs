#pragma once
#include <stddef.h>
#ifndef CLIST_H_
#define CLIST_H_

typedef struct intrusive_node {
  struct intrusive_node *next;
  struct intrusive_node *prev;
} intrusive_node_t;

typedef struct intrusive_list {
  intrusive_node_t *head;
  intrusive_node_t *tail;
} intrusive_list_t;

void init_list(intrusive_list_t *list);

void add_node(intrusive_list_t *list, intrusive_node_t *node);

struct intrusive_node * remove_node(intrusive_list_t *list, intrusive_node_t *node);

void apply(intrusive_list_t *list, void (*op)(intrusive_node_t *node, void *data), void *data);

#endif
#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))
