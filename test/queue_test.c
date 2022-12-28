#include <string.h>

#include "queue.h"

#include "test.h"

#define equals(x, y) (strcmp(x, y) == 0)
#define len(arr) (sizeof(arr) / sizeof(*arr))

static char *strs[] = {"foo", "bar", "boom", "saas", "sees", "soos"};

static void add_NULL(void) {
  int ret = queue_add(NULL, NULL);
  ASSERT(ret < 0);
}

static void addall_NULL(void) {
  int ret = queue_addall(NULL, NULL, 0UL, false);
  ASSERT(ret < 0);
}

static void peek_NULL(void) {
  void *ret = queue_peek(NULL);
  ASSERT(ret == NULL);
}

static void poll_NULL(void) {
  void *ret = queue_poll(NULL);
  ASSERT(ret == NULL);
}

static void zero_length_capped_NULL(void) {
  queue_t *q = queue_new_capped(0UL);
  ASSERT(q == NULL);
}

queue_t *q;

static void uncapped_non_NULL(void) {
  q = queue_new_uncapped();
  ASSERT(q != NULL);
}

static void uncapped_add_0(void) {
  int ret = queue_add(q, strs[0]);
  ASSERT(ret >= 0);
}

static void uncapped_add_1(void) {
  int ret = queue_add(q, strs[1]);
  ASSERT(ret >= 0);
}

static void uncapped_add_2(void) {
  int ret = queue_add(q, strs[2]);
  ASSERT(ret >= 0);
}

static void uncapped_peek(void) {
  const char *str = (const char *)queue_peek(q);

  assert(str != NULL);
  ASSERT(equals(str, strs[0]));
}

static void uncapped_addall(void) {
  int ret = queue_addall(q, (void **)strs + 3, 3UL, false);
  ASSERT(ret >= 0);
}

static void uncapped_poll(void) {
  for (size_t i = 0UL; i < len(strs); i++) {
    const char *ret = (const char *)queue_poll(q);
    assert(ret != NULL);
    assert(equals(strs[i], ret));
  }
  ASSERT(true);
}

static void capped_non_NULL(void) {
  q = queue_new_capped(len(strs));
  ASSERT(q != NULL);
}

static void capped_addall(void) {
  int ret = queue_addall(q, (void **)strs, len(strs) - 1, false);
  ASSERT(ret >= 0);
}

static void capped_peek(void) {
  const char *ret = (const char *)queue_peek(q);
  assert(ret != NULL);
  ASSERT(equals(strs[0], ret));
}

static void capped_add(void) {
  int ret = queue_add(q, strs[len(strs) - 1]);
  ASSERT(ret >= 0);
}

static void capped_full(void) {
  int ret = queue_add(q, strs[len(strs) - 1]);
  ASSERT(ret < 0);
}

static void capped_poll(void) {
  for (size_t i = 0UL; i < len(strs); i++) {
    const char *ret = (const char *)queue_poll(q);
    assert(ret != NULL);
    assert(equals(strs[i], ret));
  }
  ASSERT(true);
}

int main(void) {
  RUN_TEST(add_NULL);
  RUN_TEST(addall_NULL);
  RUN_TEST(peek_NULL);
  RUN_TEST(poll_NULL);
  RUN_TEST(zero_length_capped_NULL);

  RUN_TEST(uncapped_non_NULL);
  RUN_TEST(uncapped_add_0);
  RUN_TEST(uncapped_add_1);
  RUN_TEST(uncapped_add_2);
  RUN_TEST(uncapped_peek);
  RUN_TEST(uncapped_addall);
  RUN_TEST(uncapped_poll);
  queue_destroy(q);

  RUN_TEST(capped_non_NULL);
  RUN_TEST(capped_addall);
  RUN_TEST(capped_peek);
  RUN_TEST(capped_add);
  RUN_TEST(capped_full);
  RUN_TEST(capped_poll);
  queue_destroy(q);

  return 0;
}
