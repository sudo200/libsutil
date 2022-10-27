#ifndef ___ARRAYLIST_H__
#define ___ARRAYLIST_H__

#include <unistd.h>

#include "types.h"

/**
 * A struct resembling a
 * child process.
 */
typedef struct {
  /**
   * The PID of the child process.
   */
  pid_t pid;

  /**
   * The filedescriptor
   * of the child process'
   * standard input.
   */
  fd_t stdin;

  /**
   * The filedescriptor
   * of the child process'
   * standard output.
   */
  fd_t stdout;

  /**
   * The filedescriptor
   * of the child process'
   * standard error.
   */
  fd_t stderr;
} process;

/**
 * Spawns a new child process with the given arguments and environment,
 * and stdin, stdout and stderr redirected into pipes for communication.
 *
 * @param proc The pointer to the process struct to write fds and pid into.
 * @param file The full path to the process executable.
 * @param argv The process' arguments, or default if NULL.
 * @param envp The process' environment, or the parent's environment if NULL.
 * @return The child's PID, or a negative value if an error occured.
 *
 * @see execve
 */
pid_t spawn(process *proc, const char *file, char *const *argv,
            char *const *envp);

/**
 * Reverses the order of elements in memory.
 *
 * @param arr The memory area to reverse.
 * @param nitems The amount of items in the area.
 * @param size The size in bytes of an item.
 * @return a pointer to arr, or NULL if an error occured.
 */
void *memrev(void *arr, size_t nitems, size_t size);

#endif //___ARRAYLIST_H__
