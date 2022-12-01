#include <string.h>

#include "argparser.h"
#include "dmem.h"
#include "mstring.h"

#define EQUALS(x, y) (strcmp(x, y) == 0)
#define MEMQUALS(x, y, len) (memcmp(x, y, len) == 0)

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
                                 const char *long_name, size_t len) {
  for (; not_terminate(opts); opts++) {
    if (opts->long_name == NULL)
      continue;
    if (strlen(opts->long_name) < len)
      continue;

    if (MEMQUALS(opts->long_name, long_name, len))
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
      *opt->flag_exists = false;
    if (opt->argument != NULL)
      *opt->argument = NULL;
  }

  for (*optint = 1; *optint < argc; ++*optint) {
    if (EQUALS(argv[*optint], parse_stop))
      break;
    argparser_opt *opt;

    if (startswith(argv[*optint], shortopt_start) &&
        !startswith(argv[*optint], longopt_start)) // short option
    {
      const char *opt_str = argv[*optint] + 1; // Skip prefix

      for (; *opt_str != '\0'; opt_str++) {
        if ((opt = getshortopt(opts, *opt_str)) == NULL)
          return ARGPARSE_UNKNOWN_FLAG;

        *opt->flag_exists = true;

        if (opt->mode !=
            NO_ARG) // if a binary flag, keep interpreting string as short flags
          break;
      }
      opt_str++;

      if (strlen(opt_str) != 0) { // Argument appended
        if (opt->argument != NULL)
          *opt->argument = opt_str;
        continue;
      }

      if (*optint >= argc) {
        if (opt->mode == REQ_ARG)
          return ARGPARSE_ARG_REQ;
        continue;
      }

      if (opt->argument != NULL)
        *opt->argument = argv[++*optint];
    } else if (startswith(argv[*optint], longopt_start)) // long option
    {
      const char *opt_str =
          argv[*optint] + strlen(longopt_start); // Skip prefix
      const size_t opt_str_len = strlen(opt_str);

      const char *name_end = strchr(opt_str, longopt_seperator);
      if (name_end == NULL)
        name_end = opt_str + opt_str_len;
      else
        name_end++;

      if ((opt = getlongopt(opts, opt_str, name_end - opt_str - 1)) == NULL)
        return ARGPARSE_UNKNOWN_FLAG;

      *opt->flag_exists = true;

      if (name_end == opt_str + opt_str_len) {
        if (opt->mode == REQ_ARG)
          return ARGPARSE_ARG_REQ;
        continue;
      }

      if (opt->argument != NULL)
        *opt->argument = name_end;
    } else
      break;
  }

  return ARGPARSE_OK;
}
