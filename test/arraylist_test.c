#include <assert.h>
#include <string.h>

#define EQUALS(x, y) (strcmp(x, y) == 0)

#include "arraylist.h"
#include "dmem.h"

static char *strs[] = {"foo", "bar", "boom", "saas", "sees", "soos"};

static size_t i = 0;

static void cb_function(void *ptr) {
  assert(EQUALS((const char *)ptr, strs[i++]));
}

#include <stdio.h>

int main() {
  assert(arraylist_add(NULL, "") < 0);
  assert(arraylist_addall(NULL, NULL, 3) < 0);

  arraylist *list = arraylist_new();
  assert(list != NULL);

  assert(arraylist_get(list, 0) == NULL); // Should be empty at first
  assert(arraylist_length(list) == 0);

  assert(arraylist_add(list, strs[0]) >= 0);
  assert(arraylist_add(list, strs[1]) >= 0);
  assert(arraylist_add(list, strs[2]) >= 0);

  assert(arraylist_length(list) == 3);
  assert(arraylist_get(list, 3) == NULL);

  assert(arraylist_add(list, strs[3]) >= 0);
  assert(arraylist_addall(list, (void **)(strs + 4), 2) >= 0);

  assert(arraylist_length(list) == 6);
  assert(arraylist_foreach(list, cb_function) >= 0);

  assert(EQUALS(arraylist_remove(list, 5), strs[5]));
  assert(EQUALS(arraylist_remove(list, 0), strs[0]));
  i = 1;
  assert(arraylist_foreach(list, cb_function) >= 0);

  assert(arraylist_insert(list, strs[0], 0) >= 0);
  i = 0;
  assert(arraylist_foreach(list, cb_function) >= 0);

  assert(arraylist_clear(list) == 0);

  assert(arraylist_length(list) == 0);
  assert(arraylist_get(list, 0) == NULL);

  arraylist_destroy(list);
  return 0;
}
