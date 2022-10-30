#include <string.h>

#include "argparser.h"
#include "dmem.h"

#include "test.h"

#define EQUALS(x, y) (strcmp(x, y) == 0)

int main(void) {
  int argc1 = 5;
  char *argv1[] = {"/bin/dummy", "-acFoo", "-de", "Bar", "Huhu!"};

  bool a, b, c, d, e;
  char *c_val, *e_val;

  int optint;
  argparser_opt opts[] = {
      {"aaa", 'a', NO_ARG, &a, NULL},      {NULL, 'b', NO_ARG, &b, NULL},
      {"count", 'c', REQ_ARG, &c, &c_val}, {"delete", 'd', NO_ARG, &d, NULL},
      {NULL, 'e', REQ_ARG, &e, &e_val},

      {NULL, 0, NO_ARG, NULL, NULL}};

  test("argparse exec", argparse(argc1, argv1, opts, &optint, NULL, '\0', '\0',
                                 NULL) == ARGPARSE_OK);

  test("a == true", a);
  test("b == false", !b);
  test("c == true", c);
  test("d == true", d);
  test("e == true", e);

  test("c_val == \"Foo\"", EQUALS(c_val, "Foo"));
  test("e_val == \"Bar\"", EQUALS(e_val, "Bar"));

  test("optint == 4", optint == 4);

  ufree(c_val);
  ufree(e_val);

  int argc2 = 6;
  char *argv2[] = {"/usr/local/bin/another_dummy",
                   "--aaa=nope",
                   "--count=12345",
                   "--delete",
                   "/",
                   "ngfdjfr"};

  test("argparse exec", argparse(argc2, argv2, opts, &optint, NULL, '\0', '\0',
                                 NULL) == ARGPARSE_OK);

  test("a == true", a);
  test("b == false", !b);
  test("c == true", c);
  test("d == true", d);
  test("e == true", !e);

  test("c_val == \"12345\"", EQUALS(c_val, "12345"));
  test("e_val == NULL", e_val == NULL);

  test("optint == 4", optint == 4);

  ufree(c_val);

  return 0;
}
