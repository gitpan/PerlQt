#ifndef PACCEL_H
#define PACCEL_H

/*
 * Declaration of the PAccel class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qaccel.h"
#include "virtual.h"

class PAccel : public QAccel, public PAccel_virtualize {
    QAccel_virtual_functions
public:
    PAccel(QWidget *parent, const char *name = 0) : QAccel(parent, name) {}
};

class pAccel : public QAccel {
public:
    pAccel(QWidget *parent, const char *name = 0) : QAccel(parent, name) {}
    bool virtual_eventFilter(QObject *o, QEvent *e) {
	return QAccel::eventFilter(o, e);
    }
};

#endif  // PACCEL_H
