/*
 * PerlQt interface to qsize.h
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "psize.h"

MODULE = QSize		PACKAGE = QSize

PROTOTYPES: DISABLE

PSize *
PSize::new(...)
    CASE: items == 1
	CODE:
	RETVAL = new PSize();
	OUTPUT:
	RETVAL
    CASE: items == 2
	QSize *size = pextract(QSize, 1);
	CODE:
	RETVAL = new PSize(*size);
	OUTPUT:
	RETVAL
    CASE: items > 2
	CODE:
	RETVAL = new PSize(SvIV(ST(1)), SvIV(ST(2)));
	OUTPUT:
	RETVAL

int
QSize::height()

bool
QSize::isEmpty()

bool
QSize::isNull()

bool
QSize::isValid()

void
QSize::setHeight(h)
    int h

void
QSize::setWidth(w)
    int w

int
QSize::width()


PSize *
QSize::bmul(scale, misc)
    int scale
    CODE:
    RETVAL = new PSize(*THIS * scale);
    OUTPUT:
    RETVAL

PSize *
QSize::bdiv(scale, misc)
    int scale
    CODE:
    RETVAL = new PSize(*THIS / scale);
    OUTPUT:
    RETVAL

PSize *
QSize::badd(size, misc)
    QSize *size
    CODE:
    RETVAL = new PSize(*THIS + *size);
    OUTPUT:
    RETVAL

PSize *
QSize::bsub(size, misc)
    QSize *size
    CODE:
    RETVAL = new PSize(*THIS - *size);
    OUTPUT:
    RETVAL

bool
QSize::beq(size, misc)
    QSize *size
    CODE:
    RETVAL = (*THIS == *size);
    OUTPUT:
    RETVAL

bool
QSize::bne(size, misc)
    QSize *size
    CODE:
    RETVAL = (*THIS != *size);
    OUTPUT:
    RETVAL

