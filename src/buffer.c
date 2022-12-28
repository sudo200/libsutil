#include <errno.h>
#include <string.h>

#include "buffer.h"

#include "dmem.h"

struct buffer {
  void *buffer;
  size_t size;
};

buffer_t *buffer_new(size_t len) {
  buffer_t *buf = (buffer_t *)ualloc(sizeof(*buf));

  if (buf == NULL) {
    errno = ENOMEM;
    return NULL;
  }

  if ((buf->buffer = ualloc(len)) == NULL) {
    errno = ENOMEM;
    return NULL;
  }
  buf->size = len;

  return buf;
}

buffer_t *buffer_new_from_pointer(const void *buffer, size_t len) {
  buffer_t *buf = buffer_new(len);

  if (buf == NULL)
    return NULL;

  memcpy(buf->buffer, buffer, buf->size = len);

  return buf;
}

buffer_t *buffer_new_from_string(const char *str) {
  if (str == NULL)
    return NULL;

  return buffer_new_from_pointer(str, strlen(str) + 1);
}

void *buffer_get(buffer_t *buf) {
  if (buf == NULL) {
    errno = EINVAL;
    return NULL;
  }

  return buf->buffer;
}

size_t buffer_size(buffer_t *buf) {
  if (buf == NULL) {
    errno = EINVAL;
    return 0UL;
  }

  return buf->size;
}

void buffer_destroy(buffer_t *buffer) {
  if (buffer->buffer != NULL)
    ufree(buffer->buffer);
  ufree(buffer);
}
