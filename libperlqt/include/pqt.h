#ifndef PQT_H
#define PQT_H

/*
 * Header of general use to libperlqt and PerlQt
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */


// This header is needed by every Qt source file. It probably should be
// #included *AFTER* any real qt headers, because there are serious
// name-space conflicts between qt and Perl. Any and all name-space
// conflicts are to be solved in this header, one time.

#undef bool

#include "qglobal.h"
#include "qwindefs.h"

#if defined(DEBUG)
/*
 * Perl has an extensive set of DEBUG* macros, it's better to cut off the
 * single Qt DEBUG definition than to fiddle with all of Perl's macros. We
 * keep a copy of it in QtDEBUG if it exists. Qt is very conservative with
 * it's use of defines, Perl is just plain reckless. Lets cross our
 * fingers and hope everything works out alright.
 */
#define QtDEBUG
#undef DEBUG
#endif  // defined(DEBUG)

extern "C" {
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
}

#undef bool

#define MSTR(str) # str

#define pextract(type, elem) (type *)extract_ptr(ST(elem), MSTR(type ## *))

typedef char pChar;

extern SV *objectify_ptr(void *, const char *, int = 0);
extern void *extract_ptr(SV *, const char *);
extern bool want_destroy(SV *);
extern SV *rv_check(SV *, const char * = "Not a reference");
extern SV *obj_check(SV *, const char * = "Invalid object");
extern SV *safe_hv_store(HV *, const char *, SV *);
extern SV *safe_hv_fetch(HV *, const char *, const char * = NULL);

extern char *find_signal(SV *obj, char *signal);
extern char *find_slot(SV *obj, char *slot);

extern SV *parse_member(SV *member);

#endif  // PQT_H
