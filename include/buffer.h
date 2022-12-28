#ifndef ___BUFFER_H__
#define ___BUFFER_H__

#include "types.h"

typedef struct buffer buffer_t;

buffer_t *buffer_new(size_t len);

buffer_t *buffer_new_from_string(const char *str);

buffer_t *buffer_new_from_pointer(const void *buf, size_t len);

void *buffer_get(buffer_t *buf);

size_t buffer_size(buffer_t *buf);

void buffer_destroy(buffer_t *buffer);

#endif //___BUFFER_H__
