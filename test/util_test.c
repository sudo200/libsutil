#include <stdio.h>
#include <string.h>

#include "util.h"

#include "test.h"

#define equals(x, y, len) (memcmp(x, y, len) == 0)

static int int_arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9},
           int_arr_reverse[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};

static char *text = "Hello!";

int main(void) {
  test("arrays not equal", !equals(int_arr, int_arr_reverse, sizeof(int_arr)));
  test("memrev exec", memrev(int_arr, 9, sizeof(*int_arr)) != NULL);
  test("arrays equal", equals(int_arr, int_arr_reverse, sizeof(int_arr)));

  process proc;
  char buffer[0xFF];
  int nbytes;
  test("spawn successful", spawn(&proc, "/bin/sh", NULL, NULL) >= 0);

  dprintf(proc.stdin, "echo \"%s\"\n", text);

  test("read successful", (nbytes = read(proc.stdout, buffer, sizeof(buffer))) >= 0);

  test("output as expected", equals(buffer, text, strlen(text)));

  return 0;
}
