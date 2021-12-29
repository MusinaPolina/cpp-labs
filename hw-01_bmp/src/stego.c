#include "bmp.h"
#include "stego.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

static int symbol_to_code(char *c) {
  if ('A' <= *c && *c <= 'Z') {
    return *c - 'A';
  }
  switch (*c) {
    case ' ': return 26;
    case '.': return 27;
    case ',': return 28;
    default: assert(0);
  }
}

static char code_to_symbol(int c) {
  if (0 <= c && c < 26) {
    return (char)('A' + c);
  }
  switch (c) {
    case 26: return ' ';
    case 27: return '.';
    case 28: return ',';
    default: assert(0);
  }
}

unsigned char * get_component(Pixel *p, char *c) {
  switch (*c) {
    case 'R': return &p->r;
    case 'G': return &p->g;
    case 'B': return &p->b;
    default: assert(0);
  }
}

static unsigned char * key_pixel(Key *key, BMP *bmp) {
  int x = key->x, y = key->y;
  char c = key->c;
  
  assert(x >= 0 && y >= 0 && x < bmp->infoh.biWidth && y < bmp->infoh.biHeight);
  
  return get_component(&(bmp->pixel_array[x][y]), &c);
}

static const int BITS_IN_CODE = 5;

static void insert_pixel(unsigned char *bit, int value) {
  *bit = ((*bit | 1) ^ 1) ^ (value > 0);
}

static bool insert_code(BMP* bmp, int code, Keys *key, size_t *key_index) {
  for (int i = 0; i < BITS_IN_CODE; i++) {
    if (*key_index == key->size) {
      return 1;
    }
    insert_pixel(key_pixel(&key->keys[*key_index], bmp), code & (1 << i));
    (*key_index)++;
  }
  return 0;
}

void insert(BMP *bmp, Keys *key, char *msg) {
  size_t key_index = 0;
  for (size_t i = 0; i < strlen(msg); i++) {    
    if (insert_code(bmp, symbol_to_code(&msg[i]), key, &key_index)) {
      return;
    }
  }
}

static bool extract_pixel(unsigned char* bit) {
  return *(int *)bit & 1;
}

static char extract_code(Keys *key, size_t *key_index, BMP *bmp) {
  int code = 0;
  for (int i = 0; i < BITS_IN_CODE; i++, (*key_index)++) {
  		code |= (1 << i) * extract_pixel(key_pixel(&key->keys[*key_index], bmp));
  }
  return code_to_symbol(code);
}

char * extract(BMP *bmp, Keys *key) {
  size_t msg_size = key->size / BITS_IN_CODE + 1;
  size_t key_index = 0;
  char *msg = calloc(msg_size, sizeof(char));
  for (size_t i = 0; i < msg_size - 1; i++) {
    msg[i] = extract_code(key, &key_index, bmp);
  }
  return msg;
}
