#include "str.h"
#include "test_str.h"
#include <assert.h>


void test_strlen() {
  assert(my_strlen("Hello world!") == 12);
  assert(my_strlen("") == 0);
}


void test_strcmp() {
  assert(my_strcmp("", "") == 0);
  assert(my_strcmp("", "abc") == -1);
  assert(my_strcmp("abc", "") == 1);
  assert(my_strcmp("!!", "!!") == 0);
  assert(my_strcmp("ABC", "ABD") == -1);
  assert(my_strcmp("WWW", "WW") == 1);
  assert(my_strcmp("abc", "z") == -1);
}

#include <stdio.h>

void test_strcat() {
  char s1[10] = "abc";
  assert(my_strcmp(my_strcat(s1, "defg"), "abcdefg") == 0);
  char s2[10] = "";
  assert(my_strcmp(my_strcat(s2, ""), "") == 0);
  assert(my_strcmp(my_strcat(s2, "abc"), "abc") == 0);
  char s3[10] = "xxx";
  assert(my_strcmp(my_strcat(s3, ""), "xxx") == 0);
}


void test_strcpy() { 
  char s1[10] = "";
  assert(my_strcmp(my_strcpy(s1, ""), "") == 0);
  char s2[10] = "";
  assert(my_strcmp(my_strcpy(s2, "abc"), "abc") == 0);
  char s3[10] = "zzz";
  assert(my_strcmp(my_strcpy(s3, ""), "") == 0);
  char s4[10] = "aaaaa";
  assert(my_strcmp(my_strcpy(s4, "xyz"), "xyz") == 0);
}
