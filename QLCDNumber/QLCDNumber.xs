/*
 * PerlQt interface to qlcdnum.h
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "plcdnum.h"
#include "penum.h"

#define STORE_key(key) enumIV(hv, MSTR(key), QLCDNumber::key)

inline void init_enum() {
    HV *hv = perl_get_hv("QLCDNumber::Mode", TRUE | GV_ADDMULTI);

#undef HEX
#undef DEC
#undef OCT
#undef BIN
    STORE_key(HEX);
    STORE_key(DEC);
    STORE_key(OCT);
    STORE_key(BIN);

    hv = perl_get_hv("QLCDNumber::Segment", TRUE | GV_ADDMULTI);

    STORE_key(Outline);
    STORE_key(Filled);
    STORE_key(Flat);
}

MODULE = QLCDNumber		PACKAGE = QLCDNumber

PROTOTYPES: DISABLE

BOOT:
    init_enum();

PLCDNumber *
PLCDNumber::new(...)
    CASE: items == 1 || sv_isobject(ST(1))
	PREINIT:
	pWidget *parent = (items > 1) ? pextract(pWidget, 1) : 0;
	pChar *name = (items > 2 && SvOK(ST(2))) ? SvPV(ST(2), na) : 0;
	CODE:
	RETVAL = new PLCDNumber(parent, name);
	OUTPUT:
	RETVAL
    CASE:
	PREINIT:
	uint numDigits = SvIV(ST(1));
	pWidget *parent = (items > 2) ? pextract(pWidget, 2) : 0;
	pChar *name = (items > 3 && SvOK(ST(2))) ? SvPV(ST(3), na) : 0;
	CODE:
	RETVAL = new PLCDNumber(numDigits, parent, name);
	OUTPUT:
	RETVAL

void
QLCDNumber::DESTROY()
    CODE:
    if(want_destroy(ST(0)))
	delete THIS;

bool
QLCDNumber::checkOverflow(num)
    CASE: SvIOK(ST(1))
	int num
    CASE:
	double num

void
QLCDNumber::display(value)
    CASE: SvIOK(ST(1))
	int value
    CASE: SvNOK(ST(1))
	double value
    CASE:
	char *value

int
QLCDNumber::intValue()

QLCDNumber::Mode
QLCDNumber::mode()

int
QLCDNumber::numDigits()

QLCDNumber::SegmentStyle
QLCDNumber::segmentStyle()

void
QLCDNumber::setBinMode()

void
QLCDNumber::setDecMode()

void
QLCDNumber::setHexMode()

void
QLCDNumber::setMode(mode)
    QLCDNumber::Mode mode

void
QLCDNumber::setNumDigits(nDigits)
    int nDigits

void
QLCDNumber::setOctMode()

void
QLCDNumber::setSegmentStyle(style)
    QLCDNumber::SegmentStyle style

void
QLCDNumber::setSmallDecimalPoint(b)
    bool b

bool
QLCDNumber::smallDecimalPoint()

double
QLCDNumber::value()


MODULE = QLCDNumber	PACKAGE = QLCDNumber	PREFIX = virtual_

void
pLCDNumber::virtual_drawContents(p)
    QPainter *p

void
pLCDNumber::virtual_resizeEvent(event)
    QResizeEvent *event
