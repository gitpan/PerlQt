#ifndef PAPP_H
#define PAPP_H

/*
 * Declaration of the PApplication class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qapp.h"
#include "pobject.h"

#define QApplication_virtual_functions					\
    QObject_virtual_functions						\
public:									\
    bool notify(QObject *, QEvent *);

class PApplication_virtualize : public PObject_virtualize {
public:
    bool PApplication_notify(QObject *, QEvent *);
};

class PApplication : public QApplication, public PApplication_virtualize {
    QApplication_virtual_functions
public:
    PApplication(int &argc, char **argv) : QApplication(argc, argv) {}
};

#endif  // PAPP_H
