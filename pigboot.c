/*
 * Bootstrap for PerlQt
 *
 * Copyright (C) 1999, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README.LICENSE file which should be included with this library.
 *
 */

#include "pig_QApplication.h"
#include "pigperl.h"
#include "pigsymbol.h"
#include "pigclassinfo.h"
#include "pigconstant.h"

PIG_DECLARE_IMPORT_TABLE(pig)
PIG_DECLARE_EXPORT_TABLE(PIG_Qt)
PIG_DECLARE_EXPORT_TABLE(pigclassinfo)
PIG_DECLARE_EXPORT_TABLE(pigconstant)
PIG_DECLARE_EXPORT_TABLE(pigfunc_base)
PIG_DECLARE_EXPORT_TABLE(pigfunc_object)
PIG_DECLARE_EXPORT_TABLE(pigfunc_qt)
PIG_DECLARE_EXPORT_TABLE(pigobject)
PIG_DECLARE_EXPORT_TABLE(pigperl)
PIG_DECLARE_EXPORT_TABLE(pigproto)
PIG_DECLARE_EXPORT_TABLE(pigtype_base)
PIG_DECLARE_EXPORT_TABLE(pigtype_object)
PIG_DECLARE_EXPORT_TABLE(pigtype_qt)
PIG_DECLARE_EXPORT_TABLE(pigvirtual)

PIG_GLOBAL_EXPORT_TABLE(pig)
    PIG_EXPORT_SUBTABLE(PIG_Qt)
    PIG_EXPORT_SUBTABLE(pigclassinfo)
    PIG_EXPORT_SUBTABLE(pigconstant)
    PIG_EXPORT_SUBTABLE(pigobject)
    PIG_EXPORT_SUBTABLE(pigperl)
    PIG_EXPORT_SUBTABLE(pigproto)
    PIG_EXPORT_SUBTABLE(pigvirtual)

    PIG_EXPORT_SUBTABLE(pigfunc_base)
    PIG_EXPORT_SUBTABLE(pigfunc_object)
    PIG_EXPORT_SUBTABLE(pigfunc_qt)
    PIG_EXPORT_SUBTABLE(pigtype_base)
    PIG_EXPORT_SUBTABLE(pigtype_object)
    PIG_EXPORT_SUBTABLE(pigtype_qt)
PIG_EXPORT_ENDTABLE

extern struct pig_constant PIG_constant_Qt[];
extern struct pig_classinfo PIG_module[];

extern "C" XS(PIG_Qt__signals_import);
extern "C" XS(PIG_Qt__slots_import);

static char **pig_create_stringarray_from_av(AV *pigav, int &pigcount) {
    char **pigarray;
    I32 pigcnt, pigidx, pigarg;
    STRLEN n_a;

    pigcnt = av_len(pigav);
    pigarray = new char *[pigcnt + 2];
    pigarg = 0;
    for(pigidx = 0; pigidx <= pigcnt; pigidx++) {
        SV **pigsvp = av_fetch(pigav, pigidx, 0);
	if(pigsvp)
	    pigarray[pigarg++] = SvPV(*pigsvp, n_a);
    }
    pigarray[pigarg] = 0;
    pigcount = pigarg;
    return pigarray;
}
/*
static char **pig_assign_av_from_stringarray(char *pigarray) {

}
*/
extern "C" XS(PIG_QApplication_new) {
    dXSARGS;
    const char *pigclass;
    AV *pigargs;
    STRLEN n_a;

    if(items < 1 || items > 2)
        die("QApplication::new");

    pigclass = SvPV(ST(0), n_a);

    if(!SvROK(ST(1))) {
        pigargs = newAV();
	die("Needed an argument\n");
	// must do something here!!!
    } else {
        pigargs = (AV *)SvRV(ST(1));
	SvREFCNT_inc((SV *)pigargs);
    }

    av_unshift(pigargs, 1);
    av_store(pigargs, 0, newSVsv(perl_get_sv((char *)"0", TRUE)));

    char **pigargv;
    int pigargc;
    pigargv = pig_create_stringarray_from_av(pigargs, pigargc);
    av_shift(pigargs);

    QApplication *pigapp = new pig_enhanced_QApplication(pigargc, pigargv);

    ST(0) = pig_new_castobject(pigapp, "QApplication", pigclass);

    SvREFCNT_dec(pigargs);
    XSRETURN(1);
}

SV *gv_store(const char *name, SV *value) {    // kludge
    GV *gv = gv_fetchpv((char *)name, TRUE | GV_ADDMULTI, SVt_PVGV);
    SvREFCNT_inc(value);
    if(GvSV(gv)) SvREFCNT_dec(GvSV(gv));
    GvSV(gv) = value;
    GvIMPORTED_SV_on(gv);
    return value;
}

extern "C" XS(PIG_app_import) {
    dXSARGS;
    const char *pigclass = HvNAME(PIGcurcop->cop_stash);
    char *pigvar;
    SV *pigsv;
    SV *pigapp;

    pigapp = perl_get_sv((char *)"Qt::app", FALSE);
    if(!pigapp || !SvOK(pigapp)) {
        AV *pigargv;
	int pigcount;
	pigargv = perl_get_av((char *)"ARGV", TRUE);

	ENTER;
	SAVETMPS;
        PUSHMARK(sp);
	XPUSHs(sv_2mortal(newSVpv((char *)pig_map_class("QApplication"), 0)));
	XPUSHs(sv_2mortal(newRV((SV *)pigargv)));
	PUTBACK;

//warn("Calling QApplication::new\n");

	pigcount = perl_call_method((char *)"new", G_SCALAR);

	SPAGAIN;

	if(pigcount != 1)
	    croak("Cannot call %s::new\n", pig_map_class("QApplication"));

	pigapp = perl_get_sv((char *)"Qt::app", TRUE | GV_ADDMULTI);
	sv_setsv(pigapp, POPs);

	PUTBACK;
	FREETMPS;
	LEAVE;
    }

    pigvar = new char[strlen(pigclass) + 7];
    sprintf(pigvar, "%s::app", pigclass);
    gv_store(pigvar, pigapp);
    SvREFCNT_dec(pigapp);
    delete [] pigvar;

    XSRETURN_EMPTY;
}

void __pig_module_used(const char *pig0) {
    char *pigpm, *pigs;
    pigpm = new char [strlen(pig0) + 4];
    pigs = pigpm;
    while(*pig0) {
        if(*pig0 == ':' && *(pig0 + 1) == ':') {
	    *pigs = '/';
	    pig0++;
	} else {
	    *pigs = *pig0;
	}

	pigs++;
	pig0++;
    }
    strcpy(pigs, ".pm");

//warn("$INC{\"%s\"} = \"%s\";\n", pigpm, __FILE__);

    HV *pighv_inc = perl_get_hv((char *)"main::INC", TRUE);
    hv_store(pighv_inc, pigpm, strlen(pigpm), newSVpv((char *)__FILE__, 0), 0);
}

extern "C" XS(PIG_Qt_import) {
    dXSARGS;
    const char *pigclass = HvNAME(PIGcurcop->cop_stash);
    char *pigvar;

    pigvar = new char [strlen(pigclass) + 7];
    sprintf(pigvar, "%s::app", pigclass);
    perl_get_sv(pigvar, TRUE | GV_ADDMULTI);    // No warnings
    delete [] pigvar;
}

extern "C" XS(boot_Qt) {
    dXSARGS;
    
    pig_symbol_exchange(PIG_EXPORTTABLE(pig), PIG_IMPORTTABLE(pig), "Qt");

    __pig_module_used("Qt::app");

    __pig_module_used("Qt::signals");
    __pig_module_used("Qt::slots");
    newXS((char *)"Qt::signals::import", PIG_Qt__signals_import, (char *)__FILE__);
    newXS((char *)"Qt::slots::import", PIG_Qt__slots_import, (char *)__FILE__);

    pig_load_classinfo(PIG_module);
    pig_load_constants("Qt", PIG_constant_Qt);
//    newXS("Qt::Application::new", PIG_QApplication_new, __FILE__);
    newXS((char *)"Qt::app::import", PIG_app_import, (char *)__FILE__);
    newXS((char *)"Qt::import", PIG_Qt_import, (char *)__FILE__);

    XSRETURN_UNDEF;
}

/*
    pig_classinfo *piginfo = PIG_module;
    while(piginfo->pigclassname) {
	const char *pigmap = pig_map_class(piginfo->pigclassname);

	pig_classinfo_store(piginfo->pigclassname, piginfo);

	pig_load_constants(pigmap, piginfo->pigconstant);
	pig_load_methods(pigmap, piginfo->pigmethodlist);
	pig_load_isa(pigmap, piginfo->pigisa);

	piginfo++;
    }
*/
