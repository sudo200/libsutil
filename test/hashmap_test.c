#include <errno.h>
#include <string.h>

#include "hash.h"
#include "hashmap.h"

#include "test.h"

#define len(arr) (sizeof(arr) / sizeof(*arr))
#define equals(x, y) (strcmp(x, y) == 0)
#define stra(str) (void *)str, (size_t)strlen((const char *)str)

static char *const strs[][2] = {{"foo", "haha"},  {"bar", "hehe"},
                                {"boom", "hihi"}, {"saas", "hoho"},
                                {"sees", "huhu"}, {"soos", "lol"}};

static void put_NULL(void) {
  errno = 0;
  int ret = hashmap_put(NULL, NULL, 0UL, NULL);
  ASSERT(ret < 0 && errno == EINVAL);
}

static void get_NULL(void) {
  errno = 0;
  void *ret = hashmap_get(NULL, NULL, 0UL);
  ASSERT(ret == NULL && errno == EINVAL);
}

static void size_NULL(void) {
  errno = 0;
  size_t ret = hashmap_size(NULL);
  ASSERT(ret == 0UL && errno == EINVAL);
}

static void contains_key_NULL(void) {
  errno = 0;
  bool ret = hashmap_contains_key(NULL, NULL, 0UL);
  ASSERT(ret == false && errno == EINVAL);
}

static void foreach_NULL(void) {
  errno = 0;
  int ret = hashmap_foreach(
      NULL, (void (*)(void *, size_t, void *, void *))NULL, NULL);
  ASSERT(ret < 0 && errno == EINVAL);
}

static void clear_NULL(void) {
  errno = 0;
  int ret = hashmap_clear(NULL);
  ASSERT(ret < 0 && errno == EINVAL);
}

static void remove_NULL(void) {
  errno = 0;
  void *ret = hashmap_remove(NULL, NULL, 0UL);
  ASSERT(ret == NULL && errno == EINVAL);
}

hashmap_t *map;

static void new_non_NULL(void) {
  map = hashmap_new(fnv1a);
  ASSERT(map != NULL);
}

static void check_empty_size(void) {
  size_t size = hashmap_size(map);
  ASSERT(size == 0UL);
}

static void put_0(void) {
  int ret = hashmap_put(map, stra(strs[0][0]), strs[0][1]);
  ASSERT(ret >= 0);
}

static void put_1(void) {
  int ret = hashmap_put(map, stra(strs[1][0]), strs[1][1]);
  ASSERT(ret >= 0);
}

static void put_2(void) {
  int ret = hashmap_put(map, stra(strs[2][0]), strs[2][1]);
  ASSERT(ret >= 0);
}

static void check_after_add(void) {
  assert(hashmap_size(map) == 3UL);
  assert(hashmap_contains_key(map, stra(strs[0][0])) == true);
  assert(hashmap_contains_key(map, stra(strs[1][0])) == true);
  assert(hashmap_contains_key(map, stra(strs[2][0])) == true);
  assert(hashmap_contains_key(map, stra(strs[5][0])) == false);
  assert(equals((const char *)hashmap_get(map, stra(strs[0][0])), strs[0][1]));
  assert(equals((const char *)hashmap_get(map, stra(strs[1][0])), strs[1][1]));
  assert(equals((const char *)hashmap_get(map, stra(strs[2][0])), strs[2][1]));
  ASSERT(true);
}

static void put_3(void) {
  int ret = hashmap_put(map, stra(strs[3][0]), strs[3][1]);
  ASSERT(ret >= 0);
}

static void put_4(void) {
  int ret = hashmap_put(map, stra(strs[4][0]), strs[4][1]);
  ASSERT(ret >= 0);
}

static void put_5(void) {
  int ret = hashmap_put(map, stra(strs[5][0]), strs[5][1]);
  ASSERT(ret >= 0);
}

static void check_size(void) {
  size_t ret = hashmap_size(map);
  ASSERT(ret >= 6UL);
}

static void cb_func(void *key, size_t keysize, void *value, void *pipe) {
  size_t *i = (size_t *)pipe;
  const char *keystr = (const char *)key;
  const char *valuestr = (const char *)value;

  ++*i;
  bool key_found = false;
  for (size_t j = 0UL; j < 6UL; j++)
    if (equals(keystr, strs[j][0]))
      key_found = true;
  assert(key_found);

  bool value_found = false;
  for (size_t j = 0UL; j < 6UL; j++)
    if (equals(valuestr, strs[j][1]))
      value_found = true;
  assert(value_found);
}

static void foreach (void) {
  size_t i = 0UL;
  int ret = hashmap_foreach(map, cb_func, &i);
  assert(ret >= 0);
  ASSERT(i == 6UL);
}

static void remove_() {
  void *ret = hashmap_remove(map, stra(strs[4][0]));
  assert(ret != NULL);
  assert(equals((const char *)ret, strs[4][1]));

  assert(hashmap_get(map, stra(strs[4][0])) == NULL && errno == ENOENT);
  assert(hashmap_contains_key(map, stra(strs[4][0])) == false);
  ASSERT(true);
}

static void clear(void) {
  int ret = hashmap_clear(map);
  assert(ret >= 0);
  assert(hashmap_contains_key(map, stra(strs[0][0])) == false);
  assert(hashmap_contains_key(map, stra(strs[1][0])) == false);
  assert(hashmap_contains_key(map, stra(strs[2][0])) == false);
  assert(hashmap_contains_key(map, stra(strs[3][0])) == false);
  assert(hashmap_contains_key(map, stra(strs[4][0])) == false);
  assert(hashmap_contains_key(map, stra(strs[5][0])) == false);
  assert(hashmap_size(map) == 0UL);
  ASSERT(true);
}

int main(void) {
  RUN_TEST(put_NULL);
  RUN_TEST(get_NULL);
  RUN_TEST(size_NULL);
  RUN_TEST(contains_key_NULL);
  RUN_TEST(foreach_NULL);
  RUN_TEST(clear_NULL);
  RUN_TEST(remove_NULL);

  RUN_TEST(new_non_NULL);
  RUN_TEST(check_empty_size);
  RUN_TEST(put_0);
  RUN_TEST(put_1);
  RUN_TEST(put_2);
  RUN_TEST(check_after_add);
  RUN_TEST(put_3);
  RUN_TEST(put_4);
  RUN_TEST(put_5);
  RUN_TEST(check_size);
  RUN_TEST(foreach);
  RUN_TEST(remove_);
  RUN_TEST(clear);

  hashmap_destroy(map);

  return 0;
}
