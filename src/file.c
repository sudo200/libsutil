#include <errno.h>
#include <string.h>

#include "dmem.h"
#include "file.h"

int fpeek(FILE *stream) {
  if (stream == NULL) {
    errno = EBADF;
    return EOF;
  }

  return ungetc(fgetc(stream), stream);
}

char *fpeeks(FILE *stream, size_t n) {
  if (stream == NULL) {
    errno = EBADF;
    return NULL;
  }

  char *buffer = (char *)ualloc((n + 1) * sizeof(char));
  if (buffer == NULL)
    return NULL;

  for (size_t i = 0; i < n; i++)
    if ((buffer[i] = fgetc(stream)) == EOF)
      return NULL;
  buffer[n] = '\0';

  for (size_t i = n; i > 0; i--)
    ungetc(buffer[i - 1], stream);

  return buffer;
}

size_t fsize(FILE *stream) {
  if (stream == NULL) {
    errno = EBADF;
    return 0;
  }
  fpos_t pos;
  size_t start = 0, end = 0;
  fgetpos(stream, &pos);
  fseek(stream, 0L, SEEK_SET);
  start = ftell(stream);
  fseek(stream, 0L, SEEK_END);
  end = ftell(stream);
  fsetpos(stream, &pos);
  return end - start;
}
