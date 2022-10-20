#include <errno.h>
#include <string.h>

#include "dmem.h"
#include "util.h"

void *memrev(void *arr, size_t nitems, size_t size) {
  if (nitems == 0UL || size == 0UL) {
    errno = EINVAL;
    return NULL;
  }

  void *buffer = ualloc(size);
  if (buffer == NULL) {
    errno = ENOMEM;
    return NULL;
  }

  size_t i = nitems - 1, j = 0;
  while (j < i) {
    memcpy(buffer, ((uint8_t *)arr) + (j * size), size);
    memcpy(((uint8_t *)arr) + (j * size), ((uint8_t *)arr) + (i * size), size);
    memcpy(((uint8_t *)arr) + (i * size), buffer, size);
    j++;
    i--;
  }
  ufree(buffer);

  return arr;
}
