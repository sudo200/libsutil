#include <string.h>

#define EQUALS(x, y) (strcmp(x, y) == 0)
#define MEMEQUALS(x, y, len) (memcmp(x, y, len) == 0)

#include "arraylist.h"
#include "dmem.h"

#include "test.h"

static size_t i = 0;

static void cb_function(void *ptr, void *pipe) {
  assert(EQUALS((const char *)ptr, ((char **)pipe)[i++]));
}

char *strs[] = {"foo", "bar", "boom", "saas", "sees", "soos"};

void add_NULL(void) { ASSERT(arraylist_add(NULL, "") < 0); }

void addall_NULL(void) { ASSERT(arraylist_addall(NULL, NULL, 3) < 0); }

arraylist *list;

void new_non_NULL(void) {
  list = arraylist_new();
  ASSERT(list != NULL);
}

void empty_after_creation(void) {
  assert(arraylist_get(list, 0) == NULL);
  ASSERT(arraylist_length(list) == 0);
}

void add_0(void) {
  int ret = arraylist_add(list, strs[0]);
  ASSERT(ret >= 0);
}

void add_1(void) {
  int ret = arraylist_add(list, strs[1]);
  ASSERT(ret >= 0);
}

void add_2(void) {
  int ret = arraylist_add(list, strs[2]);
  ASSERT(ret >= 0);
}

void check_after_add() {
  assert(arraylist_length(list) == 3);
  ASSERT(arraylist_get(list, 3) == NULL);
}

void add_3(void) {
  int ret = arraylist_add(list, strs[3]);
  ASSERT(ret >= 0);
}

void addall(void) {
  int ret = arraylist_addall(list, (void **)(strs + 4), 2);
  ASSERT(ret >= 0)
}

void confirm_length(void) { ASSERT(arraylist_length(list) == 6); }

void **arr;

void to_array_not_NULL(void) {
  arr = arraylist_to_array(list);
  ASSERT(arr != NULL);
}

void to_array_equal(void) {
  ASSERT(MEMEQUALS(arr, strs, sizeof(*arr) * arraylist_length(list)));
  ufree(arr);
}

void foreach_0(void) {
  int ret = arraylist_foreach(list, cb_function, strs);
  ASSERT(ret >= 0);
}

void remove_5(void) {
  void *item = arraylist_remove(list, 5);
  ASSERT(EQUALS(item, strs[5]));
}

void remove_0(void) {
  void *item = arraylist_remove(list, 0);
  ASSERT(EQUALS(item, strs[0]));
}

void foreach_1(void) {
  i = 1;
  int ret = arraylist_foreach(list, cb_function, strs);
  ASSERT(ret >= 0);
}

void insert(void) {
  int ret = arraylist_insert(list, strs[0], 0);
  ASSERT(ret >= 0);
}

void foreach_2(void) {
  i = 0;
  int ret = arraylist_insert(list, strs[0], 0);
  ASSERT(ret >= 0);
}

void clear(void) {
  int ret = arraylist_clear(list);
  ASSERT(ret == 0);
}

void empty_after_clear(void) {
  assert(arraylist_length(list) == 0);
  ASSERT(arraylist_get(list, 0) == NULL);
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
  RUN_TEST(add_3);
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

  arraylist_destroy(list);
  return 0;
}
