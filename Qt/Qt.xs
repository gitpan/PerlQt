/*
 * PerlQt bootstrap module
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqt.h>

static AV *dynaloaderAV = NULL, *bootstrapAV = NULL;

void pqt_bootstrap(char *classname) {
    dSP;
    ENTER;
    SAVETMPS;
    SV *c = sv_2mortal(newSVpv("Qt::", 0));
    sv_catpv(c, classname);
    int classlen = SvCUR(c);

    sv_catpv(c, "::ISA");
    safe_gv_store(SvPVX(c), dynaloaderAV);
    SvCUR_set(c, classlen);

    PUSHMARK(sp);
    XPUSHs(c);
    PUTBACK;
    perl_call_sv(
	(SV *)GvCV(
	    gv_fetchmethod(gv_stashsv(c, TRUE), "bootstrap")
	), G_DISCARD
    );
    FREETMPS;
    LEAVE;
// MUST FIX %INC!
}

MODULE = Qt		PACKAGE = Qt
PROTOTYPES: DISABLE

BOOT:
{
    dynaloaderAV = newAV();
    bootstrapAV = newAV();
    safe_av_store_new(dynaloaderAV, 0, newSVpv("DynaLoader", 0));
    safe_av_store_new(bootstrapAV, 0, newSVpv("Qt::Bootstrap", 0));
}
{
    char *classes[] = {
	"QApplication",
	"QButton",
	"QObject",
	"QPaintDevice",
	"QPushButton",
	"QWidget",
	NULL
    };
    HV *inchv = GvHVn(incgv);
    SV *c = sv_newmortal();
    SV *found = sv_2mortal(newSVpv("notfound", 0));

    for(int i = 0; classes[i]; i++) {
	int classlen = strlen(classes[i]);
	sv_setpvn(c, classes[i], classlen);

	sv_catpv(c, "::ISA");
	safe_gv_store(SvPVX(c), bootstrapAV);
	SvCUR_set(c, classlen);			// restore class name

	sv_catpv(c, ".pm");
	safe_hv_store(inchv, SvPVX(c), found);	// $INC{$class.pm} = $found;
    }
}

void
import(CLASS, ...)
    char *CLASS
    CODE:
    pqt_bootstrap("QApplication");

MODULE = Qt		PACKAGE = Qt::Bootstrap

void
import(CLASS, ...)
    char *CLASS
    CODE:
    pqt_bootstrap(CLASS);
