/*
 * PerlQt interface to qbrush.h
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pbrush.h"
#include "pcolor.h"
#include "penum.h"

#define STORE_key(key) enumIV(hv, MSTR(key), key ## Pattern)

inline void init_enum() {
    HV *hv = perl_get_hv("QBrush::Brush", TRUE | GV_ADDMULTI);

    enumIV(hv, "None", NoBrush);
    STORE_key(Solid);
    STORE_key(Dense1);
    STORE_key(Dense2);
    STORE_key(Dense3);
    STORE_key(Dense4);
    STORE_key(Dense5);
    STORE_key(Dense6);
    STORE_key(Dense7);
    STORE_key(Hor);
    STORE_key(Ver);
    STORE_key(Cross);
    STORE_key(BDiag);
    STORE_key(FDiag);
    STORE_key(DiagCross);
    STORE_key(Custom);
}

MODULE = QBrush		PACKAGE = QBrush

PROTOTYPES: DISABLE

BOOT:
    init_enum();

PBrush *
PBrush::new(...)
    CASE: items == 1
	CODE:
	RETVAL = new PBrush();
	OUTPUT:
	RETVAL
    CASE: items == 2 && sv_isobject(ST(1)) && sv_derived_from(ST(1), "QBrush")
	PREINIT:
	QBrush *brush = pextract(QBrush, 1);
	CODE:
	RETVAL = new PBrush(*brush);
	OUTPUT:
	RETVAL
    CASE: items > 2 && sv_isobject(ST(2))
	PREINIT:
	QColor *color = pextract(QColor, 1);
	QPixmap *pixmap = pextract(QPixmap, 2);
	CODE:
	RETVAL = new PBrush(*color, *pixmap);
	OUTPUT:
	RETVAL
    CASE: !sv_isobject(ST(1))
	PREINIT:
	BrushStyle style = (BrushStyle)SvIV(ST(1));
	CODE:
	RETVAL = new PBrush(style);
	OUTPUT:
	RETVAL
    CASE:
	PREINIT:
	QColor *color = pextract(QColor, 1);
	BrushStyle style = (items > 2) ?
	    (BrushStyle)SvIV(ST(2)) : SolidPattern;
	CODE:
	RETVAL = new PBrush(*color, style);
	OUTPUT:
	RETVAL

PColor *
QBrush::color()
    CODE:
    RETVAL = new PColor(THIS->color());
    OUTPUT:
    RETVAL

QPixmap *
QBrush::pixmap()

void
QBrush::setColor(color)
    QColor *color
    CODE:
    THIS->setColor(*color);

void
QBrush::setPixmap(pixmap)
    QPixmap *pixmap
    CODE:
    THIS->setPixmap(*pixmap);

void
QBrush::setStyle(style)
    BrushStyle style

BrushStyle
QBrush::style()


bool
QBrush::beq(brush, misc)
    QBrush *brush
    CODE:
    RETVAL = (*THIS == *brush);
    OUTPUT:
    RETVAL

bool
QBrush::bne(brush, misc)
    QBrush *brush
    CODE:
    RETVAL = (*THIS != *brush);
    OUTPUT:
    RETVAL
