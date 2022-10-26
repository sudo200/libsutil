#ifndef ___ARGPARSER_H__
#define ___ARGPARSER_H__

#include "types.h"

#define LONGOPT_START_DEFAULT "--"
#define SHORTOPT_START_DEFAULT '-'
#define LONGOPT_SEPERATOR_DEFAULT '='
#define PARSE_STOP_DEFAULT "--"

typedef enum {
  /**
   * Parsing was successful.
   */
  ARGPARSE_OK,

  /**
   * Something went wrong.
   */
  ARGPARSE_GENERIC_ERROR,

  /**
   * A flag requiring an argument didn't get one.
   */
  ARGPARSE_ARG_REQ,

  /**
   * An unknown flag has been encountered.
   */
  ARGPARSE_UNKNOWN_FLAG,
} argparser_status;

typedef enum {
  /**
   * The flag does not accept an argument.
   */
  NO_ARG = 0,

  /**
   * The flag can accept an argument.
   */
  OPT_ARG,

  /**
   * The flag requires an argument.
   */
  REQ_ARG,
} argparser_argmode;

typedef struct {
  /**
   * The long name of the flag.
   * Can be NULL, if no long name is desired.
   */
  const char *long_name;

  /**
   * The short name of the flag.
   * Can be '\0', if no short name is desired.
   */
  const char short_name;

  /**
   * The argmode of the flag.
   * @see argparser_argmode
   */
  const argparser_argmode mode;

  /**
   * If the flag exists, true
   * is written into the variable
   * specified by this pointer, else false.
   */
  bool *flag_exists;

  /**
   * If an argument exists,
   * it is written into this pointer.
   * Can be NULL, if no argument are accepted.
   */
  char **argument;
} argparser_opt;

/**
 * Parses program arguments.
 *
 * @param argc argc from the main function.
 * @param argv argv from the main function.
 * @param opts A null-terminated array with all options to parse.
 * @param optint Pointer to an int, in which the first index after flags is
 * stored. Can be NULL.
 * @param longopt_start A string with which all long options have to start. Can
 * be NULL to use the default.
 * @param shortopt_start A character with which all short options have to start.
 * Can be NULL to use the default.
 * @param longopt_seperator A character with which seperates long option and
 * argument. Can be NULL to use the default.
 * @param parse_stop A string which when encountered stops parsing.
 * @return The status of parsing.
 */
argparser_status argparse(int argc, char **argv, argparser_opt *opts,
                          int *optint, const char *longopt_start,
                          char shortopt_start,
                          char longopt_seperator, const char *parse_stop);

#endif //___ARGPARSER_H__
