#include <stdlib.h>
#include <string.h>

#define EQUALS(x, y) (strcmp(x, y) == 0)

#include "dmem.h"
#include "file.h"

#include "test.h"

char b[] = "Hello there!\nGENERAL KENOBI!";
FILE *testfile;

void test_fsize(void) { ASSERT(fsize(testfile) == sizeof(b)); }

void test_fpeek(void) {
  assert(fpeek(testfile) == 'H');
  assert(fpeek(testfile) == 'H');

  fgetc(testfile);
  assert(fpeek(testfile) == 'e');
  ASSERT(fpeek(testfile) == 'e');
}

void test_fpeeks(void) {
  char *buffer = fpeeks(testfile, 12);
  assert(buffer != NULL);
  ASSERT(EQUALS(buffer, "Hello there!"));
  ufree(buffer);
}

int main(void) {
  testfile = fmemopen(b, sizeof(b), "r");

  RUN_TEST(test_fsize);
  fseek(testfile, 0L, SEEK_SET);
  RUN_TEST(test_fpeek);
  fseek(testfile, 0L, SEEK_SET);
  RUN_TEST(test_fpeeks);

  fclose(testfile);
  return EXIT_SUCCESS;
}
