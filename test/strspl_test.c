#include <assert.h>
#include <string.h>

#define EQUALS(x, y)  (strcmp(x, y) == 0)

#include "strspl.h"

int main(void)
{
  string_array_t tokens;
  assert(strspl(&tokens, "Hello there my friends!", ' ') == 0);

  assert(tokens.len == 4);

  assert(EQUALS(tokens.arr[0], "Hello"));
  assert(EQUALS(tokens.arr[1], "there"));
  assert(EQUALS(tokens.arr[2], "my"));
  assert(EQUALS(tokens.arr[3], "friends!"));

  free(*tokens.arr);
  free(tokens.arr);
  
  return 0;
}

