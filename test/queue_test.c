#include <assert.h>
#include <string.h>

#include "queue.h"

int main(void)
{
  assert(queue_add(NULL, NULL) == -1);
  assert(queue_addall(NULL, NULL, 1, false) == -1);

  return 0;
}

