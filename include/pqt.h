#ifndef PQT_H
#define PQT_H

/*
 * Globally useful header for PerlQt and its components
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include <qglobal.h>
#include <qwindefs.h>

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
#include <EXTERN.h>
#include <perl.h>
#include <XSUB.h>
}

#undef bool

#define pQ(idx, name)  ((name *)extract_ptr(ST(idx), #name))
#define pdQ(idx, name) ((name *)extract_ptr(ST(idx), #name " &"))
#define pzQ(idx, name) ((items > idx)?(name *)extract_ptr(ST(idx), #name) : 0)

//#define pPV(idx)   pchar_pv(ST(idx))
//#define pdPV(idx)  pchar_pv(ST(idx), TRUE)
//#define pzPV(idx)  ((items > idx) ? pchar_pv(ST(idx)) : 0)
#define pcPV(idx)  pcchar_pv(ST(idx))
#define pcdPV(idx) pcchar_pv(ST(idx), TRUE)
#define pczPV(idx) ((items > idx) ? pcchar_pv(ST(idx)) : 0)

#define pIV(idx) SvIV(ST(idx))
#define pzIV(idx) ((items > idx) ? SvIV(ST(idx)) : 0)
#define pnIV(idx) ((items > idx) ? SvIV(ST(idx)) : -1)
#define pDefIV(idx, value) ((items > idx) ? SvIV(ST(idx)) : value)

#define pBOOL(idx)  (SvTRUE(ST(idx)) ? TRUE : FALSE)
#define ptBOOL(idx) ((items > idx) ? pBOOL(idx) : TRUE)
#define pfBOOL(idx) ((items > idx) ? pBOOL(idx) : FALSE)

#define pArgREF(var, type) objectify_ptr((void *)var, #type)
#define pArgBOOL(var) newSVsv(boolSV(var))
#define pArgIV(var) newSViv((IV)var)
#define pArgPV(var) newSVpv((char *)var, 0)

#define prDEREF(var, type) *(type *)extract_ptr(var, #type " &")
#define prREF(var, type) (type *)extract_ptr(var, #type)
#define prBOOL(var) (SvTRUE(var) ? TRUE : FALSE)

bool safe_hv_exists(HV *, const char *);

SV *safe_av_fetch(AV *, I32, const char * = 0);
SV *safe_av_store(AV *, I32, SV *, const char * = 0);
SV *safe_hv_fetch(HV *, const char *, const char * = 0);
SV *safe_hv_store(HV *, const char *, SV *, const char * = 0);

AV *safe_gv_store(const char *, AV *);
CV *safe_gv_store(const char *, CV *);
HV *safe_gv_store(const char *, HV *);
SV *safe_gv_store(const char *, SV *);

#define safe_av_store_new(av, key, value) \
    SvREFCNT_dec(safe_av_store(av, key, value))
#define safe_hv_store_new(hv, key, value) \
    SvREFCNT_dec(safe_hv_store(hv, key, value))
#define safe_gv_store_new(name, xv) \
    SvREFCNT_dec(safe_gv_store(name, xv))

// xsubpp food
#ifdef DEF
#undef DEF
#endif
#define DEF

struct pqt_const_hash {
    const char *key;
    IV value;
};

struct pqt_const_object {
    const char *key;
    const void *value;
    const char *className;
};

struct pqt_export {
    const char *name;
    void *source;
};


// pqt_class_register(className, multiple_inheritance ? isaArray : isaString,
//		      exportList, overloadList);

void pqt_class_register(const char *);
void pqt_class_register(const char *, const char **, const char ** = 0,
			const struct pqt_export * = 0, const char ** = 0);
void pqt_class_register(const char *, const char *, const char ** = 0,
			const struct pqt_export * = 0, const char ** = 0);

class virtualize;

bool pqt_object(SV *);
bool want_destroy(SV *);

HV *obj_check(SV *, const char * = "Invalid object");
SV *rv_check(SV *, const char * = "Not a reference");

SV *objectify_ptr(const void *, const char *, bool = FALSE);
SV *objectify_qobject(const QObject *, const char *, bool = FALSE);
SV *objectify_new_qobject(const QObject *, virtualize *, const char *);

void *extract_ptr(SV *, const char * = 0);

pchar pchar_pv(SV *, bool = FALSE);
pcchar pcchar_pv(SV *, bool = FALSE);
SV *pcchar_sv(const char *);

// Ignore this stuff below

//#define pqtRETVAL(type, value) STMT_START {type t=value; RETVAL=&t;} STMT_END
//#define pcQ(idx, name) (const name *)extract_ptr(ST(idx), "const " #name)
//#define pQd(idx, name) ((items > idx) ? (name *)extract_ptr(ST(idx), #name " &") : 0)
//#define pcQd(idx, name) ((items > idx) ? (name *)extract_ptr(ST(idx), "const " #name " &") : 0)

//#define ppQ(idx, name) *(name *)extract_ptr(ST(idx), #name)
//#define ppcQ(idx, name) *(const name *)extract_ptr(ST(idx), "const " #name)

//#define pcdPV(idx) ((items > idx) ? 
//#define pPVd(idx) ((items > idx) ? pchar_pv(ST(idx), 1) : 0)
//#define pcPVd(idx) ((items > idx) ? pcchar_pv(ST(idx), 1) : 0)

#endif  // PQT_H
