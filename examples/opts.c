#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <zt_opts.h>

static int
local_opt_long(int argn, int defn, int * argc, char ** argv, zt_opt_def_t * def, zt_opt_error error) {
    long   result;
    char * end = NULL;
    int    args_consumed = 0;
    char * arg = zt_opt_get_value(argn, defn, argv, def, &args_consumed, error);

    errno  = 0;
    result = strtol(arg, &end, 0);

    if (errno) {
        /* check errno */
        error(errno, "invalid number '%s'", arg);
    }

    if (end && *end) {
        /* invalid character */
        error(EINVAL, "'%s' is not a number", arg);
    }

    if (def[defn].cb_data) {
        *(long *)def[defn].cb_data = result;
    }

    return args_consumed;
}

struct lfd {
    int data;
};

int
main(int argc, char ** argv) {
    int        bool_type        = 0;
    char     * str              = NULL;
    long       long_int         = 0;
    int        flag             = 0;
    int        flag2            = 0;
    struct lfd local_func_data  = {
        0
    };

    #define LONG_DESC "This is a really long string intended to overflow the wrap widths so that we can test how well they work.  This is only a test"
    struct zt_opt_def options[] = {
        { 'h',        "help",     NULL,           zt_opt_help_stdout,   "[options]",      "this help text"   },
        { 'b',        "bool",     "[true|false]", zt_opt_bool_int,      &bool_type,       "boolean test"     },
        { 's',        "string",   "text",         zt_opt_string,        &str,             LONG_DESC          },
        { 'f',        "func",     "arg",          local_opt_long,       &local_func_data, "generic function" },
        { 'l',        "long",     "int",          zt_opt_long,          &long_int,        "a long integer"   },
        { 'q',        ZT_OPT_NLO, NULL,           zt_opt_flag_int,      &flag,            "short only flag"  },
        { ZT_OPT_NSO, "quiet",    NULL,           zt_opt_flag_int,      &flag2,           "long only flag"   },
        { ZT_OPT_END() }
    };

    int               nargc = argc;
    char           ** pargv = argv;

    int               ret   = zt_opt_process_args(&nargc, pargv, options, NULL, NULL);
    if (ret < 0) {
        fprintf(stderr, "Error processing args");
        exit(1);
    }

    return 0;
}
