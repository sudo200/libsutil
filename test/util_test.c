#include <stdio.h>
#include <string.h>

#include "util.h"

#include "test.h"

#define equals(x, y, len) (memcmp(x, y, len) == 0)

static int int_arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9},
           int_arr_reverse[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};

static char *text = "Hello!";

void memrev_test(void) {
  assert(!equals(int_arr, int_arr_reverse, sizeof(int_arr)));
  void *ret = memrev(int_arr, 9, sizeof(*int_arr));
  assert(ret != NULL);
  ASSERT(equals(int_arr, int_arr_reverse, sizeof(int_arr)));
}

void spawn_test(void) {
  process proc;
  char buffer[0xFF];

  pid_t ret = spawn(&proc, "/bin/sh", NULL, NULL);

  assert(ret > 0);

  int nbytes = dprintf(proc.stdin_, "echo \"%s\"\n", text);
  assert(nbytes > 0);

  nbytes = read(proc.stdout_, buffer, sizeof(buffer));
  assert(nbytes > 0);

  ASSERT(equals(buffer, text, strlen(text)));
}

int main(void) {
  RUN_TEST(memrev_test);
  RUN_TEST(spawn_test);

  return 0;
}
