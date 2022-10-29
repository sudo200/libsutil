#include <string.h>

#define EQUALS(x, y) (strcmp(x, y) == 0)

#include "arraylist.h"
#include "dmem.h"

#include "test.h"

static char *strs[] = {"foo", "bar", "boom", "saas", "sees", "soos"};

static size_t i = 0;

static void cb_function(void *ptr) {
  test("foreach cb_function equals", EQUALS((const char *)ptr, strs[i++]));
}

#include <stdio.h>

int main() {
  test("add NULL pointer", arraylist_add(NULL, "") < 0);
  test("addall NULL pointer", arraylist_addall(NULL, NULL, 3) < 0);

  arraylist *list = arraylist_new();
  assert(list != NULL);

  test("empty element", arraylist_get(list, 0) == NULL); // Should be empty at first
  test("empty len", arraylist_length(list) == 0);

  test("add 0", arraylist_add(list, strs[0]) >= 0);
  test("add 1", arraylist_add(list, strs[1]) >= 0);
  test("add 2", arraylist_add(list, strs[2]) >= 0);

  test("length == 3", arraylist_length(list) == 3);
  test("list[3] == NULL", arraylist_get(list, 3) == NULL);

  test("add 3", arraylist_add(list, strs[3]) >= 0);
  test("add rest", arraylist_addall(list, (void **)(strs + 4), 2) >= 0);

  test("length == 6", arraylist_length(list) == 6);
  test("foreach exec", arraylist_foreach(list, cb_function) >= 0);

  test("remove 5", EQUALS(arraylist_remove(list, 5), strs[5]));
  test("remove 0", EQUALS(arraylist_remove(list, 0), strs[0]));
  i = 1;
  test("foreach exec", arraylist_foreach(list, cb_function) >= 0);

  test("insert 0", arraylist_insert(list, strs[0], 0) >= 0);
  i = 0;
  test("foreach exec", arraylist_foreach(list, cb_function) >= 0);

  test("clear", arraylist_clear(list) == 0);

  test("length == 0", arraylist_length(list) == 0);
  test("list empty", arraylist_get(list, 0) == NULL);

  arraylist_destroy(list);
  return 0;
}
