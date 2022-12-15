#include <string.h>

#include "stack.h"

#include "test.h"

#define EQUALS(x, y) (strcmp(x, y) == 0)
#define LENGTH(arr) (sizeof(arr) / sizeof(*arr))

static char *strs[] = {"foo", "bar", "boom", "saas", "sees", "soos"};

static void push_NULL(void) {
  int ret = stack_push(NULL, NULL);
  ASSERT(ret < 0);
}

stack *s;

static void uncapped_non_NULL(void) {
  s = stack_new_uncapped();
  ASSERT(s != NULL);
}

static void uncapped_check_empty_size(void) {
  size_t len = stack_size(s);
  ASSERT(len == 0UL);
}

static void uncapped_push(void) {
  for (size_t i = 0UL; i < LENGTH(strs); i++) {
    int ret = stack_push(s, strs[i]);
    assert(ret >= 0);
  }
  ASSERT(true);
}

static void uncapped_check_size(void) {
  size_t len = stack_size(s);
  ASSERT(len == LENGTH(strs));
}

static void uncapped_pop(void) {
  for (size_t i = LENGTH(strs) - 1; i >= 3; i--) {
    const char *ret = (const char *)stack_pop(s);
    assert(ret != NULL);
    assert(EQUALS(ret, strs[i]));
  }
  ASSERT(true);
}

static void uncapped_clear(void) {
  int ret = stack_clear(s);
  assert(ret >= 0);
  size_t len = stack_size(s);
  assert(len == 0UL);
  const char *str = (const char *)stack_pop(s);
  ASSERT(str == NULL);
}

static void capped_non_NULL(void) {
  s = stack_new_capped(LENGTH(strs));
  ASSERT(s != NULL);
}

static void capped_check_empty_size(void) {
  size_t len = stack_size(s);
  ASSERT(len == 0UL);
}

static void capped_push(void) {
  for (size_t i = 0UL; i < LENGTH(strs); i++) {
    int ret = stack_push(s, strs[i]);
    assert(ret >= 0);
  }
  ASSERT(true);
}

static void capped_check_size(void) {
  size_t len = stack_size(s);
  ASSERT(len == LENGTH(strs));
}

static void capped_check_full(void) {
  int ret = stack_push(s, strs[LENGTH(strs) - 1]);
  ASSERT(ret < 0);
}

static void capped_pop(void) {
  for (size_t i = LENGTH(strs) - 1; i >= 3; i--) {
    const char *ret = (const char *)stack_pop(s);
    assert(ret != NULL);
    assert(EQUALS(ret, strs[i]));
  }
  ASSERT(true);
}

static void capped_clear(void) {
  int ret = stack_clear(s);
  assert(ret >= 0);
  size_t len = stack_size(s);
  assert(len == 0UL);
  const char *str = (const char *)stack_pop(s);
  ASSERT(str == NULL);
}

int main(void) {
  RUN_TEST(push_NULL);

  RUN_TEST(uncapped_non_NULL);
  RUN_TEST(uncapped_check_empty_size);
  RUN_TEST(uncapped_push);
  RUN_TEST(uncapped_check_size);
  RUN_TEST(uncapped_pop);
  RUN_TEST(uncapped_clear);
  stack_destroy(s);

  RUN_TEST(capped_non_NULL);
  RUN_TEST(capped_check_empty_size);
  RUN_TEST(capped_push);
  RUN_TEST(capped_check_size);
  RUN_TEST(capped_check_full);
  RUN_TEST(capped_pop);
  RUN_TEST(capped_clear);
  stack_destroy(s);

  return 0;
}
