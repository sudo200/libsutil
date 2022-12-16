#ifndef ___LOGGER_H__
#define ___LOGGER_H__

#include <stdio.h>

#include "types.h"

typedef struct logger logger;
typedef struct marker marker;

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
 *
 * @param info  The stream to write messages below WARNING into.
 * @param error The stream to write messages from and above WARNING into.
 * @param _syslog If true, also write into syslog
 */
logger *logger_new(FILE *info, FILE *error, bool _syslog);

bool logger_do_trace(logger *log);
bool logger_do_debug(logger *log);
bool logger_do_info(logger *log);
bool logger_do_notice(logger *log);
bool logger_do_warning(logger *log);
bool logger_do_error(logger *log);
bool logger_do_fatal(logger *log);

__attribute__((format(printf,4,5))) int logger_printf(logger *log, loglevel lvl, marker *m, const char *format, ...);
int logger_print(logger *log, loglevel lvl, marker *m, const char *msg);

/**
 * Destroys the given logger instance.
 *
 * IMPORTANT: Used streams are NOT closed BUT flushed.
 */
void logger_destroy(logger *log);

/**
 * Creates a new marker with the given name.
 *
 * @param name The name of the marker.
 * @return The new marker or NULL on error.
 */
marker *marker_new(const char *name);

/**
 * Destroys the given marker.
 *
 * @param m The marker to destroy.
 */
void marker_destroy(marker *m);

#define logger_trace(log, msg) logger_print(log, TRACE, NULL, msg)
#define logger_trace_f(log, format, ...)                                       \
  logger_printf(log, TRACE, NULL, format, __VA_ARGS__);
#define logger_debug(log, msg) logger_print(log, DEBUG, NULL, msg)
#define logger_debug_f(log, format, ...)                                       \
  logger_printf(log, DEBUG, NULL, format, __VA_ARGS__)
#define logger_info(log, msg) logger_print(log, INFO, NULL, msg)
#define logger_info_f(log, format, ...)                                        \
  logger_printf(log, INFO, NULL, format, __VA_ARGS__)
#define logger_notice(log, msg) logger_print(log, NOTICE, NULL, msg)
#define logger_notice_f(log, format, ...)                                      \
  logger_printf(log, NOTICE, NULL, format, __VA_ARGS__)
#define logger_warning(log, msg) logger_print(log, WARNING, NULL, msg)
#define logger_warning_f(log, format, ...)                                     \
  logger_printf(log, WARNING, NULL, format, __VA_ARGS__)
#define logger_error(log, msg) logger_print(log, ERROR, NULL, msg)
#define logger_error_f(log, format, ...)                                       \
  logger_printf(log, ERROR, NULL, format, __VA_ARGS__)
#define logger_fatal(log, msg) logger_print(log, FATAL, NULL, msg)
#define logger_fatal_f(log, format, ...)                                       \
  logger_printf(log, FATAL, NULL, format, __VA_ARGS__)

#define logger_trace_m(log, marker, msg) logger_print(log, TRACE, marker, msg)
#define logger_trace_fm(log, marker, format, ...)                              \
  logger_printf(log, TRACE, marker, format, __VA_ARGS__)
#define logger_debug_m(log, marker, msg) logger_print(log, DEBUG, marker, msg)
#define logger_debug_fm(log, marker, format, ...)                              \
  logger_printf(log, DEBUG, marker, format, __VA_ARGS__)
#define logger_info_m(log, marker, msg) logger_print(log, INFO, marker, msg)
#define logger_info_fm(log, marker, format, ...)                               \
  logger_printf(log, INFO, marker, format, __VA_ARGS__)
#define logger_notice_m(log, marker, msg) logger_print(log, NOTICE, marker, msg)
#define logger_notice_fm(log, marker, format, ...)                             \
  logger_printf(log, NOTICE, marker, format, __VA_ARGS__)
#define logger_warning_m(log, marker, msg)                                     \
  logger_print(log, WARNING, marker, msg)
#define logger_warning_fm(log, marker, format, ...)                            \
  logger_printf(log, WARNING, marker, format, __VA_ARGS__)
#define logger_error_m(log, marker, msg) logger_print(log, ERROR, marker, msg)
#define logger_error_fm(log, marker, format, ...)                              \
  logger_printf(log, ERROR, marker, format, __VA_ARGS__)
#define logger_fatal_m(log, marker, msg) logger_print(log, FATAL, marker, msg)
#define logger_fatal_fm(log, marker, format, ...)                              \
  logger_printf(log, FATAL, marker, format, __VA_ARGS__)

#endif //___LOGGER_H__
