#include <syslog.h>

#include "logger.h"

#include "dmem.h"
#include "mstring.h"

static const char *const loglevel_str[] = {"TRACE",   "DEBUG", "INFO", "NOTICE",
                                           "WARNING", "ERROR", "FATAL"};

static int logger2syslog(loglevel lvl) {
  switch (lvl) {
  case TRACE:
  case DEBUG:
    return LOG_DEBUG;
  case INFO:
    return LOG_INFO;
  case NOTICE:
    return LOG_NOTICE;
  case WARNING:
    return LOG_WARNING;
  case ERROR:
    return LOG_ERR;
  case FATAL:
    return LOG_EMERG;
  }
}

struct logger {
  FILE *info;
  FILE *error;
  bool _syslog;
};

struct marker {
  char *name;
};

loglevel loggerlevel = INFO;

logger_t *logger_new(FILE *info, FILE *error, bool _syslog) {
  if (info == NULL && error == NULL) {
    info = stdout;
    error = stderr;
  } else if (info != NULL && error == NULL)
    error = info;
  else if (info == NULL && error != NULL)
    info = error;

  logger_t *log = (logger_t *)ualloc(sizeof(*log));
  if (log == NULL)
    return NULL;

  *log = (logger_t){
      .info = info,
      .error = error,
      ._syslog = _syslog,
  };

  if (_syslog)
    openlog(NULL, LOG_PID, LOG_USER);

  return log;
}

bool logger_do_trace(logger_t *log) { return loggerlevel <= TRACE; }

bool logger_do_debug(logger_t *log) { return loggerlevel <= DEBUG; }

bool logger_do_info(logger_t *log) { return loggerlevel <= INFO; }

bool logger_do_notice(logger_t *log) { return loggerlevel <= NOTICE; }

bool logger_do_warning(logger_t *log) { return loggerlevel <= WARNING; }

bool logger_do_error(logger_t *log) { return loggerlevel <= ERROR; }

bool logger_do_fatal(logger_t *log) { return loggerlevel <= FATAL; }

int logger_printf(logger_t *log, loglevel lvl, marker *m, const char *format,
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

  const char *_format = (m == NULL) ? "[%1$s] %2$s" : "[%1$s] <%3$s> %2$s";

  if (log->_syslog)
    syslog(logger2syslog(lvl) | LOG_USER, _format, loglevel_str[lvl], buffer,
           m == NULL ? NULL : m->name);

  if (fprintf((lvl < WARNING) ? log->info : log->error, _format,
              loglevel_str[lvl], buffer, m == NULL ? NULL : m->name) <= 0) {
    ufree(buffer);
    return -1;
  }
  putc('\n', (lvl < WARNING) ? log->info : log->error);
  ufree(buffer);

  return 0;
}

int logger_print(logger_t *log, loglevel lvl, marker *m, const char *msg) {
  if (logger_printf(log, lvl, m, "%s", msg) < 0)
    return -1;
  return 0;
}

void logger_destroy(logger_t *log) {
  if (log == NULL)
    return;

  if (log->_syslog)
    closelog();

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
