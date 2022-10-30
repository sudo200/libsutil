#ifndef ___LOGGER_H__
#define ___LOGGER_H__

#include <stdio.h>

#include "types.h"

typedef struct logger logger;

typedef enum {
  TRACE,
  DEBUG,
  INFO,
  NOTICE,
  WARNING,
  ERROR,
  FATAL,
} loglevel;

extern loglevel loggerlevel;

/**
 * Creates a new logger with given streams for writting output to.
 *
 * If both info and error are not NULL, info is used for output
 * below WARNING and error for output from and above WARNING.
 *
 * If info is not NULL and error is NULL, or vice versa,
 * the one stream is used for all output.
 *
 * If both info and error are NULL, info is set
 * to stdout and error to stderr.
 */
logger *logger_new(FILE *info, FILE *error);

bool logger_do_trace(logger *log);
bool logger_do_debug(logger *log);
bool logger_do_info(logger *log);
bool logger_do_notice(logger *log);
bool logger_do_warning(logger *log);
bool logger_do_error(logger *log);
bool logger_do_fatal(logger *log);

int logger_printf(logger *log, loglevel lvl, const char *format, ...);
int logger_print(logger *log, loglevel lvl, const char *msg);

/**
 * Destroys the given logger instance.
 *
 * IMPORTANT: Used streams are NOT closed BUT flushed.
 */
void logger_destroy(logger *log);

#define logger_trace(log, msg) logger_print(log, TRACE, msg)
#define logger_trace_f(log, format, ...)                                       \
  logger_printf(log, TRACE, format, __VA_ARGS__);
#define logger_debug(log, msg) logger_print(log, DEBUG, msg)
#define logger_debug_f(log, format, ...)                                       \
  logger_printf(log, DEBUG, format, __VA_ARGS__)
#define logger_info(log, msg) logger_print(log, INFO, msg)
#define logger_info_f(log, format, ...)                                        \
  logger_printf(log, INFO, format, __VA_ARGS__)
#define logger_notice(log, msg) logger_print(log, NOTICE, msg)
#define logger_notice_f(log, format, ...)                                      \
  logger_printf(log, NOTICE, format, __VA_ARGS__)
#define logger_warning(log, msg) logger_print(log, WARNING, msg)
#define logger_warning_f(log, format, ...)                                     \
  logger_printf(log, WARNING, format, __VA_ARGS__)
#define logger_error(log, msg) logger_print(log, ERROR, msg)
#define logger_error_f(log, format, ...)                                       \
  logger_printf(log, ERROR, format, __VA_ARGS__)
#define logger_fatal(log, msg) logger_print(log, FATAL, msg)
#define logger_fatal_f(log, format, ...)                                       \
  logger_printf(log, FATAL, format, __VA_ARGS__)

#endif //___LOGGER_H__
