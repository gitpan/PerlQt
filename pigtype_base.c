/*
 * Definition and export of types declared in pigtype_base.h
 *
 * Copyright (C) 1999, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README.LICENSE file which should be included with this library.
 *
 */

#include "pigperl.h"
#include "pigtype_base.h"

PIG_DEFINE_TYPE_ARGUMENT(pig_type_bool, bool) {
    PIGARGS;
    bool pigr = SvTRUE(PIG_ARG) ? TRUE : FALSE;
    PIGARGUMENT(pigr);
}

PIG_DEFINE_TYPE_DEFARGUMENT(pig_type_bool, bool) {
    PIGARGS;
    bool pigr = PIG_ARGOK ? (SvTRUE(PIG_ARG) ? TRUE : FALSE) : pig0;
    PIGARGUMENT(pigr);
}

PIG_DEFINE_TYPE_RETURN(pig_type_bool, bool) {
    PIGRET;
    PIGRETURN(sv_mortalcopy(boolSV(pig0)));
}

PIG_DEFINE_TYPE_PUSH(pig_type_bool, bool) {
    PIGPUSHSTACK;
    PIGPUSH(sv_mortalcopy(boolSV(pig0)));
}

PIG_DEFINE_TYPE_POP(pig_type_bool, bool) {
    PIGPOPSTACK;
    bool pigr = SvTRUE(PIG_TOPSTACK) ? TRUE : FALSE;
    PIGPOP(pigr);
}


PIG_DEFINE_TYPE_ARGUMENT(pig_type_char, char) {
    STRLEN n_a;
    PIGARGS;
    char *pigr = SvPV(PIG_ARG, n_a);
    PIGARGUMENT(pigr ? *pigr : 0);
}

PIG_DEFINE_TYPE_DEFARGUMENT(pig_type_char, char) {
    STRLEN n_a;
    PIGARGS;
    char *pigr = (PIG_ARGOK && SvOK(PIG_ARG)) ? SvPV(PIG_ARG, n_a) : &pig0;
    PIGARGUMENT(pigr ? *pigr : 0);
}

PIG_DEFINE_TYPE_RETURN(pig_type_char, char) {
    PIGRET;
    char pigr[2];
    pigr[0] = pig0;
    pigr[1] = 0;
    PIGRETURN(sv_2mortal(newSVpv(pigr, 0)));
}

PIG_DEFINE_TYPE_PUSH(pig_type_char, char) {
    PIGPUSHSTACK;
    char pigr[2];
    pigr[0] = pig0;
    pigr[1] = 0;
    PIGPUSH(sv_2mortal(newSVpv(pigr, 0)));
}

PIG_DEFINE_TYPE_POP(pig_type_char, char) {
    STRLEN n_a;
    PIGPOPSTACK;
    char *pigr = SvPV(PIG_TOPSTACK, n_a);
    PIGPOP(pigr ? *pigr : 0);
}


PIG_DEFINE_TYPE_ARGUMENT(pig_type_cstring, const char *) {
    STRLEN n_a;
    PIGARGS;
    const char *pigr = PIG_ARGOK ? SvPV(PIG_ARG, n_a) : 0;
    PIGARGUMENT(pigr);
}

PIG_DEFINE_TYPE_DEFARGUMENT(pig_type_cstring, const char *) {
    STRLEN n_a;
    PIGARGS;
    const char *pigr = PIG_ARGOK ? SvPV(PIG_ARG, n_a) : pig0;
    PIGARGUMENT(pigr);
}

PIG_DEFINE_TYPE_RETURN(pig_type_cstring, const char *) {
    PIGRET;
    PIGRETURN(pig0 ?
	      sv_2mortal(newSVpv((char *)pig0, 0)) :
	      sv_mortalcopy(&PIGsv_undef));
}

PIG_DEFINE_TYPE_PUSH(pig_type_cstring, const char *) {
    PIGPUSHSTACK;
    PIGPUSH(pig0 ?
	    sv_2mortal(newSVpv((char *)pig0, 0)) :
	    sv_mortalcopy(&PIGsv_undef));
}

PIG_DEFINE_TYPE_POP(pig_type_cstring, const char *) {
    STRLEN n_a;
    PIGPOPSTACK;
    const char *pigr = SvPV(PIG_TOPSTACK, n_a);
    PIGPOP(pigr);
}


PIG_DEFINE_TYPE_ARGUMENT(pig_type_double, double) {
    PIGARGS;
    double pigr = SvNV(PIG_ARG);
    PIGARGUMENT(pigr);
}

PIG_DEFINE_TYPE_DEFARGUMENT(pig_type_double, double) {
    PIGARGS;
    double pigr = PIG_ARGOK ? SvNV(PIG_ARG) : pig0;
    PIGARGUMENT(pigr);
}

PIG_DEFINE_TYPE_RETURN(pig_type_double, double) {
    PIGRET;
    PIGRETURN(sv_2mortal(newSVnv(pig0)));
}

PIG_DEFINE_TYPE_PUSH(pig_type_double, double) {
    PIGPUSHSTACK;
    PIGPUSH(sv_2mortal(newSVnv(pig0)));
}

PIG_DEFINE_TYPE_POP(pig_type_double, double) {
    PIGPOPSTACK;
    double pigr = SvNV(PIG_TOPSTACK);
    PIGPOP(pigr);
}


PIG_DEFINE_TYPE_ARGUMENT(pig_type_long_double, long double) {
    PIGARGS;
    long double pigr = SvNV(PIG_ARG);
    PIGARGUMENT(pigr);
}

PIG_DEFINE_TYPE_DEFARGUMENT(pig_type_long_double, long double) {
    PIGARGS;
    long double pigr = PIG_ARGOK ? SvNV(PIG_ARG) : pig0;
    PIGARGUMENT(pigr);
}

PIG_DEFINE_TYPE_RETURN(pig_type_long_double, long double) {
    PIGRET;
    PIGRETURN(sv_2mortal(newSVnv(pig0)));
}

PIG_DEFINE_TYPE_PUSH(pig_type_long_double, long double) {
    PIGPUSHSTACK;
    PIGPUSH(sv_2mortal(newSVnv(pig0)));
}

PIG_DEFINE_TYPE_POP(pig_type_long_double, long double) {
    PIGPOPSTACK;
    long double pigr = SvNV(PIG_TOPSTACK);
    PIGPOP(pigr);
}


PIG_DEFINE_TYPE_ARGUMENT(pig_type_float, float) {
    PIGARGS;
    float pigr = SvNV(PIG_ARG);
    PIGARGUMENT(pigr);
}

PIG_DEFINE_TYPE_DEFARGUMENT(pig_type_float, float) {
    PIGARGS;
    float pigr = PIG_ARGOK ? SvNV(PIG_ARG) : pig0;
    PIGARGUMENT(pigr);
}

PIG_DEFINE_TYPE_RETURN(pig_type_float, float) {
    PIGRET;
    PIGRETURN(sv_2mortal(newSVnv(pig0)));
}

PIG_DEFINE_TYPE_PUSH(pig_type_float, float) {
    PIGPUSHSTACK;
    PIGPUSH(sv_2mortal(newSVnv(pig0)));
}

PIG_DEFINE_TYPE_POP(pig_type_float, float) {
    PIGPOPSTACK;
    float pigr = SvNV(PIG_TOPSTACK);
    PIGPOP(pigr);
}


PIG_DEFINE_TYPE_ARGUMENT(pig_type_int, int) {
    PIGARGS;
    int pigr = SvIV(PIG_ARG);
    PIGARGUMENT(pigr);
}

PIG_DEFINE_TYPE_DEFARGUMENT(pig_type_int, int) {
    PIGARGS;
    int pigr = PIG_ARGOK ? SvIV(PIG_ARG) : pig0;
    PIGARGUMENT(pigr);
}

PIG_DEFINE_TYPE_RETURN(pig_type_int, int) {
    PIGRET;
    PIGRETURN(sv_2mortal(newSViv(pig0)));
}

PIG_DEFINE_TYPE_PUSH(pig_type_int, int) {
    PIGPUSHSTACK;
    PIGPUSH(sv_2mortal(newSViv(pig0)));
}

PIG_DEFINE_TYPE_POP(pig_type_int, int) {
    PIGPOPSTACK;
    int pigr = SvIV(PIG_TOPSTACK);
    PIGPOP(pigr);
}


PIG_DEFINE_TYPE_ARGUMENT(pig_type_long, long) {
    PIGARGS;
    long pigr = SvIV(PIG_ARG);
    PIGARGUMENT(pigr);
}

PIG_DEFINE_TYPE_DEFARGUMENT(pig_type_long, long) {
    PIGARGS;
    long pigr = PIG_ARGOK ? SvIV(PIG_ARG) : pig0;
    PIGARGUMENT(pigr);
}

PIG_DEFINE_TYPE_RETURN(pig_type_long, long) {
    PIGRET;
    PIGRETURN(sv_2mortal(newSViv(pig0)));
}

PIG_DEFINE_TYPE_PUSH(pig_type_long, long) {
    PIGPUSHSTACK;
    PIGPUSH(sv_2mortal(newSViv(pig0)));
}

PIG_DEFINE_TYPE_POP(pig_type_long, long) {
    PIGPOPSTACK;
    long pigr = SvIV(PIG_TOPSTACK);
    PIGPOP(pigr);
}


PIG_DEFINE_TYPE_ARGUMENT(pig_type_short, short) {
    PIGARGS;
    short pigr = SvIV(PIG_ARG);
    PIGARGUMENT(pigr);
}

PIG_DEFINE_TYPE_DEFARGUMENT(pig_type_short, short) {
    PIGARGS;
    short pigr = PIG_ARGOK ? SvIV(PIG_ARG) : pig0;
    PIGARGUMENT(pigr);
}

PIG_DEFINE_TYPE_RETURN(pig_type_short, short) {
    PIGRET;
    PIGRETURN(sv_2mortal(newSViv(pig0)));
}

PIG_DEFINE_TYPE_PUSH(pig_type_short, short) {
    PIGPUSHSTACK;
    PIGPUSH(sv_2mortal(newSViv(pig0)));
}

PIG_DEFINE_TYPE_POP(pig_type_short, short) {
    PIGPOPSTACK;
    short pigr = SvIV(PIG_TOPSTACK);
    PIGPOP(pigr);
}


PIG_DEFINE_TYPE_ARGUMENT(pig_type_ptr, void *) {
    PIGARGS;
    void *pigr = (void *)SvIV(PIG_ARG);
    PIGARGUMENT(pigr);
}

PIG_DEFINE_TYPE_DEFARGUMENT(pig_type_ptr, void *) {
    PIGARGS;
    void *pigr = PIG_ARGOK ? (void *)SvIV(PIG_ARG) : pig0;
    PIGARGUMENT(pigr);
}

PIG_DEFINE_TYPE_RETURN(pig_type_ptr, void *) {
    PIGRET;
    PIGRETURN(sv_2mortal(newSViv((IV)pig0)));
}

PIG_DEFINE_TYPE_PUSH(pig_type_ptr, void *) {
    PIGPUSHSTACK;
    PIGPUSH(sv_2mortal(newSViv((IV)pig0)));
}

PIG_DEFINE_TYPE_POP(pig_type_ptr, void *) {
    PIGPOPSTACK;
    void *pigr = (void *)SvIV(PIG_TOPSTACK);
    PIGPOP(pigr);
}

struct _pig_type_boolptr_variable {
    SV *pigsv;
    bool pigvar;
};

PIG_DEFINE_SCOPE_ARGUMENT(pig_type_boolptr) {
    _pig_type_boolptr_variable *pigr = (_pig_type_boolptr_variable *)pig0;
    sv_setsv(pigr->pigsv, pigr->pigvar ? &PIGsv_yes : &PIGsv_no);
    delete pigr;
}

PIG_DEFINE_TYPE_ARGUMENT(pig_type_boolptr, void *) {
    PIGARGS;
    if(PIG_ARGOK) {
	_pig_type_boolptr_variable *pigr = new _pig_type_boolptr_variable;
	pigr->pigsv = PIG_ARG;
	pigr->pigvar = SvTRUE(PIG_ARG) ? TRUE : FALSE;
	PIGSCOPE_ARGUMENT(pig_type_boolptr, pigr);
	PIGARGUMENT(&pigr->pigvar);
    } else {
	PIGARGUMENT(0);
    }
}

PIG_DEFINE_TYPE_DEFARGUMENT(pig_type_boolptr, bool *) {
    PIGARGS;
    if(PIG_ARGOK) {
	_pig_type_boolptr_variable *pigr = new _pig_type_boolptr_variable;
	pigr->pigsv = PIG_ARG;
	pigr->pigvar = SvTRUE(PIG_ARG) ? TRUE : FALSE;
	PIGSCOPE_ARGUMENT(pig_type_boolptr, pigr);
	PIGARGUMENT(&pigr->pigvar);
    } else {
	PIGARGUMENT(pig0);
    }
}

PIG_DEFINE_TYPE_RETURN(pig_type_boolptr, bool *) {
    PIGRET;
    PIGRETURN(sv_mortalcopy(pig0 ? boolSV(*pig0) : &PIGsv_undef));
}

PIG_DEFINE_TYPE_PUSH(pig_type_boolptr, bool *) {
    PIGPUSHSTACK;
    PIGPUSH(sv_mortalcopy(pig0 ? boolSV(*pig0) : &PIGsv_undef));
}

PIG_DEFINE_STUB_POP(pig_type_boolptr, bool *)


struct _pig_type_intptr_variable {
    SV *pigsv;
    int pigvar;
};

PIG_DEFINE_SCOPE_ARGUMENT(pig_type_intptr) {
    _pig_type_intptr_variable *pigr = (_pig_type_intptr_variable *)pig0;
    sv_setiv(pigr->pigsv, pigr->pigvar);
    delete pigr;
};

PIG_DEFINE_TYPE_ARGUMENT(pig_type_intptr, int *) {
    PIGARGS;
    if(PIG_ARGOK) {
	_pig_type_intptr_variable *pigr = new _pig_type_intptr_variable;
	pigr->pigsv = PIG_ARG;
	pigr->pigvar = SvIV(PIG_ARG);
	PIGSCOPE_ARGUMENT(pig_type_intptr, pigr);
	PIGARGUMENT(&pigr->pigvar);
    } else {
	PIGARGUMENT(0);
    }
}

PIG_DEFINE_TYPE_DEFARGUMENT(pig_type_intptr, int *) {
    PIGARGS;
    if(PIG_ARGOK) {
	_pig_type_intptr_variable *pigr = new _pig_type_intptr_variable;
	pigr->pigsv = PIG_ARG;
	pigr->pigvar = SvIV(PIG_ARG);
	PIGSCOPE_ARGUMENT(pig_type_intptr, pigr);
	PIGARGUMENT(&pigr->pigvar);
    } else {
	PIGARGUMENT(pig0);
    }
}

PIG_DEFINE_TYPE_RETURN(pig_type_intptr, int *) {
    PIGRET;
    PIGRETURN(pig0 ? sv_2mortal(newSViv(*pig0)) : sv_mortalcopy(&PIGsv_undef));
}

PIG_DEFINE_TYPE_PUSH(pig_type_intptr, int *) {
    PIGPUSHSTACK;
    PIGPUSH(pig0 ? sv_2mortal(newSViv(*pig0)) : sv_mortalcopy(&PIGsv_undef));
}

PIG_DEFINE_STUB_POP(pig_type_intptr, int *)


struct _pig_type_floatptr_variable {
    SV *pigsv;
    float pigvar;
};

PIG_DEFINE_SCOPE_ARGUMENT(pig_type_floatptr) {
    _pig_type_floatptr_variable *pigr = (_pig_type_floatptr_variable *)pig0;
    sv_setnv(pigr->pigsv, pigr->pigvar);
    delete pigr;
};

PIG_DEFINE_TYPE_ARGUMENT(pig_type_floatptr, float *) {
    PIGARGS;
    if(PIG_ARGOK) {
	_pig_type_floatptr_variable *pigr = new _pig_type_floatptr_variable;
	pigr->pigsv = PIG_ARG;
	pigr->pigvar = SvNV(PIG_ARG);
	PIGSCOPE_ARGUMENT(pig_type_floatptr, pigr);
	PIGARGUMENT(&pigr->pigvar);
    } else {
	PIGARGUMENT(0);
    }
}

PIG_DEFINE_TYPE_DEFARGUMENT(pig_type_floatptr, float *) {
    PIGARGS;
    if(PIG_ARGOK) {
	_pig_type_floatptr_variable *pigr = new _pig_type_floatptr_variable;
	pigr->pigsv = PIG_ARG;
	pigr->pigvar = SvNV(PIG_ARG);
	PIGSCOPE_ARGUMENT(pig_type_floatptr, pigr);
	PIGARGUMENT(&pigr->pigvar);
    } else {
	PIGARGUMENT(pig0);
    }
}

PIG_DEFINE_TYPE_RETURN(pig_type_floatptr, float *) {
    PIGRET;
    PIGRETURN(pig0 ? sv_2mortal(newSVnv(*pig0)) : sv_mortalcopy(&PIGsv_undef));
}

PIG_DEFINE_TYPE_PUSH(pig_type_floatptr, float *) {
    PIGPUSHSTACK;
    PIGPUSH(pig0 ? sv_2mortal(newSVnv(*pig0)) : sv_mortalcopy(&PIGsv_undef));
}

PIG_DEFINE_STUB_POP(pig_type_floatptr, float *)


PIG_DEFINE_SCOPE_ARGUMENT(pig_type_shortarray) {
    delete[] (short *)pig0;
}

PIG_DEFINE_TYPE_ARGUMENT(pig_type_shortarray, short *) {
    PIGARGS;
    AV *pigav;
    SV **pigsvp;
    I32 pigcnt, pigidx;
    short *pigr;

    if(!SvOK(PIG_ARG))
        return 0;
    if(!SvROK(PIG_ARG) || SvTYPE(SvRV(PIG_ARG)) != SVt_PVAV) {
        if(PIGdowarn)
           warn("Argument must be an array reference, not a list");
       return 0;
    }

    pigav = (AV *)SvRV(PIG_ARG);
    pigcnt = av_len(pigav);
    pigr = new short[pigcnt + 2];

    for(pigidx = 0; pigidx <= pigcnt; pigidx++) {
        pigsvp = av_fetch(pigav, pigidx, 0);
       if(!pigsvp) continue;
        pigr[pigidx] = (short)SvIV(*pigsvp);
    }

    pigr[pigidx] = 0;    // Might as well zero-terminated?

    PIGSCOPE_ARGUMENT(pig_type_shortarray, pigr);
    PIGARGUMENT(pigr);
}

PIG_DEFINE_STUB_DEFARGUMENT(pig_type_shortarray, short *)
PIG_DEFINE_STUB_RETURN(pig_type_shortarray, short *)
PIG_DEFINE_STUB_PUSH(pig_type_shortarray, short *)
PIG_DEFINE_STUB_POP(pig_type_shortarray, short *)


PIG_DEFINE_TYPE_ARGUMENT2(pig_type_shortarrayitems, int, int) {
    PIGARGS;
    SV *pigarg = ST(pig0);
    if(!SvOK(pigarg) || !SvROK(pigarg) || SvTYPE(SvRV(pigarg)) != SVt_PVAV)
        return 0;

    // This does not move us to the next ST() argument
    return av_len((AV *)SvRV(pigarg)) + 1;
}

PIG_DEFINE_STUB_DEFARGUMENT(pig_type_shortarrayitems, int)
PIG_DEFINE_STUB_RETURN(pig_type_shortarrayitems, int)
PIG_DEFINE_STUB_PUSH(pig_type_shortarrayitems, int)
PIG_DEFINE_STUB_POP(pig_type_shortarrayitems, int)


PIG_DEFINE_TYPE(pig_type_bool)
PIG_DEFINE_TYPE(pig_type_char)
PIG_DEFINE_TYPE(pig_type_cstring)
PIG_DEFINE_TYPE(pig_type_double)
PIG_DEFINE_TYPE(pig_type_long_double)
PIG_DEFINE_TYPE(pig_type_int)
PIG_DEFINE_TYPE(pig_type_float)
PIG_DEFINE_TYPE(pig_type_long)
PIG_DEFINE_TYPE(pig_type_short)
PIG_DEFINE_TYPE(pig_type_ptr)
PIG_DEFINE_TYPE(pig_type_boolptr)
PIG_DEFINE_TYPE(pig_type_intptr)
PIG_DEFINE_TYPE(pig_type_floatptr)
PIG_DEFINE_TYPE(pig_type_shortarray)
PIG_DEFINE_TYPE(pig_type_shortarrayitems)


PIG_EXPORT_TABLE(pigtype_base)
    PIG_EXPORT_TYPE(pig_type_bool, "bool")
    PIG_EXPORT_TYPE(pig_type_char, "char")
    PIG_EXPORT_TYPE(pig_type_cstring, "const char*")
    PIG_EXPORT_TYPE(pig_type_double, "double")
    PIG_EXPORT_TYPE(pig_type_long_double, "long double")
    PIG_EXPORT_TYPE(pig_type_float, "float")
    PIG_EXPORT_TYPE(pig_type_int, "int")
    PIG_EXPORT_TYPE(pig_type_int, "enum")
    PIG_EXPORT_TYPE(pig_type_int, "uint")
    PIG_EXPORT_TYPE(pig_type_long, "long")
    PIG_EXPORT_TYPE(pig_type_short, "short")
    PIG_EXPORT_TYPE(pig_type_ptr, "*")
    PIG_EXPORT_TYPE(pig_type_boolptr, "bool*")
    PIG_EXPORT_TYPE(pig_type_intptr, "int*")
    PIG_EXPORT_TYPE(pig_type_floatptr, "float*")
    PIG_EXPORT_TYPE(pig_type_shortarray, "short[]")
    PIG_EXPORT_TYPE(pig_type_shortarrayitems, "sizeof(short[])")
PIG_EXPORT_ENDTABLE
