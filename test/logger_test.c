#include <stdio.h>
#include <string.h>

#include "logger.h"

#include "test.h"

#define BUFFER_SIZE 0xFF

#define EQUALS(x, y) (strcmp(x, y) == 0)

char info_buffer[BUFFER_SIZE], error_buffer[BUFFER_SIZE];
FILE *info_stream, *error_stream;

__attribute__((unused)) static void debug(const char *buf) {
  fputs("\n** DEBUG **\n", stderr);
  for (; *buf != '\0'; buf++)
    fprintf(stderr, "\t%1$c\t%1$X\t%1$d\n", *buf);
  fputs("**       **\n\n", stderr);
}

static void clear(void) {
  memset(info_buffer, '\0', sizeof(info_buffer));
  memset(error_buffer, '\0', sizeof(error_buffer));

  fseek(info_stream, 0L, SEEK_SET);
  fseek(error_stream, 0L, SEEK_SET);
}

static void flush(void) {
  fflush(info_stream);
  fflush(error_stream);
}

static void con(void) {
  info_stream = fmemopen(info_buffer, BUFFER_SIZE, "w");
  error_stream = fmemopen(error_buffer, BUFFER_SIZE, "w");
  clear();
}

static void des(void) {
  fclose(info_stream);
  fclose(error_stream);
}

void logger_printf_NULL_ptr(void) {
  int ret = logger_printf(NULL, FATAL, NULL, "");
  ASSERT(ret < 0);
}

void logger_print_NULL_ptr(void) {
  int ret = logger_print(NULL, FATAL, NULL, "");
  ASSERT(ret < 0);
}

logger *logg;

void logger_new_non_NULL(void) {
  logg = logger_new(info_stream, error_stream, false);
  ASSERT(logg != NULL);
}

void test_std_log_level(void) {
  logger_debug(logg, "Hello there!");
  flush();
  assert(EQUALS(info_buffer, ""));
  clear();

  assert(!logger_do_trace(logg));
  assert(!logger_do_debug(logg));
  assert(logger_do_info(logg));

  logger_info(logg, "Hello there!");
  flush();

  ASSERT(EQUALS(info_buffer, "[INFO] Hello there!\n"));
  clear();
}

void check_verbosity(void) {
  clear();

  loggerlevel = TRACE;

  logger_trace(logg, "trace");
  logger_debug(logg, "debug");
  logger_info(logg, "info");
  logger_notice(logg, "notice");
  logger_warning(logg, "warning");
  logger_error(logg, "error");
  logger_fatal(logg, "fatal");
  flush();

  assert(
      EQUALS(info_buffer,
             "[TRACE] trace\n[DEBUG] debug\n[INFO] info\n[NOTICE] notice\n"));
  ASSERT(EQUALS(error_buffer,
                "[WARNING] warning\n[ERROR] error\n[FATAL] fatal\n"));
  clear();
}

marker *m;
void check_marker_non_NULL(void) {
  m = marker_new("Hello");
  ASSERT(m != NULL);
}

void check_output_marker(void) {
  clear();
  logger_trace_m(logg, m, "trace");
  logger_debug_m(logg, m, "debug");
  logger_info_m(logg, m, "info");
  logger_notice_m(logg, m, "notice");
  logger_warning_m(logg, m, "warning");
  logger_error_m(logg, m, "error");
  logger_fatal_m(logg, m, "fatal");
  flush();

  assert(EQUALS(info_buffer,
                "[TRACE] <Hello> trace\n[DEBUG] <Hello> debug\n[INFO] <Hello> "
                "info\n[NOTICE] <Hello> notice\n"));
  ASSERT(EQUALS(error_buffer, "[WARNING] <Hello> warning\n[ERROR] <Hello> "
                              "error\n[FATAL] <Hello> fatal\n"));
}

int main(void) {
  con();
  clear();

  RUN_TEST(logger_print_NULL_ptr);
  RUN_TEST(logger_printf_NULL_ptr);
  RUN_TEST(logger_new_non_NULL);
  RUN_TEST(test_std_log_level);
  RUN_TEST(check_verbosity);
  RUN_TEST(check_marker_non_NULL);
  RUN_TEST(check_output_marker);

  marker_destroy(m);
  logger_destroy(logg);
  des();
  return 0;
}
