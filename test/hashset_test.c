#include <errno.h>
#include <string.h>

#include "hash.h"
#include "hashset.h"

#include "test.h"

#define len(arr) (sizeof(arr) / sizeof(*arr))
#define equals(x, y) (strcmp(x, y) == 0)
#define stra(str) (void *)str, (size_t)strlen((const char *)str)

static char *const strs[] = {"foo", "bar", "boom", "saas", "sees", "soos"};

static void add_NULL(void) {
  int ret = hashset_add(NULL, "", 1UL);
  ASSERT(ret < 0 && errno == EINVAL);
}

static void size_NULL(void) {
  int ret = hashset_clear(NULL);
  ASSERT(ret < 0 && errno == EINVAL);
}

static void clear_NULL(void) {
  int ret = hashset_clear(NULL);
  ASSERT(ret < 0 && errno == EINVAL);
}

static void remove_NULL(void) {
  void *ret = hashset_remove(NULL, "", 1UL);
  ASSERT(ret == NULL && errno == EINVAL);
}

static void contains_NULL(void) {
  bool ret = hashset_contains(NULL, "", 1UL);
  ASSERT(!ret && errno == EINVAL);
}

hashset *set;

static void new_non_NULL(void) {
  set = hashset_new(djb2);
  ASSERT(set != NULL);
}

static void check_empty_size(void) {
  size_t size = hashset_size(set);
  ASSERT(size == 0UL);
}

static void add_0(void) {
  int ret = hashset_add(set, stra(strs[0]));
  ASSERT(ret >= 0);
}

static void add_1(void) {
  int ret = hashset_add(set, stra(strs[1]));
  ASSERT(ret >= 0);
}

static void add_2(void) {
  int ret = hashset_add(set, stra(strs[2]));
  ASSERT(ret >= 0);
}

static void check_after_add(void) {
  assert(hashset_size(set) == 3UL);
  assert(hashset_contains(set, stra(strs[2])));
  assert(hashset_contains(set, stra(strs[0])));
  assert(hashset_contains(set, stra(strs[1])));
  ASSERT(true);
}

static void add_3(void) {
  int ret = hashset_add(set, stra(strs[3]));
  ASSERT(ret >= 0);
}

static void add_4(void) {
  int ret = hashset_add(set, stra(strs[4]));
  ASSERT(ret >= 0);
}

static void add_5(void) {
  int ret = hashset_add(set, stra(strs[5]));
  ASSERT(ret >= 0);
}

static void check_size(void) {
  size_t ret = hashset_size(set);
  ASSERT(ret == 6UL);
}

static void cb_func(void *item, size_t size, void *pipe) {
  size_t *i = (size_t *)pipe;
  const char *str = (const char *)item;
  puts(str);

  ++*i;
  for (size_t j = 0UL; j < len(strs); j++)
    if (equals(strs[j], str))
      return;
  assert(false);
}

static void foreach (void) {
  size_t i = 0UL;
  int ret = hashset_foreach(set, cb_func, &i);
  assert(ret >= 0);
  ASSERT(i == 6UL);
}

int main(void) {
  RUN_TEST(add_NULL);
  RUN_TEST(size_NULL);
  RUN_TEST(clear_NULL);
  RUN_TEST(remove_NULL);
  RUN_TEST(contains_NULL);

  RUN_TEST(new_non_NULL);
  RUN_TEST(check_empty_size);
  RUN_TEST(add_0);
  RUN_TEST(add_1);
  RUN_TEST(add_2);
  RUN_TEST(check_after_add);
  RUN_TEST(add_3);
  RUN_TEST(add_4);
  RUN_TEST(add_5);
  RUN_TEST(check_size);
  RUN_TEST(foreach);
  hashset_destroy(set);

  return 0;
}
