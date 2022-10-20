#include <assert.h>
#include <string.h>

#include "util.h"

#define equals(x, y, len) (memcmp(x, y, len) == 0)

static int int_arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9},
           int_arr_reverse[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};

int main(void) {
  assert(!equals(int_arr, int_arr_reverse, sizeof(int_arr)));
  assert(memrev(int_arr, 9, sizeof(*int_arr)) != NULL);
  assert(equals(int_arr, int_arr_reverse, sizeof(int_arr)));

  return 0;
}
