/*
 * PerlQt interface to qfontmet.h
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pfontmet.h"
#include "pfont.h"
#include "prect.h"

MODULE = QFontMetrics		PACKAGE = QFontMetrics

PROTOTYPES: DISABLE

PFontMetrics *
PFontMetrics::new(copy)
    CASE: sv_isobject(ST(1)) && sv_derived_from(ST(1), "QFont")
	PREINIT:
	QFont *font = pextract(QFont, 1);
	CODE:
	RETVAL = new PFontMetrics(*font);
	OUTPUT:
	RETVAL
    CASE: sv_isobject(ST(1)) && sv_derived_from(ST(1), "QFontMetrics")
	PREINIT:
	QFontMetrics *fontmet = pextract(QFontMetrics, 1);
	CODE:
	RETVAL = new PFontMetrics(*fontmet);
	OUTPUT:
	RETVAL

void
QFontMetrics::DESTROY()
    CODE:
    if(want_destroy(ST(0)))
	delete THIS;

int
QFontMetrics::ascent()

PRect *
QFontMetrics::boundingRect(str, len = -1)
    char *str
    int len
    CODE:
    RETVAL = new PRect(THIS->boundingRect(str, len));
    OUTPUT:
    RETVAL

int
QFontMetrics::descent()

PFont *
QFontMetrics::font()
    CODE:
    RETVAL = new PFont(THIS->font());
    OUTPUT:
    RETVAL

int
QFontMetrics::height()

int
QFontMetrics::leading()

int
QFontMetrics::lineSpacing()

int
QFontMetrics::lineWidth()

int
QFontMetrics::maxWidth()

int
QFontMetrics::strikeOutPos()

int
QFontMetrics::underlinePos()

int
QFontMetrics::width(str, len = -1)
    char *str
    int len
