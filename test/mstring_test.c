#include <stdlib.h>
#include <string.h>

#define EQUALS(x, y) (strcmp(x, y) == 0)
#define LENGTH(arr) (sizeof(arr) / sizeof(*arr))

#include "dmem.h"
#include "mstring.h"

#include "test.h"

int main(void) {
  char *mystr;
  test("msprintf exec", msprintf(&mystr, "%s a test: %.3f, 0x%X %c", "This is",
                                 653.76965364, 42, '\n') > 0);
  test("msprintf string", EQUALS(mystr, "This is a test: 653.770, 0x2A \n"));

  test("mstrcat exec", mstrcat(&mystr, "foo bar boom\n") != NULL);
  test("mstrcat string",
       EQUALS(mystr, "This is a test: 653.770, 0x2A \nfoo bar boom\n"));

  ufree(mystr);

  test("startswith test", startswith("Hello there!", "Hel"));
  test("endswith", endswith("Foo!", "!"));

  string_array_t arr;

  test("strspl exec", strspl(&arr, "Hello there!", " ") >= 0);
  test("strspl len", arr.len == 2);
  test("strspl arr[0]", EQUALS(arr.arr[0], "Hello"));
  test("strspl arr[1]", EQUALS(arr.arr[1], "there!"));

  char *str;
  test("strjoin exec", strjoin(&str, arr, "(", " ", ")") >= 0);
  test("strjoin string", EQUALS(str, "(Hello there!)"));

  ufree(str);
  ufree(*arr.arr);
  ufree(arr.arr);

  char *s;
  msprintf(&s, "%s", "a b  c dhgdf e ");
  char s_cpy[] = "a,b,,c,dhgdf,e,";

  test("strreplace exec", strreplace(&s, " ", ",") != NULL);

  test("strreplace equal", EQUALS(s, s_cpy));
  ufree(s);

  char teststr[] = {"tEsTsTrIng123456789@!$&/"};
  test("strupp exec", strupp(teststr) == teststr);
  test("strupp result", EQUALS(teststr, "TESTSTRING123456789@!$&/"));

  strcpy(teststr, "tEsTsTrIng123456789@!$&/");
  test("strlow exec", strlow(teststr) == teststr);
  test("strlow result", EQUALS(teststr, "teststring123456789@!$&/"));

  return 0;
}
