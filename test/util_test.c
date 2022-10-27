#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "util.h"

#define equals(x, y, len) (memcmp(x, y, len) == 0)

static int int_arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9},
           int_arr_reverse[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};

static char *text = "Hello!";

int main(void) {
  assert(!equals(int_arr, int_arr_reverse, sizeof(int_arr)));
  assert(memrev(int_arr, 9, sizeof(*int_arr)) != NULL);
  assert(equals(int_arr, int_arr_reverse, sizeof(int_arr)));

  process proc;
  char buffer[0xFF];
  int nbytes;
  assert(spawn(&proc, "/bin/sh", NULL, NULL) >= 0);

  dprintf(proc.stdin, "echo \"%s\"\n", text);

  assert((nbytes = read(proc.stdout, buffer, sizeof(buffer))) >= 0);

  assert(equals(buffer, text, strlen(text)));

  return 0;
}
