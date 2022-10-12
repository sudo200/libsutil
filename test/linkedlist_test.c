#include <assert.h>
#include <string.h>

#include <stdio.h>

#include "linkedlist.h"

#define EQUALS(x, y)  (strcmp(x, y) == 0)

static int i = 0;
static char *strs[] = {
  "foo",
  "bar",
  "boom",
  "saas",
  "sees",
  "soos"
};

void cb_function(void *item)
{
  assert(EQUALS((const char *) item, strs[i++]));
}

int main(void)
{
  linkedlist *list = linkedlist_new();
  assert(list != NULL);

  assert(linkedlist_length(list) == 0);
  assert(linkedlist_get(list, 0) == NULL);

  assert(linkedlist_add(list, strs[0]) >= 0);

  assert(linkedlist_foreach(list, cb_function) >= 0);
  i = 0;

  assert(linkedlist_add(list, strs[1]) >= 0);
  assert(linkedlist_add(list, strs[2]) >= 0);

  assert(linkedlist_length(list) == 3);

  assert(linkedlist_addall(list, (void **)(strs + 3), 3) >= 0);

  assert(EQUALS(linkedlist_get(list, 1), strs[1]));
  assert(EQUALS(linkedlist_get(list, 5), strs[5]));
  assert(linkedlist_foreach(list, cb_function) >= 0);

  assert(linkedlist_length(list) == 6);

  assert(linkedlist_clear(list) >= 0);

  assert(linkedlist_add(list, strs[5]) >= 0);
  assert(linkedlist_insertall(list, (void **)strs + 1, 4, 0) >= 0);
  assert(linkedlist_insert(list, strs[0], 0) >= 0);

  assert(linkedlist_insert(list, strs[0], 0) >= 0);
  assert(EQUALS((const char *) linkedlist_remove(list, 0), strs[0]));

  i = 0;
  assert(linkedlist_foreach(list, cb_function) >= 0);

  linkedlist_destroy(list);
  return 0;
}

