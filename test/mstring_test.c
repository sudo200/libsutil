#include <stdlib.h>
#include <string.h>

#define EQUALS(x, y) (strcmp(x, y) == 0)
#define LENGTH(arr) (sizeof(arr) / sizeof(*arr))

#include "dmem.h"
#include "mstring.h"

#include "test.h"

char *mystr;

static void check_msprintf(void) {
  int ret = msprintf(&mystr, "%s a test: %.3f, 0x%X %c", "This is",
                     653.76965364, 42, '\n');
  assert(ret > 0);
  ASSERT(EQUALS(mystr, "This is a test: 653.770, 0x2A \n"));
}

static void check_mstrcat(void) {
  char *ret = mstrcat(&mystr, "foo bar boom\n");
  assert(ret != NULL);
  ASSERT(EQUALS(mystr, "This is a test: 653.770, 0x2A \nfoo bar boom\n"));

  ufree(mystr);
}

static void check_startswith(void) {
  bool ret = startswith("Hello there!", "Hel");
  ASSERT(ret);
}

static void check_endswith(void) {
  bool ret = endswith("Foo!", "!");
  ASSERT(ret);
}

string_array_t arr;

static void check_strspl(void) {
  int ret = strspl(&arr, "Hello there!", " ");
  assert(ret >= 0);
  assert(arr.len == 2UL);
  assert(EQUALS(arr.arr[0], "Hello"));
  ASSERT(EQUALS(arr.arr[1], "there!"));
}

static void check_strjoin(void) {
  char *str;
  int ret = strjoin(&str, arr, "(", " ", ")");
  assert(ret >= 0);
  ASSERT(EQUALS(str, "(Hello there!)"));

  ufree(str);
  ufree(*arr.arr);
  ufree(arr.arr);
}

static void check_strreplace(void) {
  char *s;
  msprintf(&s, "%s", "a b  c dhgdf e "); // For dyn. str
  char s_cpy[] = "a,b,,c,dhgdf,e,";

  char *ret = strreplace(&s, " ", ",");
  assert(ret != NULL);

  ASSERT(EQUALS(s, s_cpy));
  ufree(s);
}

char teststr[] = {"tEsTsTrIng123456789@!$&/"};

static void check_strupp(void) {
  bool ret = (strupp(teststr) == teststr);
  assert(ret);
  ASSERT(EQUALS(teststr, "TESTSTRING123456789@!$&/"));
}

static void check_strlow(void) {
  strcpy(teststr, "tEsTsTrIng123456789@!$&/");
  bool ret = (strlow(teststr) == teststr);
  assert(ret);
  ASSERT(EQUALS(teststr, "teststring123456789@!$&/"));
}

int main(void) {
  RUN_TEST(check_msprintf);
  RUN_TEST(check_mstrcat);
  RUN_TEST(check_startswith);
  RUN_TEST(check_endswith);
  RUN_TEST(check_strspl);
  RUN_TEST(check_strjoin);
  RUN_TEST(check_strreplace);
  RUN_TEST(check_strupp);
  RUN_TEST(check_strlow);

  return 0;
}
