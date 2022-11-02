#include <string.h>

#include "logger.h"

#include "test.h"

#define BUFFER_SIZE 0xFF

#define EQUALS(x, y) (strcmp(x, y) == 0)

char info_buffer[BUFFER_SIZE], error_buffer[BUFFER_SIZE];
FILE *info_stream, *error_stream;

void clear(void) {
  memset(info_buffer, 0, BUFFER_SIZE);
  memset(error_buffer, 0, BUFFER_SIZE);

  fseek(info_stream, 0L, SEEK_SET);
  fseek(error_stream, 0L, SEEK_SET);
}

__attribute__((constructor)) void
X19hdHRyaWJ1dGVfXygoY29uc3RydWN0b3IpKSB2b2lkICh2b2lkKQo(void) {
  info_stream = fmemopen(info_buffer, BUFFER_SIZE, "w");
  error_stream = fmemopen(error_stream, BUFFER_SIZE, "w");
  clear();
}

__attribute__((destructor)) void
X19hdHRyaWJ1dGVfXygoZGVzdHJ1Y3RvcikpIHZvaWQgKHZvaWQpCg(void) {
  fclose(info_stream);
  fclose(error_stream);
}

int main(void) {
  test("logger_printf NULL pointer", logger_printf(NULL, FATAL, NULL, "") < 0);
  test("logger_print NULL pointer", logger_print(NULL, FATAL, NULL, "") < 0);

  logger *log = logger_new(info_stream, error_stream);

  logger_debug(log, "Hello there!");
  test("std logger level", EQUALS(info_buffer, ""));
  logger_info(log, "Hello there!");
  test("std logger level", EQUALS(info_buffer, "[INFO] Hello there!\n"));
  clear();
  test("std logger level", !logger_do_trace(log));
  test("std logger level", !logger_do_debug(log));
  test("std logger level", logger_do_info(log));

  loggerlevel = TRACE;

  logger_trace(log, "trace");
  logger_debug(log, "debug");
  logger_info(log, "info");
  logger_warning(log, "warning");
  logger_error(log, "error");
  logger_fatal(log, "fatal");

  test("logger write info",
       EQUALS(info_buffer,
              "[TRACE] trace\n[DEBUG] debug\n[INFO] info\n[NOTICE] notice\n"));
  test("logger write error",
       EQUALS(error_buffer,
              "[WARNING] warning\n[ERROR] error\n[FATAL] fatal\n"));
  clear();

  marker *m = marker_new("Hello");

  logger_trace_m(log, m, "trace");
  logger_debug_m(log, m, "debug");
  logger_info_m(log, m, "info");
  logger_notice_m(log, m, "notice");
  logger_warning_m(log, m, "warning");
  logger_error_m(log, m, "error");
  logger_fatal_m(log, m, "fatal");

  test("logger write info marker",
       EQUALS(info_buffer,
              "[TRACE] <Hello> trace\n[DEBUG] <Hello> debug\n[INFO] <Hello> "
              "info\n[NOTICE] <Hello> notice\n"));
  test("logger write error marker",
       EQUALS(error_buffer, "[WARNING] <Hello> warning\n[ERROR] <Hello> "
                            "error\n[FATAL] <Hello> fatal\n"));

  marker_destroy(m);
  logger_destroy(log);
  return 0;
}
