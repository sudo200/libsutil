#ifndef ___TYPES_H__
#define ___TYPES_H__

#include <stdint.h>
#include <stdbool.h>

typedef int fd_t;
typedef int errno_t;
typedef void (*callback_t)(void);
typedef void * (*thread_worker_t)(void *);
typedef void (*sighandler_t)(int);
typedef struct
{
  char **arr;
  size_t len;
}
string_array_t;

#endif//___TYPES_H__

