#include "mergesort.h"
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>

static void my_memcpy(void *ptr_d, void *ptr_s, size_t element_size) {
  for (size_t i = 0; i < element_size; i++) {
    *((char *)(ptr_d + i)) = *((char *)(ptr_s + i));
  }
}

static void merge(void *array, size_t elements, size_t half, size_t element_size, int (*comparator)(const void *, const void *)) {
  void *buffer = malloc(elements * element_size);
  assert(buffer);
  void *middle = array + half * element_size;
  void *end = array + element_size * elements;
  void *ptr_l = array;
  void *ptr_r = middle;
  void *ptr = buffer;
  while (ptr_l < middle && ptr_r < end) {  
    if (comparator(ptr_l, ptr_r) <= 0) {
      my_memcpy(ptr, ptr_l, element_size);
      ptr_l += element_size;
    } else {
      my_memcpy(ptr, ptr_r, element_size);
      ptr_r += element_size;
    }
    ptr += element_size;
  }
  my_memcpy(ptr, ptr_l, middle - ptr_l); 
  
  my_memcpy(ptr, ptr_r, end - ptr_r); 
  
  my_memcpy(array, buffer, element_size * elements);
 
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
