#include <assert.h>
#include <string.h>

#include "dstring.h"

#define equals(x, y) (strcmp(x, y) == 0)

#include <stdio.h>

int main(void) {
  dstring str = dstring_new(NULL);
  assert(str != NULL);

  assert(equals(str, ""));

  dstring_destroy(&str);

  str = dstring_new("foo,bar,boom");
  assert(str != NULL);

  assert(equals(str, "foo,bar,boom"));
  assert(dstring_length(str) == 12);

  assert(dstring_cat(&str, ",saas,sees,soos") >= 0);

  assert(equals(str, "foo,bar,boom,saas,sees,soos"));
  assert(dstring_length(str) == 27);

  dstring copy = dstring_new(str);

  assert(dstring_cmp(str, copy) == 0);

  dstring_destroy(&str);
  dstring_destroy(&copy);
  return 0;
}
