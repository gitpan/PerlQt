/*
 * Functions definitions for pigconstant.h
 *
 * Copyright (C) 1999, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README.LICENSE file which should be included with this library.
 *
 */

#include "pigperl.h"
#include "pigconstant.h"
#include "pigclassinfo.h"
#include "pigtype_object.h"

#if PIGPERL_PL < 5

/* perl-5.005 code. Used under GPL, removed PL_ prefixes */

static void newCONSTSUB(HV *stash, char *name, SV *sv) {
    U32 oldhints = hints;
    HV *old_cop_stash = curcop->cop_stash;
    HV *old_curstash = curstash;
    line_t oldline = curcop->cop_line;
    curcop->cop_line = copline;

    hints &= ~HINT_BLOCK_SCOPE;
    if(stash)
        curstash = curcop->cop_stash = stash;

    newSUB(
        start_subparse(FALSE, 0),
        newSVOP(OP_CONST, 0, newSVpv(name,0)),
        newSVOP(OP_CONST, 0, &sv_no),        /* SvPV(&sv_no) == "" -- GMB */
        newSTATEOP(0, Nullch, newSVOP(OP_CONST, 0, sv))
    );

    hints = oldhints;
    curcop->cop_stash = old_cop_stash;
    curstash = old_curstash;
    curcop->cop_line = oldline;
}
#endif

static void pig_load_constant_int(const pig_constant_int *pig0, const char *pig1) {
    HV *pigstash;

    if(!pig0 || !pig1) return;
    pigstash = gv_stashpv((char *)pig1, TRUE);

    while(pig0->pigname) {
        newCONSTSUB(pigstash, (char *)pig0->pigname, newSViv(pig0->pigval));
	pig0++;
    }
}

static void pig_load_constant_object(const pig_constant_object *pig0, const char *pig1) {
    HV *pigstash;
    pig_object_data *pigd;
    SV *pigobj;

    if(!pig0 || !pig1) return;
    pigstash = gv_stashpv((char *)pig1, TRUE);

    while(pig0->pigname) {
        if(!strcmp(pig0->pigtype, "char")) {
	    newCONSTSUB(pigstash, (char *)pig0->pigname, newSVpv((char *)pig0->pigptr, 0));
	    pig0++;
	    continue;
	}
        pigobj = pig_object_create(pig_map_class(pig0->pigtype), &pigd);
	pigd->pigptr = pig0->pigptr;
	pigd->piginfo = pig_classinfo_fetch(pig0->pigtype);
	pigd->pigflags = PIGOBJECT_CONST;

	newCONSTSUB(pigstash, (char *)pig0->pigname, pigobj);

	pig0++;
    }
}

PIG_DEFINE_VOID_FUNC_2(pig_load_constants, const char *, pig_constant *) {
    if(!pig0 || !pig1) return;

    while(pig1->pigconstantlist) {
        if(pig1->pigtype == PIG_CONSTANT_INT)
	    pig_load_constant_int((pig_constant_int *)pig1->pigconstantlist, pig0);
	else if(pig1->pigtype == PIG_CONSTANT_OBJECT)
	    pig_load_constant_object((pig_constant_object *)pig1->pigconstantlist, pig0);
	pig1++;
    }
}

PIG_EXPORT_TABLE(pigconstant)
    PIG_EXPORT_FUNC(pig_load_constants)
PIG_EXPORT_ENDTABLE
