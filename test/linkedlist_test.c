#include <string.h>

#include "dmem.h"

#include "linkedlist.h"
#include "test.h"

#define EQUALS(x, y) (strcmp(x, y) == 0)
#define MEMEQUALS(x, y, len) (memcmp(x, y, len) == 0)

static int i = 0;

void cb_function(void *item, void *pipe) {
  test("foreach cb_function equals",
       EQUALS((const char *)item, ((char **)pipe)[i++]));
}

int main(void) {
  char *strs[] = {"foo", "bar", "boom", "saas", "sees", "soos"};

  linkedlist *list = linkedlist_new();
  test("new != NULL", list != NULL);

  test("empty length", linkedlist_length(list) == 0);
  test("empty element", linkedlist_get(list, 0) == NULL);

  test("add 0", linkedlist_add(list, strs[0]) >= 0);

  test("foreach exec", linkedlist_foreach(list, cb_function, strs) >= 0);
  i = 0;

  test("add 1", linkedlist_add(list, strs[1]) >= 0);
  test("add 2", linkedlist_add(list, strs[2]) >= 0);

  test("add 3", linkedlist_length(list) == 3);

  test("add rest", linkedlist_addall(list, (void **)(strs + 3), 3) >= 0);

  test("list[1] == strs[1]", EQUALS(linkedlist_get(list, 1), strs[1]));
  test("list[5] == strs[5]", EQUALS(linkedlist_get(list, 5), strs[5]));
  test("foreach exec", linkedlist_foreach(list, cb_function, strs) >= 0);

  void **arr = linkedlist_to_array(list);
  test("to_array not NULL", arr != NULL);
  test("to_array equal",
       MEMEQUALS(arr, strs, sizeof(*arr) * linkedlist_length(list)));
  ufree(arr);

  test("length == 6", linkedlist_length(list) == 6);

  test("clear exec", linkedlist_clear(list) >= 0);

  test("add 5", linkedlist_add(list, strs[5]) >= 0);
  test("insert (1-4) @ 0",
       linkedlist_insertall(list, (void **)strs + 1, 4, 0) >= 0);
  test("insert 0 @ 0", linkedlist_insert(list, strs[0], 0) >= 0);

  test("insert 0 @ 0", linkedlist_insert(list, strs[0], 0) >= 0);
  test("remove 0", EQUALS((const char *)linkedlist_remove(list, 0), strs[0]));

  i = 0;
  test("foreach exec", linkedlist_foreach(list, cb_function, strs) >= 0);

  linkedlist_destroy(list);
  return 0;
}
