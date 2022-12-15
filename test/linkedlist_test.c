#include <string.h>

#include "dmem.h"

#include "linkedlist.h"
#include "test.h"

#define EQUALS(x, y) (strcmp(x, y) == 0)
#define MEMEQUALS(x, y, len) (memcmp(x, y, len) == 0)

static int i = 0;

void cb_function(void *item, void *pipe) {
  assert(EQUALS((const char *)item, ((char **)pipe)[i++]));
}

char *strs[] = {"foo", "bar", "boom", "saas", "sees", "soos"};

linkedlist *list;

void add_NULL(void) { ASSERT(linkedlist_add(NULL, "")); }

void addall_NULL(void) { ASSERT(linkedlist_addall(NULL, NULL, 3)); }

void new_non_NULL(void) {
  list = linkedlist_new();
  ASSERT(list != NULL);
}

void empty_after_creation(void) {
  assert(linkedlist_length(list) == 0);
  ASSERT(linkedlist_get(list, 0) == NULL);
}

void add_0(void) {
  int ret = linkedlist_add(list, strs[0]);
  ASSERT(ret >= 0);
}

void add_1(void) {
  int ret = linkedlist_add(list, strs[1]);
  ASSERT(ret >= 0);
}

void add_2(void) {
  int ret = linkedlist_add(list, strs[2]);
  ASSERT(ret >= 0);
}

void check_after_add(void) {
  assert(linkedlist_length(list) == 3);
  ASSERT(linkedlist_get(list, 3) == NULL);
}

void addall(void) {
  int ret = linkedlist_addall(list, (void **)(strs + 3), 3);
  ASSERT(ret >= 0);
}

void confirm_length(void) { ASSERT(linkedlist_length(list) == 6); }

void **arr;

void to_array_not_NULL(void) {
  arr = linkedlist_to_array(list);
  ASSERT(arr != NULL);
}

void to_array_equal(void) {
  ASSERT(MEMEQUALS(arr, strs, sizeof(*arr) * linkedlist_length(list)));
  ufree(arr);
}

void foreach_0(void) {
  int ret = linkedlist_foreach(list, cb_function, strs);
  ASSERT(ret >= 0);
}

void remove_5(void) {
  void *item = linkedlist_remove(list, 5);
  ASSERT(EQUALS(item, strs[5]));
}

void remove_0(void) {
  void *item = linkedlist_remove(list, 0);
  ASSERT(EQUALS(item, strs[0]));
}

void foreach_1(void) {
  i = 1;
  int ret = linkedlist_foreach(list, cb_function, strs);
  ASSERT(ret >= 0);
}

void insert(void) {
  int ret = linkedlist_insert(list, strs[0], 0);
  ASSERT(ret >= 0);
}

void foreach_2(void) {
  i = 0;
  int ret = linkedlist_foreach(list, cb_function, strs);
  ASSERT(ret >= 0);
}

void clear(void) {
  int ret = linkedlist_clear(list);
  ASSERT(ret >= 0);
}

void empty_after_clear(void) {
  assert(linkedlist_length(list) == 0);
  ASSERT(linkedlist_get(list, 0) == NULL);
}

int main(void) {
  RUN_TEST(add_NULL);
  RUN_TEST(addall_NULL);
  RUN_TEST(new_non_NULL);
  RUN_TEST(empty_after_creation);
  RUN_TEST(add_0);
  RUN_TEST(add_1);
  RUN_TEST(add_2);
  RUN_TEST(check_after_add);
  RUN_TEST(addall);
  RUN_TEST(confirm_length);
  RUN_TEST(to_array_not_NULL);
  RUN_TEST(to_array_equal);
  RUN_TEST(foreach_0);
  RUN_TEST(remove_5);
  RUN_TEST(remove_0);
  RUN_TEST(foreach_1);
  RUN_TEST(insert);
  RUN_TEST(foreach_2);
  RUN_TEST(clear);
  RUN_TEST(empty_after_clear);
  linkedlist_destroy(list);
  return 0;
}
