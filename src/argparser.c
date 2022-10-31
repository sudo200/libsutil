#include <string.h>

#include "argparser.h"
#include "dmem.h"
#include "mstring.h"

#define EQUALS(x, y) (strcmp(x, y) == 0)

// Private functions
static bool not_terminate(const argparser_opt *opt) {
  if (opt == NULL)
    return false;

  if (opt->argument != NULL)
    return true;
  if (opt->flag_exists != NULL)
    return true;
  if (opt->mode != 0)
    return true;
  if (opt->long_name != NULL)
    return true;
  if (opt->short_name != '\0')
    return true;

  return false;
}

static argparser_opt *getlongopt(const argparser_opt *opts,
                                 const char *long_name) {
  for (; not_terminate(opts); opts++) {
    if (opts->long_name == NULL)
      continue;

    if (EQUALS(opts->long_name, long_name))
      return (argparser_opt *)opts;
  }

  return NULL;
}

static argparser_opt *getshortopt(const argparser_opt *opts, char short_name) {
  for (; not_terminate(opts); opts++) {
    if (opts->short_name == '\0')
      continue;

    if (opts->short_name == short_name)
      return (argparser_opt *)opts;
  }

  return NULL;
}

// Public functions
argparser_status argparse(int argc, char **argv, argparser_opt *opts,
                          int *optint, const char *longopt_start,
                          char _shortopt_start, char longopt_seperator,
                          const char *parse_stop) {
  if (argv == NULL || opts == NULL)
    return ARGPARSE_GENERIC_ERROR;

  if (optint == NULL) {
    int _optint;
    optint = &_optint;
  }
  if (longopt_start == NULL)
    longopt_start = LONGOPT_START_DEFAULT;
  if (_shortopt_start == '\0')
    _shortopt_start = SHORTOPT_START_DEFAULT;
  if (longopt_seperator == '\0')
    longopt_seperator = LONGOPT_SEPERATOR_DEFAULT;
  if (parse_stop == NULL)
    parse_stop = PARSE_STOP_DEFAULT;

  const char shortopt_start[] = {_shortopt_start, '\0'};

  for (argparser_opt *opt = opts; not_terminate(opt); opt++) {
    if (opt->flag_exists != NULL)
      *(opt->flag_exists) = false;
    if (opt->argument != NULL)
      (*opt->argument) = NULL;
  }

  for (*optint = 1; *optint < argc; (*optint)++) {
    if (EQUALS(argv[*optint], parse_stop))
      break;
    argparser_opt *opt;

    if (startswith(argv[*optint], shortopt_start) &&
        !startswith(argv[*optint], longopt_start)) // short option
    {
      const char *opt_str = argv[*optint] + 1;

      for (; *opt_str; opt_str++) {
        if ((opt = getshortopt(opts, *opt_str)) == NULL)
          return ARGPARSE_UNKNOWN_FLAG;

        *opt->flag_exists = true;

        if (opt->mode != NO_ARG)
          break;
      }

      if (strlen(opt_str) == 0 &&
          (*optint >= argc || startswith(argv[*optint + 1], longopt_start) ||
           startswith(argv[*optint + 1], shortopt_start)))
        return ARGPARSE_ARG_REQ;

      msprintf(opt->argument, "%s",
               strlen(opt_str) > 1 ? opt_str + 1 : argv[++(*optint)]);
    } else if (startswith(argv[*optint], longopt_start)) // long option
    {
      char *opt_str, *arg;
      msprintf(&opt_str, "%s", argv[*optint] + strlen(longopt_start));
      if ((arg = strchr(opt_str, longopt_seperator)) != NULL)
        *arg++ = '\0';

      if ((opt = getlongopt(opts, opt_str)) == NULL) {
        ufree(opt_str);
        return ARGPARSE_UNKNOWN_FLAG;
      }
      *(opt->flag_exists) = true;

      if (opt->mode == NO_ARG) {
        ufree(opt_str);
        continue;
      }

      if (arg == NULL && opt->mode == REQ_ARG)
        return ARGPARSE_ARG_REQ;

      if (arg != NULL) {
        msprintf(opt->argument, "%s", arg);
        ufree(opt_str);
      }
    } else // Smth. else
      break;
  }

  return ARGPARSE_OK;
}
