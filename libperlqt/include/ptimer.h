#ifndef PTIMER_H
#define PTIMER_H

/*
 * Declaration of the PTimer class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qtimer.h"
#include "pobject.h"

#define QTimer_virtual_functions QObject_virtual_functions

class PTimer_virtualize : public PObject_virtualize {};

class PTimer : public QTimer, public PTimer_virtualize {
    QTimer_virtual_functions
public:
    PTimer(QObject *parent = 0, const char *name = 0) : QTimer(parent, name) {}
};

class pTimer : public QTimer {
public:
    bool virtual_event(QEvent *e) { return QTimer::event(e); }
};

#endif  // PTIMER_H
