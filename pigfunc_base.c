/*
 * Definition and export of functions in pigfunc_base.h
 *
 * Copyright (C) 1999, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README.LICENSE file which should be included with this library.
 *
 */

#include "pigperl.h"
#include "pigclassinfo.h"
#include "pigvirtual.h"
#include "pigfunc_base.h"

PIG_DEFINE_VOID_FUNC_1(pig_sub_enter, struct pig_sub_frame *) {
    struct pig_sub_frame *pignode;
    pignode = new pig_sub_frame;
    pignode->pignext = pig_frame;
    pignode->pigscope = 0;
    pignode->pigax = pig0->pigax;
    pig_frame = pignode;
}

PIG_DEFINE_VOID_FUNC_0(pig_sub_leave) {
    struct pig_sub_frame *pignode;
    if(!pig_frame) return;
    pignode = pig_frame;
    pig_frame = pignode->pignext;
    pig_scope_leave(pignode->pigscope);
    delete pignode;
}

PIG_DEFINE_VOID_FUNC_2(pig_begin, void *, const char *) {
    struct pig_sub_frame pigf;
    pigf.pigax = TOPMARK + 1;
    pig_sub_enter(&pigf);

    pig_argument_idx = 0;
    pig_argument_max_idx = PIGstack_sp - (PIGstack_base + TOPMARK);

    pig_depth++;
}

PIG_DEFINE_VOID_FUNC_2(pig_begin_virtual, const class pig_virtual *, const char *) {
    dSP;
    ENTER;
    SAVETMPS;
    PUSHMARK(sp);
    XPUSHs(sv_2mortal(newSVsv((SV *)pig0->pig_rv)));
    //printf("Calling %s::%s\n", HvNAME(SvSTASH(SvRV((SV *)pig0->pig_rv))), pig1);
    PUTBACK;
}

PIG_DEFINE_VOID_FUNC_0(pig_lastargument) {
    dXSARGS;
    pig_argument_idx = 0;
}

PIG_DEFINE_VOID_FUNC_0(pig_end) {
    pig_depth--;
    pig_argument_idx = 0;
    pig_sub_leave();
}

PIG_DEFINE_FUNC_0(int, pig_argumentcount) {
    return pig_argument_max_idx;
}

PIG_DEFINE_FUNC_1(unsigned int, pig_argument_info, int) {
    PIGARGS;
    SV *pigsv = ST(pig0);
    unsigned int pigr = 0;
    if(!SvOK(pigsv)) {
        pigr = PIGTYPE_UNDEF;
    }
    else if(SvROK(pigsv)) {
	if(mg_find(SvRV(pigsv), '~'))
            pigr = PIGTYPE_OBJECT;    // BUGGY ASSUMPTION
    }
    else if(SvIOK(pigsv)) {
        IV pigi = SvIV(pigsv);
	pigr = PIGTYPE_INT;
	if(pigi == 0 || pigi == 1) pigr |= PIGTYPE_BOOL;
    }
    else if(SvNOK(pigsv)) {
        pigr = PIGTYPE_FLOAT;
    }
    else if(SvPOK(pigsv)) {
        pigr = PIGTYPE_STRING;
    }
    else pigr = 0;

    return pigr;
}

PIG_DEFINE_FUNC_2(int, pig_find_in_array, const char *, const char **) {
    int pigidx = 0;
    int pigcur = 0;

    while(pig1[pigidx]) {
        while(pig1[pigidx][pigcur] == pig0[pigcur]) {
	    if(!pig0[pigcur]) {
	        return pigidx;
	    }
	    pigcur++;
	}
	pigcur = 0;
	pigidx++;
    }
    return -1;
}


PIG_DEFINE_VOID_FUNC_2(pig_ambiguous, const char *, const char *) {
    die("Couldn't call %s::%s with your arguments", pig_map_class(pig0), pig1);
}

PIG_DEFINE_VOID_FUNC_2(pig_call_method, const class pig_virtual *, const char *) {
    dSP;
    perl_call_method((char *)pig1, G_DISCARD);
    FREETMPS;
    LEAVE;
}

PIG_DEFINE_VOID_FUNC_2(pig_call_retmethod, const class pig_virtual *, const char *) {
    dSP;
    int pigr = perl_call_method((char *)pig1, G_SCALAR);
    if(pigr < 1) croak("perl_call_method croaked");
    SPAGAIN;
    if(PIG_TOPSTACK) SvREFCNT_dec(PIG_TOPSTACK);
    PIG_TOPSTACK = newSVsv(POPs);
    PUTBACK;
    FREETMPS;
    LEAVE;
}

PIG_DEFINE_VOID_FUNC_0(pig_return_nothing) {
//    dXSARGS;
}

PIG_EXPORT_TABLE(pigfunc_base)
    PIG_EXPORT_FUNC(pig_sub_enter)
    PIG_EXPORT_FUNC(pig_sub_leave)
    PIG_EXPORT_FUNC(pig_begin)
    PIG_EXPORT_FUNC(pig_begin_virtual)
    PIG_EXPORT_FUNC(pig_lastargument)
    PIG_EXPORT_FUNC(pig_end)
    PIG_EXPORT_FUNC(pig_argumentcount)
    PIG_EXPORT_FUNC(pig_argument_info)
    PIG_EXPORT_FUNC(pig_find_in_array)
    PIG_EXPORT_FUNC(pig_ambiguous)
    PIG_EXPORT_FUNC(pig_call_method)
    PIG_EXPORT_FUNC(pig_call_retmethod)
    PIG_EXPORT_FUNC(pig_return_nothing)
PIG_EXPORT_ENDTABLE
