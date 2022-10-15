#include <assert.h>
#include <string.h>

#include "queue.h"

#define equals(x, y)  (strcmp(x, y) == 0)

static char *strs[] = {
  "foo",
  "bar",
  "boom",
  "saas",
  "sees",
  "soos"
};

void queue_debug(queue *);

int main(void)
{
  assert(queue_add(NULL, NULL) == -1);
  assert(queue_addall(NULL, NULL, 1, false) == -1);
  assert(queue_new_capped(0) == NULL);

  for(size_t n = 0; n < 2; n++)
  {
    queue *q = (n == 1) ? queue_new_uncapped() : queue_new_capped(6);
    assert(q != NULL);

    assert(queue_add(q, strs[0]) >= 0);
    assert(queue_add(q, strs[1]) >= 0);
    assert(queue_add(q, strs[2]) >= 0);

    assert(queue_addall(q, (void **) strs + 3, 3, false) >= 0);

    for(size_t i = 0; i < 3; i++)
      assert(equals((const char *) queue_peek(q), strs[0]));

    for(size_t i = 0; i < 6; i++)
      assert(equals((const char *) queue_poll(q), strs[i]));
  
    queue_destroy(q);
  }
  return 0;
}

