#include <errno.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#include "dmem.h"
#include "util.h"

#define equal(x, y) (strcmp(x, y) == 0)

extern char **environ;

pid_t spawn(process *proc, const char *file, char *const *argv,
            char *const *envp) {
  fd_t _stdin[2], _stdout[2], _stderr[2];
  if (argv == NULL) {
    char *const _argv[] = {(char *)file, NULL};
    argv = _argv;
  }
  if (envp == NULL)
    envp = environ;

  if (pipe(_stdin) == -1)
    return -1;
  if (pipe(_stdout) == -1)
    return -1;
  if (pipe(_stderr) == -1)
    return -1;

  pid_t pid = fork();
  if (pid == -1)
    return -1;

  if (pid == 0) // Child
  {
    dup2(_stdin[0], STDIN_FILENO);
    dup2(_stdout[1], STDOUT_FILENO);
    dup2(_stderr[1], STDERR_FILENO);

    close(_stdin[0]);
    close(_stdin[1]);
    close(_stdout[0]);
    close(_stdout[1]);
    close(_stderr[0]);
    close(_stderr[1]);

    if (execve(file, argv, envp) == -1) {
      _exit(1);
      return -1;
    } // Should never be reached
    return 0;
  } else // Parent
  {
    close(_stdin[0]);
    close(_stdout[1]);
    close(_stderr[1]);

    proc->pid = pid;
    proc->stdin_ = _stdin[1];
    proc->stdout_ = _stdout[0];
    proc->stderr_ = _stderr[0];
    return pid;
  }
}

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

int setsignal(int signum, sighandler_t handler) {
  const struct sigaction action = {
      .sa_handler = handler,
  };
  return sigaction(signum, &action, NULL);
}

FILE *fopenor(const char *file, const char *modes, FILE *stream) {
  if (file == NULL)
    return NULL;

  if (equal(file, "-"))
    return stream;

  return fopen(file, modes);
}

int memcmp_secure(const void *ptr1, const void *ptr2, size_t num) {
  const uint8_t *p1 = (const uint8_t *)ptr1;
  const uint8_t *p2 = (const uint8_t *)ptr2;
  uint8_t result = 0;
  size_t i;
  for (i = 0; i < num; i++)
    result |= p1[i] ^ p2[i];
  return result;
}
