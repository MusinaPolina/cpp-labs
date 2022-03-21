#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "point_list.h"

static void input_text(intrusive_list_t *list, char *infile) {
  FILE *file = fopen(infile, "r");
  assert(file);
  int x, y;
  while (fscanf(file, "%d %d", &x, &y) == 2) {
    add_point(list, x, y);
  }
  fclose(file);
}

static void print_pointft(intrusive_node_t *node, void *data) {
  assert(node);
  point_t *point = get_point(node);
  assert(data);
  fprintf((FILE *)data, "%d %d\n", point->x, point->y);
}

static void printft(intrusive_list_t *list, FILE *file) {
  assert(list);
  apply(list, &print_pointft, file);
}


static void save_text(intrusive_list_t *list, char *outfile) {
  FILE *file = fopen(outfile, "w");
  assert(file);
  printft(list, file);
  fclose(file);
}


static void print_point(intrusive_node_t *node, void *data) {
  if (node) {
    point_t *point = get_point(node);
    assert(data);
    printf((char *)data, point->x, point->y);
  }
}

static void print(intrusive_list_t *list, char *fmt) {
  assert(list);
  apply(list, &print_point, fmt);
}

const int byte_number = 3;
static const int byte_shift = 8;
static const int byte_size = (1 << byte_shift) - 1;

static int bytes_to_int(unsigned char *bytes) {
  int negative = bytes[byte_number - 1] & (1 << (byte_shift - 1));
  for (int i = 0; i < byte_number; i++) {
    bytes[i] ^= byte_size * (negative != 0);
  }
  int ans = 0;
  for (int i = 0; i < byte_number; i++) {
    ans |= (int)(bytes[i] << (byte_shift * i));
  }
  if (negative) {
    ans = -ans - 1;
  }
  return ans;
}

static void input_bin(intrusive_list_t *lst, char *infile) {
  FILE *file = fopen(infile, "rb");
  assert(file);
  unsigned char bytes[6];
  while (fread(bytes, sizeof(bytes[0]), sizeof(bytes) / sizeof(bytes[0]), file) == 6) {
    int x = bytes_to_int(bytes);
    int y = bytes_to_int(bytes + sizeof(bytes[0]) * 3);
    add_point(lst, x, y);
  }
  fclose(file);
}

void int_to_bytes(int x, unsigned char *buffer) {
  if (x < 0) {
    int_to_bytes(-x - 1, buffer);
    for (int i = 0; i < byte_number; i++) {
      buffer[i] ^= byte_size;
    }
    return;
  }
  for (int i = 0; i < byte_number; i++) {
    buffer[i] = (x >> (i * byte_shift)) & byte_size;
  }
}

static void print_pointfb(intrusive_node_t *node, void *data) {
  assert(node);
  point_t *point = get_point(node);
  int int_size = sizeof(unsigned char) * byte_number;
  unsigned char *buffer = malloc(int_size * 2);
  int_to_bytes(point->x, buffer);
  int_to_bytes(point->y, buffer + int_size);
  assert(data);
  fwrite(buffer, sizeof(buffer[0]), int_size * 2, (FILE *)data);
  free(buffer);
}

static void printfb(intrusive_list_t *list, FILE *file) {
  assert(list);
  apply(list, &print_pointfb, file);
}

static void save_bin(intrusive_list_t *list, char *outfile) {
  FILE *file = fopen(outfile, "wb");
  assert(file);
  printfb(list, file);
  fclose(file);
}

int main(int argc, char **argv) {
  assert(argc >= 4);
  
  char *infmt = argv[1];
  char *infile = argv[2];
  
  intrusive_list_t list;
  init_list(&list);
  
  if (strcmp(infmt, "loadtext") == 0) {
    input_text(&list, infile);
  } else if (strcmp(infmt, "loadbin") == 0) {
    input_bin(&list, infile);
  } else {
    assert(0);
  }
  
  char *action = argv[3];
  if (strcmp(action, "count") == 0) {
    printf("%d\n", count_points(&list));
  } else {
    assert(argc == 5);
  }
  
  if (strcmp(action, "print") == 0) {
    print(&list, argv[4]);
    printf("\n");
  } else if (strcmp(action, "savetext") == 0) {
    save_text(&list, argv[4]);
  } else if (strcmp(action, "savebin") == 0) {
    save_bin(&list, argv[4]);
  }
  remove_all_points(&list);
  return 0;
}
