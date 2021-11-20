#include "str.h"
#include <stddef.h>

size_t my_strlen(const char *s) {
  size_t len = 0;
  while (*s != '\0') {
    len++, s++;
  }
  return len;
}


int my_strcmp(const char *s1, const char *s2) {
  while (*s1 != '\0') {
    if (*s1 != *s2) {
      return (*s1 > *s2) * 2 - 1;
    }
    ++s1, ++s2;
  }
  return (*s1 != *s2) * -1;
}	


char *my_strcat(char * restrict s1, const char * restrict s2) {
  char *s = s1;
  while (*s != '\0') {
    ++s;
  }
  while (*s2 != '\0') {
    *s = *s2;
    ++s, ++s2;
  } 
  return s1;
}


char *my_strcpy(char * restrict s1, const char * restrict s2) {
  char *s = s1;
  while (*s2 != '\0') {
    *s = *s2;
    ++s, ++s2;
  }
  *s = '\0';
  return s1;
}
