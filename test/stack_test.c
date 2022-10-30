#include <string.h>

#include "stack.h"

#include "test.h"

#define EQUALS(x, y) (strcmp(x, y) == 0)
#define LENGTH(arr) (sizeof(arr) / sizeof(*arr))

static char *strs[] = {"foo", "bar", "boom", "saas", "sees", "soos"};

void capped_test(void) {
  test("empty capped stack", stack_new_capped(0UL) == NULL);

  stack *cs = stack_new_capped(5);
  test("capped stack not NULL", cs != NULL);

  test("capped init size", stack_size(cs) == 0UL);

  for (size_t i = 0; i < 5; i++)
    test("capped push no error", stack_push(cs, strs[i]) >= 0);

  test("capped size full", stack_size(cs) == 5UL);

  test("capped push full", stack_push(cs, strs[5]) < 0);

  test("capped size full", stack_size(cs) == 5UL);

  for (size_t i = 0; i < 3; i++)
    test("capped peek equal", EQUALS((const char *)stack_peek(cs), strs[4]));

  for (size_t i = 4; i > 1; i--)
    test("capped pop equal", EQUALS((const char *)stack_pop(cs), strs[i]));

  test("capped clear exec", stack_clear(cs) >= 0);

  test("capped size empty", stack_size(cs) == 0UL);
  test("capped peek empty", stack_peek(cs) == NULL);
  test("capped pop empty", stack_pop(cs) == NULL);

  stack_destroy(cs);
}

void uncapped_test(void) {
  stack *us = stack_new_uncapped();
  test("uncapped stack not NULL", us != NULL);

  test("uncapped init size", stack_size(us) == 0UL);

  for (size_t i = 0; i < LENGTH(strs); i++)
    test("uncapped push no error", stack_push(us, strs[i]) >= 0);

  test("uncapped size", stack_size(us) == 6UL);

  for (size_t i = 0; i < 3; i++)
    test("uncapped peek equal", EQUALS((const char *)stack_peek(us), strs[5]));

  for (size_t i = 5; i > 3; i--)
    test("uncapped pop equal", EQUALS((const char *)stack_pop(us), strs[i]));

  for (size_t i = 0; i < 3; i++)
    test("uncapped peek equal", EQUALS((const char *)stack_peek(us), strs[3]));

  test("uncapped clear exec", stack_clear(us) >= 0);

  test("uncapped size empty", stack_size(us) == 0UL);
  test("uncapped peek empty", stack_peek(us) == NULL);
  test("uncapped pop empty", stack_pop(us) == NULL);

  stack_destroy(us);
}

int main(void) {
  capped_test();
  uncapped_test();

  return 0;
}
