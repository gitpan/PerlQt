/*
 * PerlQt interface to qpen.h
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "ppen.h"
#include "pcolor.h"
#include "penum.h"

#define STORE_key(key) enumIV(hv, MSTR(key), key ## Line)

inline void init_enum() {
    HV *hv = perl_get_hv("QPen::Pen", TRUE | GV_ADDMULTI);

    enumIV(hv, "None", NoPen);
    STORE_key(Solid);
    STORE_key(Dash);
    STORE_key(Dot);
    STORE_key(DashDot);
    STORE_key(DashDotDot);
}

MODULE = QPen		PACKAGE = QPen

PROTOTYPES: DISABLE

BOOT:
    init_enum();

PPen *
PPen::new(...)
    CASE: items == 1
	CODE:
	RETVAL = new PPen();
	OUTPUT:
	RETVAL
    CASE: items == 2 && sv_isobject(ST(1)) && sv_derived_from(ST(1), "QPen")
	PREINIT:
	QPen *pen = pextract(QPen, 1);
	CODE:
	RETVAL = new PPen(*pen);
	OUTPUT:
	RETVAL
    CASE: !sv_isobject(ST(1))
	PREINIT:
	PenStyle style = (PenStyle)SvIV(ST(1));
	CODE:
	RETVAL = new PPen(style);
	OUTPUT:
	RETVAL
    CASE:
	PREINIT:
	QColor *color = pextract(QColor, 1);
	uint width = (items > 2) ? SvIV(ST(2)) : 0;
	PenStyle style = (items > 3) ? (PenStyle)SvIV(ST(3)) : SolidLine;
	CODE:
	RETVAL = new PPen(*color, width, style);
	OUTPUT:
	RETVAL

void
QPen::DESTROY()
    CODE:
    if(want_destroy(ST(0)))
	delete THIS;

PColor *
QPen::color()
    CODE:
    RETVAL = new PColor(THIS->color());
    OUTPUT:
    RETVAL

void
QPen::setColor(color)
    QColor *color
    CODE:
    THIS->setColor(*color);

void
QPen::setStyle(style)
    PenStyle style

void
QPen::setWidth(width)
    uint width

PenStyle
QPen::style()

uint
QPen::width()


bool
QPen::beq(pen, misc)
    QPen *pen
    CODE:
    RETVAL = (*THIS == *pen);
    OUTPUT:
    RETVAL

bool
QPen::bne(pen, misc)
    QPen *pen
    CODE:
    RETVAL = (*THIS != *pen);
    OUTPUT:
    RETVAL
