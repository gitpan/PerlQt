#ifndef PLCDNUM_H
#define PLCDNUM_H

/*
 * Declaration of the PLCDNumber class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qlcdnum.h"
#include "pframe.h"

#define QLCDNumber_virtual_functions QFrame_virtual_functions

class PLCDNumber_virtualize : public PFrame_virtualize {};

class PLCDNumber : public QLCDNumber, public PLCDNumber_virtualize {
    QLCDNumber_virtual_functions
public:
    PLCDNumber(QWidget *parent = 0, const char *name = 0) :
	QLCDNumber(parent, name) {}
    PLCDNumber(uint numDigits, QWidget *parent = 0, const char *name = 0) :
	QLCDNumber(numDigits, parent, name) {}
};

class pLCDNumber : public QLCDNumber {
public:
    void virtual_drawContents(QPainter *p) { QLCDNumber::drawContents(p); }
    void virtual_resizeEvent(QResizeEvent *e) { QLCDNumber::resizeEvent(e); }
};

typedef QLCDNumber::Mode QLCDNumber__Mode;
typedef QLCDNumber::SegmentStyle QLCDNumber__SegmentStyle;

#endif  // PLCDNUM_H
