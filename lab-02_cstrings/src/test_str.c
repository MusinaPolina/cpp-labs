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


void test_strcat() {
  assert(my_strcat("abc", "defg") == (char*)"abcdefg");
  char *emp = "";
  assert(my_strcat(emp, "") == (char*)"");
  assert(my_strcat(emp, "abc") == (char*)"abc");
  assert(my_strcat("xxx", "") == (char*)"xxx");
}


void test_strcpy() {
  char *emp = "";
  assert(my_strcpy(emp, "") == (char*)"");
  assert(my_strcpy(emp, "abc") == (char*)"abc");
  assert(my_strcpy("zzz", "") == (char*)"");
  assert(my_strcpy("aaaaa", "xyz") == (char*)"xyz");
}
