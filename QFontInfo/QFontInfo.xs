/*
 * PerlQt interface to qfontinf.h
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pfontinf.h"
#include "pfont.h"

MODULE = QFontInfo		PACKAGE = QFontInfo

PROTOTYPES: DISABLE

PFontInfo *
PFontInfo::new(copy)
    CASE: sv_isobject(ST(1)) && sv_derived_from(ST(1), "QFont")
	PREINIT:
	QFont *font = pextract(QFont, 1);
	CODE:
	RETVAL = new PFontInfo(*font);
	OUTPUT:
	RETVAL
    CASE: sv_isobject(ST(1)) && sv_derived_from(ST(1), "QFontInfo")
	PREINIT:
	QFontInfo *fontinf = pextract(QFontInfo, 1);
	CODE:
	RETVAL = new PFontInfo(*fontinf);
	OUTPUT:
	RETVAL

void
QFontInfo::DESTROY()
    CODE:
    if(want_destroy(ST(0)))
	delete THIS;

bool
QFontInfo::bold()

QFont::CharSet
QFontInfo::charSet()

bool
QFontInfo::exactMatch()

const char *
QFontInfo::family()

bool
QFontInfo::fixedPitch()

PFont *
QFontInfo::font()
    CODE:
    RETVAL = new PFont(THIS->font());
    OUTPUT:
    RETVAL

bool
QFontInfo::italic()

int
QFontInfo::pointSize()

bool
QFontInfo::rawMode()

bool
QFontInfo::strikeOut()

QFont::StyleHint
QFontInfo::styleHint()

bool
QFontInfo::underline()

int
QFontInfo::weight()