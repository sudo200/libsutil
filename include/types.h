#ifndef ___TYPES_H__
#define ___TYPES_H__

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef int fd_t;
typedef int errno_t;

typedef void (*callback_t)(void);
typedef void * (*thread_worker_t)(void *);
typedef void (*sighandler_t)(int);
typedef void * (*alloc_t)(size_t);
typedef void (*dealloc_t)(void *);
typedef void * (*realloc_t)(void *, size_t);

typedef struct
{
  char **arr;
  size_t len;
}
string_array_t;

#endif//___TYPES_H__

