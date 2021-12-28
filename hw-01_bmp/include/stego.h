#pragma once
#include "bmp.h"

typedef struct tagKey {
  int x, y;
  char c;
} Key;

typedef struct tagKeys {
  size_t size;
  Key *keys;
} Keys;

void insert(BMP *bmp, Keys *keys, char *msg);
char * extract(BMP *bmp, Keys *keys);
