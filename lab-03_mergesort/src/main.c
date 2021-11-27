#include "mergesort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp_int(const void *a, const void *b) {
  return *(int *)a - *(int *)b;
}

int string_to_int(char *s) {
  int k = 1;
  if (*s == '-') {
    k = -1;
    s++;
  }
  int ans = 0;
  while (*s != '\0') {
    ans *= 10;
    ans += *s - '0';
    s++;
  }
  return ans * k;
}

void int_sort(int n, char **arg) {
  int *array = malloc((n - 2) * sizeof(int));
  for (int i = 2; i < n; i++) {
    array[i - 2] = string_to_int(arg[i]);
  }
  mergesort(array, n - 2, sizeof(int), cmp_int);
  printf("%d", array[0]);
  for (int i = 1; i < n - 2; i++) {
    printf(" %d", array[i]);
  }
  free(array);
}


int cmp_char(const void *a, const void *b) {
  return *(char *)a - *(char *)b;
}

void char_sort(int n, char **arg) {
  char *array = malloc((n - 2) * sizeof(char));
  for (int i = 2; i < n; i++) {
    array[i - 2] = arg[i][0];
  }
  mergesort(array, n - 2, sizeof(char), cmp_char);
  printf("%c", array[0]);
  for (int i = 1; i < n - 2; i++) {
    printf(" %c", array[i]);
  }
  free(array);
}

int cmp_str(const void *a, const void *b) {
  return strcmp(*(char **)a, *(char **)b);
}

void str_sort(int n, char **arg) {
  char **array = malloc((n - 2) * sizeof(char *));
  for (int i = 2; i < n; i++) {
    array[i - 2] = arg[i];
  }
  mergesort(array, n - 2, sizeof(char *), cmp_str);
  printf("%s", array[0]);
  for (int i = 1; i < n - 2; i++) {
    printf(" %s", array[i]);
  }
  free(array);
}

int main(int argc, char **argv) {
  if (argc == 2) {
    return 0;
  }
  if (argv[1][0] == 'i') {
    int_sort(argc, argv);
  } else if (argv[1][0] == 'c') {
    char_sort(argc, argv);
  } else if (argv[1][0] == 's') {
    str_sort(argc, argv);
  }
  return 0;
}
