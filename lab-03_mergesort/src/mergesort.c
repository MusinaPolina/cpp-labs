#include "mergesort.h"
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

void my_memcpy(void *ptr_d, void *ptr_s, size_t element_size) {
  for (size_t i = 0; i < element_size; i++) {
    *((char *)ptr_d) = *((char *)ptr_s);
  }
}

void *array_pointer(void *array, size_t index, size_t element_size) {
  return array + index * element_size;
}

void merge(void *array, size_t elements, size_t half, size_t element_size, int (*comparator)(const void *, const void *)) {
  void *buffer = malloc(elements * element_size);
  assert(buffer);
  size_t il = 0, ir = half;
  while (il < half && ir < elements) {
    void *ptr_l = array_pointer(array, il, element_size);
    void *ptr_r = array_pointer(array, ir, element_size);
    void *ptr = array_pointer(buffer, il + ir - half, element_size);   
    if (comparator(ptr_l, ptr_r) <= 0) {
      my_memcpy(ptr, ptr_l, element_size);
      il++;
    } else {
      my_memcpy(ptr, ptr_r, element_size);
      ir++;
    }
  }
  for (size_t i = il; i < half; i++) {
    my_memcpy(array_pointer(buffer, i + ir - half, element_size), array_pointer(array, i, element_size), element_size); 
  }
  for (size_t i = ir; i < elements; i++) {
    my_memcpy(array_pointer(buffer, il + i - half, element_size), array_pointer(array, i, element_size), element_size); 
  }
  for (size_t i = 0; i < elements; i++) {
    my_memcpy(array_pointer(array, i, element_size), array_pointer(buffer, i, element_size), element_size);
  }
  free(buffer); 
}

void mergesort(void *array, size_t elements, size_t element_size, int (*comparator)(const void *, const void *)) {
  if (elements < 2) {
    return;
  }
  size_t half = elements / 2;
  mergesort(array, half, element_size, comparator);
  mergesort((array + half * element_size), elements - half, element_size, comparator);
  merge(array, elements, half, element_size, comparator);
}
