/*
 * Routines needed globally in PerlQt.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pqt.h"

SV *obj_check(SV *sv, const char *message = "Invalid object") {
    SV *rv = rv_check(sv, message);
    if(!SvOBJECT(rv) || SvTYPE(rv) != SVt_PVHV)
        croak(message);
    return rv;
}

SV *rv_check(SV *sv, const char *message = "Not a reference") {
    if(!sv || !SvROK(sv)) croak(message);
    return SvRV(sv);
}

SV *safe_hv_store(HV *hash, const char *key, SV *value) {
    register SV **svp = hv_store(hash, (char *)key, strlen(key), value, 0);
    if(!svp) croak("Hash store store of '%s' failed", key);
    return *svp;
}

SV *safe_hv_fetch(HV *hash, const char *key, const char *message) {
    register SV **svp = hv_fetch(hash, (char *)key, strlen(key), 0);
    if(!svp) {
	if(message) croak(message);
	else croak("Could not access hash key \"%s\"", key);
    }
    return *svp;
}

static char *parse_clname(const char *clname) {
    char *newclname, *tmp;
    int clen = strlen(clname);

    if(!clname) croak("NULL classname");
    tmp = New(123, newclname, clen+1, char);
    strcpy(newclname, clname);
    while(isALNUM(*tmp)) tmp++;
    *tmp = 0;
    if(toLOWER(*newclname) == 'p' && clen != strlen(newclname))
	*newclname = 'Q';

    return newclname;   // this is New() memory, careful!
}

SV *objectify_ptr(void *ptr, const char *clname, int delete_on_destroy = 0) {
    if(!ptr) return &sv_undef;
    char *name = parse_clname(clname);

    HV *obj = newHV();

    HV *THIS   = newHV();
    SV *ptrsv  = newSViv((IV)ptr); SvREADONLY_on(ptrsv);
//    SV *coresv = newSViv((IV)ptr); SvREADONLY_on(coresv);
    safe_hv_store(THIS, name, ptrsv);
//    safe_hv_store(THIS, "CORE", coresv);  // Interesting naming scheme
    SvREFCNT_inc(ptrsv);
    safe_hv_store(THIS, "CORE", ptrsv);
    safe_hv_store(obj, "THIS", newRV_noinc((SV *)THIS));

    safe_hv_store(obj, "DELETE", boolSV(delete_on_destroy));
    SV *ret = sv_bless(newRV_noinc((SV *)obj), gv_stashpv(name, TRUE));
    Safefree(name);  // parse_clname
    return ret;
}

void *extract_ptr(SV *rv, const char *clname) {
    if(!SvOK(rv)) {
	if(toLOWER(clname[0]) != 'p')
	    warn("Unexpected undef argument converted to NULL pointer");
	return NULL;
    }
    HV *obj = (HV *)obj_check(rv);

    if(hv_exists(obj, "DELETED", 7)) {
	SV *sv = safe_hv_fetch(obj, "DELETED");
	if(SvREADONLY(sv))
	    croak("Attempt to access object deleted by parent");
	croak("DELETED is a reserved object key, and has been forged");
    }

    char *name = parse_clname(clname);
    HV *THIS =
	(HV *)rv_check(
	    safe_hv_fetch(obj, "THIS", "Could not access \"THIS\" element")
	);
    SV **ptrsv = hv_fetch(THIS, name, strlen(name), 0);
    SV *value;
    if(!ptrsv) {
	if(!sv_derived_from(rv, name))
	    croak("Expected a %s, got a %s", name, HvNAME(SvSTASH((SV *)obj)));
	value = safe_hv_fetch(THIS, "CORE", "Couldn't fetch \"CORE\"");
	SvREFCNT_inc(value);
	safe_hv_store(THIS, name, value);
//	    SV *copy = newSVsv(value);
//	    SvREADONLY_on(copy);
//	    safe_hv_store(THIS, name, copy);  // cache
    }
    else value = *ptrsv;
    if(!SvREADONLY(value))
	croak("Tampered THIS pointer");
    Safefree(name);  // parse_clname

    return (void *)SvIV(value);
}

bool want_destroy(SV *rv) {
//    printf("want_destroy %p\n", extract_ptr(rv, "DynaLoader"));
//    printf("want_destroy %d %d\n", SvREFCNT(rv), SvREFCNT(obj_check(rv)));
//    return hv_exists((HV *)obj_check(rv), "DELETE", 6);
    SV **svp = hv_fetch((HV *)obj_check(rv), "DELETE", 6, 0);
    if(svp) {
//	if(SvTRUE(*svp))
//	    printf("Must destroy %p\n", extract_ptr(rv, "DynaLoader"));
	return SvTRUE(*svp);
    }
    else return FALSE;
}

char *find_signal(SV *obj, char *signal) {
    dSP;
    int count;
    SV *ret;

    PUSHMARK(sp);
    XPUSHs(obj);
    XPUSHs(sv_2mortal(newSVpv(signal, 0)));
    PUTBACK;

    count = perl_call_pv("signals::find_signal", G_SCALAR);
    SPAGAIN;
    if(count != 1) croak("Bad perl_call_pv, bad");
    ret = POPs;
    PUTBACK;

    return SvTRUE(ret) ? SvPV(ret, na) : 0;
}

char *find_slot(SV *obj, char *slot) {
    dSP;
    int count;
    SV *ret;

    PUSHMARK(sp);
    XPUSHs(obj);
    XPUSHs(sv_2mortal(newSVpv(slot, 0)));
    PUTBACK;

    count = perl_call_pv("slots::find_slot", G_SCALAR);
    SPAGAIN;
    if(count != 1) croak("Bad perl_call_pv, bad");
    ret = POPs;
    PUTBACK;

    return SvTRUE(ret) ? SvPV(ret, na) : 0;
}

SV *parse_member(SV *member) {
    dSP;
    int count;
    SV *ret;

    PUSHMARK(sp);
    XPUSHs(member);
    PUTBACK;

    count = perl_call_pv("QObject::parse_member", G_SCALAR);
    SPAGAIN;
    if(count != 1) croak("Bad perl_call_pv, bad");
    ret = POPs;
    PUTBACK;

    return ret;
}

HV *Protos;

SV *unproto(SV *type) {
    STRLEN len;
    char *proto = SvPV(type, len);
    SV **svp = hv_fetch(Protos, proto, len, 0);
    if(svp) {
//	printf("%d: svp = '%s'\n", len, SvPV(*svp, na));
	return sv_mortalcopy(*svp);
//	return *svp;
    } else {
	warn("no prototype, damn\n");
    }
}

/*
SV *unproto(SV *type) {
    dSP;
    int count;
    SV *ret;

    PUSHMARK(sp);
    XPUSHs(type);
    PUTBACK;

    count = perl_call_pv("QObject::unproto", G_SCALAR);
    SPAGAIN;
    if(count != 1) croak("Bad perl_call_pv, bad");
    ret = POPs;
    PUTBACK;

    return ret;
}
*/
SV *proto(SV *p) {
    dSP;
    int count;
    SV *ret;

    PUSHMARK(sp);
    XPUSHs(p);
    PUTBACK;

    count = perl_call_pv("QObject::proto", G_SCALAR);
    SPAGAIN;
    if(count != 1) croak("Bad perl_call_pv, bad");
    ret = POPs;
    PUTBACK;

    return ret;
}

