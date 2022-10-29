#include <stdlib.h>
#include <string.h>

#define EQUALS(x, y) (strcmp(x, y) == 0)

#include "dmem.h"
#include "file.h"

#include "test.h"

int main(void) {
  char b[] = "Hello there!\nGENERAL KENOBI!";
  FILE *testfile = fmemopen(b, sizeof(b), "r");

  test("fsize", fsize(testfile) == sizeof(b));

  fseek(testfile, 0L, SEEK_SET);

  test("fpeek 0.0", fpeek(testfile) == 'H');
  test("fpeek 0.1", fpeek(testfile) == 'H');
  fgetc(testfile);
  test("fpeek 1.0", fpeek(testfile) == 'e');
  test("fpeek 1.1", fpeek(testfile) == 'e');

  fseek(testfile, 0L, SEEK_SET);

  char *buffer = fpeeks(testfile, 12);
  test("fpeeks NULL", buffer != NULL);
  test("fpeeks equals", EQUALS(buffer, "Hello there!"));
  ufree(buffer);

  fclose(testfile);
  return EXIT_SUCCESS;
}
