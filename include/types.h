#ifndef ___TYPES_H__
#define ___TYPES_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * Datatype of a single byte.
 */
typedef uint8_t byte;

/**
 * Datatype of file descriptors.
 */
typedef int fd_t;

/**
 * Datatype of the errno variable.
 */
typedef int errno_t;

/**
 * A function getting nothing and returning nothing.
 * Often used as a callback.
 */
typedef void (*callback_t)(void);

/**
 * A function executed in a POSIX thread.
 */
typedef void *(*thread_worker_t)(void *);

/**
 * A callback function for a signal.
 */
typedef void (*sighandler_t)(int);

/**
 * A function for allocating memory dynamically.
 */
typedef void *(*alloc_t)(size_t);

/**
 * A function for deallocating dynamic memory.
 */
typedef void (*dealloc_t)(void *);

/**
 * A function for resizing a dynamic memory area.
 */
typedef void *(*realloc_t)(void *, size_t);

/**
 * A struct describing an array of strings.
 */
typedef struct {
  char **arr;
  size_t len;
} string_array_t;

#endif //___TYPES_H__
