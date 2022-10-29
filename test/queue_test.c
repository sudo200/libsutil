#include <string.h>

#include "queue.h"

#include "test.h"

#define equals(x, y) (strcmp(x, y) == 0)

static char *strs[] = {"foo", "bar", "boom", "saas", "sees", "soos"};

static const char *const msgs[][2] = {
  {"new_uncapped NULL", "new_capped NULL"},
  {"uncapped add 0", "capped add 0"},
  {"uncapped add 1", "capped add 1"},
  {"uncapped add 2", "capped add 2"},
  {"uncapped addall rest", "capped addall rest"},
  {"uncapped peek equals", "capped peek equals"},
  {"uncapped poll equals", "capped poll equals"}
};

int main(void) {
  test("add NULL pointer", queue_add(NULL, NULL) == -1);
  test("addall NULL pointer", queue_addall(NULL, NULL, 1, false) == -1);
  test("new_capped(0) == NULL", queue_new_capped(0) == NULL);

  for (size_t n = 0; n < 2; n++) {
    queue *q = (n == 1) ? queue_new_uncapped() : queue_new_capped(6);
    test(msgs[0][n], q != NULL);

    test(msgs[1][n], queue_add(q, strs[0]) >= 0);
    test(msgs[2][n], queue_add(q, strs[1]) >= 0);
    test(msgs[3][n], queue_add(q, strs[2]) >= 0);

    test(msgs[4][n], queue_addall(q, (void **)strs + 3, 3, false) >= 0);

    for (size_t i = 0; i < 3; i++)
      test(msgs[5][n], equals((const char *)queue_peek(q), strs[0]));

    for (size_t i = 0; i < 6; i++)
      test(msgs[6][n], equals((const char *)queue_poll(q), strs[i]));

    queue_destroy(q);
  }
  return 0;
}
