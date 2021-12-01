#include "mergesort.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int cmp_int(const void *a, const void *b) {
  return *(int *)a - *(int *)b;
}

static void int_sort(int n, char **arg) {
  int *array = malloc(n * sizeof(int));
  assert(array);
  for (int i = 0; i < n; i++) {
    array[i] = atoi(arg[i]);
  }
  mergesort(array, n, sizeof(int), cmp_int);
  printf("%d", array[0]);
  for (int i = 1; i < n; i++) {
    printf(" %d", array[i]);
  }
  printf("\n");
  free(array);
}


static int cmp_char(const void *a, const void *b) {
  return *(char *)a - *(char *)b;
}

static void char_sort(int n, char **arg) {
  char *array = malloc(n * sizeof(char));
  assert(array);
  for (int i = 0; i < n; i++) {
    array[i] = arg[i][0];
  }
  mergesort(array, n, sizeof(char), cmp_char);
  printf("%c", array[0]);
  for (int i = 1; i < n; i++) {
    printf(" %c", array[i]);
  }
  printf("\n");
  free(array);
}

static int cmp_str(const void *a, const void *b) {
  return strcmp(*(char **)a, *(char **)b);
}

static void str_sort(int n, char **arg) {
  char **array = malloc(n * sizeof(char *));
  for (int i = 0; i < n; i++) {
    array[i] = arg[i];
  }
  mergesort(array, n, sizeof(char *), cmp_str);
  printf("%s", array[0]);
  for (int i = 1; i < n; i++) {
    printf(" %s", array[i]);
  }
  printf("\n");
  free(array);
}

int main(int argc, char **argv) {
  if (argc == 2) {
    printf("\n");
    return 0;
  }
  if (argv[1][0] == 'i') {
    int_sort(argc - 2, argv + 2);
  } else if (argv[1][0] == 'c') {
    char_sort(argc - 2, argv + 2);
  } else if (argv[1][0] == 's') {
    str_sort(argc - 2, argv + 2);
  }
  return 0;
}
