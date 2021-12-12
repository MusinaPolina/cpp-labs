#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "point_list.h"

void input_text(intrusive_list_t *list, char *infile) {
  FILE *file = fopen(infile, "r");
  assert(file);
  int x, y;
  while (fscanf(file, "%d %d", &x, &y) == 2) {
    add_point(list, x, y);
  }
  fclose(file);
}

void save_text(intrusive_list_t *list, char *outfile) {
  FILE *file = fopen(outfile, "w");
  assert(file);
  printft(list, file);
  fclose(file);
}

int bytes_to_int(unsigned char *bytes) {
  return (int)bytes[0] | ((int)bytes[1] << 8) | ((int)bytes[2] << 16);
}

void input_bin(intrusive_list_t *lst, char *infile) {
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

void save_bin(intrusive_list_t *list, char *outfile) {
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
