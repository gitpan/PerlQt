/*
 * Core routines for PerlQt
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqt.h>
#include <pvirtual.h>

SV *objectify_qobject(const QObject *obj, const char *name,
		      bool delete_on_destroy) {
    if(!obj) return newSVsv(&sv_undef);
    register QMetaObject *meta = obj->metaObject();
    do {
        const char *classname = meta->className();
        if(gv_stashpv((char *)classname, FALSE))  // Does the class exist?
            return sv_2mortal(objectify_ptr((const void *)obj, classname));
    } while(meta = meta->superClass());           // Fall back conversion

    // Since when does the world work the way you expect it to?

    if(!name) name = obj->className();
    if(!name) name = "QObject";
    return objectify_ptr((const void *)obj, name, delete_on_destroy);
}

SV *objectify_new_qobject(const QObject *obj, virtualize *virt,
			  const char *name) {
    if(!obj || !virt || !name) return newSVsv(&sv_undef);
    SV *objref = objectify_ptr((const void *)obj, name, TRUE);
    virt->setClassName(name);
    virt->setQtObject(objref);
    return objref;
}

char *parse_classname(const char *name, char *ch = 0) {
    static char *c = new char[64];
    static int clen = 64;
    const char *s = name;
    int len;

    while(isSPACE(*s)) s++;
    if(!isIDFIRST(*s)) croak("Invalid class name '%s'", name);
    name = s;
    while(isALNUM(*s) || *s == ':') s++;
    len = s - name;

    if(!(len < clen)) { delete [] c; clen = len + 1; c = new char[clen]; }
    strncpy(c, name, len);
    c[len] = 0;

    if(ch) { while(isSPACE(*s)) s++; *ch = *s; }

    return c;
}

//Yes, this logic table isn't entirely consistent. So what? It's MY program!
//
//if DESTROY = no, permanently immortal
//if DESTROY = yes, currently mortal
//if !exists DESTROY, currently immortal
//
//if CONST = yes, permanently const
//if CONST = no, currently const
//if !exists CONST, currently mutable

SV *objectify_ptr(const void *ptr, const char *n, bool delete_on_destroy) {
    if(!ptr || !n) return newSVsv(&sv_undef);
    HV *obj = newHV();
    HV *THIS = newHV();
    bool isconst = !strncmp(n, "const ", 6);
    if(isconst) n += 6;
    n = parse_classname(n);

    safe_hv_store_new(THIS, n, safe_hv_store(THIS, "CORE", newSViv((IV)ptr)));
    safe_hv_store(THIS, "CORE::DESTROY", boolSV(delete_on_destroy));
    if(isconst) safe_hv_store(THIS, "CORE::CONST", &sv_yes);

    sv_magic((SV *)obj, (SV *)THIS, '~', (char *)n, strlen(n));
    SvREFCNT_dec(THIS);
    return sv_bless(newRV_noinc((SV *)obj), gv_stashpv((char *)n, TRUE));
}

void *extract_ptr(SV *rv, const char *n) {
    char ch = 0;
    bool wantconst = FALSE;
    if(n) {
	wantconst = !strncmp(n, "const ", 6);
	if(wantconst) n += 6;
	n = parse_classname(n, &ch);
    }
    if(!SvOK(rv)) {
	if(dowarn && ch == '&')			// Non-fatal, non-mandatory
	    warn("Unexpected undef argument converted to NULL pointer");
	return 0;
    }
    HV *obj = obj_check(rv);
    MAGIC *mg = mg_find((SV *)obj, '~');
    if(!mg || !mg->mg_obj) croak("Not a PerlQt object");
    HV *THIS = (HV *)mg->mg_obj;
    if(safe_hv_exists(THIS, "DESTROYED"))
	croak("Attempt to access destroyed object");
    if(dowarn && !wantconst && safe_hv_exists(THIS, "CORE::CONST"))
	warn("Immutable object used in mutable context");

    SV *value = safe_hv_fetch(THIS, "CORE");
    if(n && !safe_hv_exists(THIS, n)) {
	if(!sv_derived_from(rv, (char *)n))
	    croak("Expected a %s, got a %s", n, HvNAME(SvSTASH((SV *)obj)));
	safe_hv_store(THIS, n, value);
    }
    return (void *)SvIV(value);
}

bool pqt_object(SV *obj) {
    return sv_isobject(obj);
}

bool want_destroy(SV *obj) {
    return FALSE;
}
