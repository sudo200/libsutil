#include "globals.h"

const char *const LIBRARY_VERSION = HEADER_VERSION;

#define INFOPAGE                                                               \
  "libsutil " HEADER_VERSION "\n"                                              \
  "================================\n"                                         \
  "This is sudo200's utility library,\n"                                       \
  "originally developed just for fun, it\n"                                    \
  "kind of became a kitchen-sink library\n"                                    \
  "for everything from argument parsing,\n"                                    \
  "file handling to entire data structures.\n"

/////////////////////////////////////////////////////////////
///              WARNING! Black magic below!              ///
/////////////////////////////////////////////////////////////
#include <sys/unistd.h>

const char ld_loader[] __attribute__((section(".interp"))) = __LD;

__attribute__((force_align_arg_pointer)) void _start(void) {
  write(1, INFOPAGE, sizeof(INFOPAGE) - 1);
  _exit(0);
}
