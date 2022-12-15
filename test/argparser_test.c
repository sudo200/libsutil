#include <string.h>

#include "argparser.h"
#include "dmem.h"

#include "test.h"

#define EQUALS(x, y) (strcmp(x, y) == 0)

int argc1 = 5;
char *argv1[] = {"/bin/dummy", "-acFoo", "-de", "Bar", "Huhu!"};

bool a, b, c, d, e;
const char *c_val, *e_val;

int optint;
argparser_opt opts[] = {
    {"aaa", 'a', NO_ARG, &a, NULL},      {NULL, 'b', NO_ARG, &b, NULL},
    {"count", 'c', REQ_ARG, &c, &c_val}, {"delete", 'd', NO_ARG, &d, NULL},
    {NULL, 'e', REQ_ARG, &e, &e_val},

    {NULL, 0, NO_ARG, NULL, NULL}};

void argparse_exec_0(void) {
  ASSERT(argparse(argc1, argv1, opts, &optint, NULL, '\0', '\0', NULL) ==
         ARGPARSE_OK);
}

void argparse_args_0(void) {
  assert(a == true);
  assert(b == false);
  assert(c == true);
  assert(d == true);
  assert(e == true);

  assert(EQUALS(c_val, "Foo"));
  assert(EQUALS(e_val, "Bar"));

  ASSERT(optint == 4);
}

int argc2 = 6;
char *argv2[] = {"/usr/local/bin/another_dummy",
                 "--aaa=nope",
                 "--count=12345",
                 "--delete",
                 "/",
                 "ngfdjfr"};

void argparse_exec_1(void) {
  ASSERT(argparse(argc2, argv2, opts, &optint, NULL, '\0', '\0', NULL) ==
         ARGPARSE_OK);
}

void argparse_args_1(void) {
  assert(a == true);
  assert(b == false);
  assert(c == true);
  assert(d == true);
  assert(e == false);

  assert(EQUALS(c_val, "12345"));
  assert(e_val == NULL);

  ASSERT(optint == 4);
}

int main(void) {
  RUN_TEST(argparse_exec_0);
  RUN_TEST(argparse_args_0);

  RUN_TEST(argparse_exec_1);
  RUN_TEST(argparse_args_1);

  return 0;
}
