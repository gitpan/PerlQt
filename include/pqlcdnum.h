#ifndef PQLCDNUM_H
#define PQLCDNUM_H

/*
 * QLCDNumber interface.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqframe.h>
#undef BIN
#undef OCT
#undef DEC
#undef HEX
#include <qlcdnum.h>

#define QLCDNumber_functions
#define QLCDNumber_inlines(class)
#define QLCDNumber_virtual_functions					\
    QFrame_virtual_functions						\
    QLCDNumber_functions
#define QLCDNumber_virtual_inlines(class)				\
    QFrame_virtual_inlines(class)					\
    QLCDNumber_inlines(class)

class QLCDNumber_virtualize : public QFrame_virtualize {};

class VQLCDNumber : public QLCDNumber, public QLCDNumber_virtualize {
    QLCDNumber_virtual_functions
public:
    VQLCDNumber(QWidget *parent = 0, const char *name = 0) :
	QLCDNumber(parent, name) {}
    VQLCDNumber(uint numDigits, QWidget *parent = 0, const char *name = 0) :
	QLCDNumber(numDigits, parent, name) {}
};

class PQLCDNumber : public QLCDNumber {
    QLCDNumber_virtual_inlines(QLCDNumber)
};

typedef const QLCDNumber CQLCDNumber;

#endif  // PQLCDNUM_H
