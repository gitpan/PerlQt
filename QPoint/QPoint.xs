/*
 * PerlQt interface to qpoint.h
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "ppoint.h"

MODULE = QPoint		PACKAGE = QPoint

PROTOTYPES: DISABLE

PPoint *
PPoint::new(xpos = 0, ypos = 0)
    CASE: items == 1
	CODE:
	RETVAL = new PPoint();
	OUTPUT:
	RETVAL
    CASE: items == 2
	PREINIT:
	QPoint *point = pextract(QPoint, 1);
	CODE:
	RETVAL = new PPoint(*point);
	OUTPUT:
	RETVAL
    CASE: items > 2
	int xpos
	int ypos

bool
QPoint::isNull()

void
QPoint::setX(x)
    int x

void
QPoint::setY(y)
    int y

int
QPoint::x()

int
QPoint::y()


PPoint *
QPoint::uneg(nil, misc)
    CODE:
    RETVAL = new PPoint(-(*THIS));
    OUTPUT:
    RETVAL

PPoint *
QPoint::bmul(scale, misc)
    int scale
    CODE:
    RETVAL = new PPoint(*THIS * scale);
    OUTPUT:
    RETVAL

PPoint *
QPoint::bdiv(scale, misc)
    int scale
    CODE:
    RETVAL = new PPoint(*THIS / scale);
    OUTPUT:
    RETVAL

PPoint *
QPoint::badd(point, misc)
    QPoint *point
    CODE:
    RETVAL = new PPoint(*THIS + *point);
    OUTPUT:
    RETVAL

PPoint *
QPoint::bsub(point, misc)
    QPoint *point
    CODE:
    RETVAL = new PPoint(*THIS - *point);
    OUTPUT:
    RETVAL

bool
QPoint::beq(point, misc)
    QPoint *point
    CODE:
    RETVAL = (*THIS == *point);
    OUTPUT:
    RETVAL

bool
QPoint::bne(point, misc)
    QPoint *point
    CODE:
    RETVAL = (*THIS != *point);
    OUTPUT:
    RETVAL
