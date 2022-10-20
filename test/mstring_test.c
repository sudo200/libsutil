#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define EQUALS(x, y) (strcmp(x, y) == 0)

#include "dmem.h"
#include "mstring.h"

int main(void) {
  char *mystr;
  assert(msprintf(&mystr, "%s a test: %.3f, 0x%X %c", "This is", 653.76965364,
                  42, '\n') > 0);
  assert(EQUALS(mystr, "This is a test: 653.770, 0x2A \n"));

  assert(mstrcat(&mystr, "foo bar boom\n") != NULL);
  assert(EQUALS(mystr, "This is a test: 653.770, 0x2A \nfoo bar boom\n"));

  ufree(mystr);
  return 0;
}
