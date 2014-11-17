/*!
 * Filename: zt_opts.h
 * Description: Command line option parsing
 *
 * Author: Jason L. Shiffer <jshiffer@zerotao.org>
 * Copyright:
 *      Copyright (C) 2000-2010, Jason L. Shiffer.
 *      See file COPYING for details
 *
 * Notes:
 *
 */
#ifndef _ZT_OPTS_H_
#define _ZT_OPTS_H_

#include <stdarg.h>

#ifdef __cplusplus
# define BEGIN_C_DECLS extern "C" {
# define END_C_DECLS }
#else
# define BEGIN_C_DECLS
# define END_C_DECLS
#endif

BEGIN_C_DECLS

#define ZT_OPTS_NSO -1
#define ZT_OPTS_NLO NULL
#define ZT_OPTS_END() 0, NULL, NULL, NULL, NULL, NULL

typedef int (*zt_opts_error)(int code, char * fmt, ...);
typedef struct zt_opts_def zt_opts_def_t;
typedef int (*zt_opts_callback)(int argn, int defn, int * argc, char ** argv, zt_opts_def_t * def, zt_opts_error error);
struct zt_opts_def {
    char            sopt;
    char          * lopt;
    char          * arg;
    zt_opts_callback cb;
    void          * cb_data;
    char          * help;
};
typedef void (*zt_opts_validate)(zt_opts_def_t * args, zt_opts_error error);

int    zt_opts_null(int argn, int defn, int * argc, char ** argv, zt_opts_def_t * def, zt_opts_error error);

#ifdef HAVE_INTTYPES_H
int    zt_opts_intmax(int argn, int defn, int * argc, char ** argv, zt_opts_def_t * def, zt_opts_error error);
#endif /* HAVE_INTTYPES_H */

int    zt_opts_int(int argn, int defn, int * argc, char ** argv, zt_opts_def_t * def, zt_opts_error error);
int    zt_opts_long(int argn, int defn, int * argc, char ** argv, zt_opts_def_t * def, zt_opts_error error);
int    zt_opts_flag_int(int argn, int defn, int * argc, char ** argv, zt_opts_def_t * def, zt_opts_error error);
int    zt_opts_bool_int(int argn, int defn, int * argc, char ** argv, zt_opts_def_t * def, zt_opts_error error);
int    zt_opts_string(int argn, int defn, int * argc, char ** argv, zt_opts_def_t * def, zt_opts_error error);

int    zt_opts_help_stdout(int argn, int defn, int * argc, char ** argv, zt_opts_def_t * def, zt_opts_error error);
int    zt_opts_usage(const char * name, const char * help, zt_opts_def_t * opts);

char * zt_opts_get_value(int argn, int defn, char ** argv, zt_opts_def_t * def, int * args_consumed, zt_opts_error error);

void   zt_opts_validate_default(zt_opts_def_t * args, zt_opts_error error);
char * zt_opts_error_str(int code, char * fmt, ...);
char * zt_opts_verror_str(int code, char * fmt, va_list ap);
int    zt_opts_error_default(int code, char * fmt, ...);
int    zt_opts_verror_default(int code, char * fmt, va_list ap);
#define zt_opts_process(argc, argv, args) \
    zt_opts_process_args(argc, argv, args, NULL, NULL)
int    zt_opts_process_args(int * argc, char ** argv, zt_opts_def_t * args, zt_opts_validate validate, zt_opts_error error);


END_C_DECLS

#undef BEGIN_C_DECLS
#undef END_C_DECLS

#endif /*_ZT_OPTS_H_*/
