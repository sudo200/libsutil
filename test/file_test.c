#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define EQUALS(x, y) (strcmp(x, y) == 0)

#include "dmem.h"
#include "file.h"

extern int chdir(const char *);

int main(int argc, char **argv) {
  *strrchr(argv[0], '/') = '\0';
  chdir(argv[0]);

  FILE *testfile = fopen("test_file.txt", "w+");
  assert(testfile != NULL);

  size_t written = fwrite("Hello there!\n", 1, 13, testfile);
  assert(written == fsize(testfile));

  fseek(testfile, 0L, SEEK_SET);

  assert(fpeek(testfile) == 'H');
  assert(fpeek(testfile) == 'H');
  fgetc(testfile);
  assert(fpeek(testfile) == 'e');
  assert(fpeek(testfile) == 'e');

  fseek(testfile, 0L, SEEK_SET);

  char *buffer = fpeeks(testfile, 12);
  assert(buffer != NULL);
  assert(EQUALS(buffer, "Hello there!"));
  ufree(buffer);

  fclose(testfile);
  return EXIT_SUCCESS;
}
