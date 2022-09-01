#include <stdio.h>

#include "strspl.h"

#define die(msg) do { \
  perror(msg); \
  exit(EXIT_FAILURE); \
  } while(0);

int main()
{
  string_array_t tokens;
  if(strspl(&tokens, "Hello there my friends!", ' ') < 0)
    die("Error in strspl()");

  puts("Tokens:");
  for(size_t i = 0; i < tokens.len; i++)
    printf("\t%s\n", tokens.arr[i]);

  free(*tokens.arr);
  free(tokens.arr);
  
  return EXIT_SUCCESS;
}

