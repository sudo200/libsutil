#include "logger.h"

#include "dmem.h"
#include "mstring.h"

static const char *const loglevel_str[] = {"TRACE",   "DEBUG", "INFO",
                                           "NOTICE",  "INFO",  "NOTICE",
                                           "WARNING", "ERROR", "FATAL"};

struct logger {
  FILE *info;
  FILE *error;
};

struct marker {
  char *name;
};

loglevel loggerlevel = INFO;

logger *logger_new(FILE *info, FILE *error) {
  if (info == NULL && error == NULL) {
    info = stdout;
    error = stderr;
  } else if (info != NULL && error == NULL)
    error = info;
  else if (info == NULL && error != NULL)
    info = error;

  logger *log = (logger *)ualloc(sizeof(*log));
  if (log == NULL)
    return NULL;

  *log = (logger){
      .info = info,
      .error = error,
  };

  return log;
}

bool logger_do_trace(logger *log) { return loggerlevel <= TRACE; }

bool logger_do_debug(logger *log) { return loggerlevel <= DEBUG; }

bool logger_do_info(logger *log) { return loggerlevel <= INFO; }

bool logger_do_notice(logger *log) { return loggerlevel <= NOTICE; }

bool logger_do_warning(logger *log) { return loggerlevel <= WARNING; }

bool logger_do_error(logger *log) { return loggerlevel <= ERROR; }

bool logger_do_fatal(logger *log) { return loggerlevel <= FATAL; }

int logger_printf(logger *log, loglevel lvl, marker *m, const char *format,
                  ...) {
  if (log == NULL || lvl < loggerlevel)
    return -1;

  va_list args;
  char *buffer;
  va_start(args, format);
  const int r = vmsprintf(&buffer, format, args);
  va_end(args);

  if (r < 0)
    return -1;

  if (fprintf((lvl < WARNING) ? log->info : log->error,
              m == NULL ? "[%1$s] %2$s" : "[%1$s] <%3$s> %2$s",
              loglevel_str[lvl], buffer, m->name) <= 0) {
    ufree(buffer);
    return -1;
  }
  ufree(buffer);

  return 0;
}

int logger_print(logger *log, loglevel lvl, marker *m, const char *msg) {
  if (logger_printf(log, lvl, m, "%s\n", msg) < 0)
    return -1;
  return 0;
}

void logger_destroy(logger *log) {
  if (log == NULL)
    return;

  fflush(log->info);
  fflush(log->error);

  ufree(log);
}

marker *marker_new(const char *name) {
  marker *m = (marker *)ualloc(sizeof(*m));
  if (m == NULL)
    return NULL;

  msprintf(&m->name, "%s", name);

  return m;
}

void marker_destroy(marker *m) {
  if (m == NULL)
    return;

  ufree(m->name);
  ufree(m);
}
