#ifndef PQACCEL_H
#define PQACCEL_H

/*
 * QAccel interface.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqobject.h>
#include <qaccel.h>

#define QAccel_functions
#define QAccel_inlines(class)
#define QAccel_virtual_functions QObject_virtual_functions QAccel_functions
#define QAccel_virtual_inlines(class)					\
    QObject_virtual_inlines(class)					\
    QAccel_inlines(class)

class QAccel_virtualize : public QObject_virtualize {};

class VQAccel : public QAccel, public QAccel_virtualize {
    QAccel_virtual_functions
public:
    VQAccel(QWidget *parent, const char *name = 0) : QAccel(parent, name) {}
};

class PQAccel : public QAccel {
    QAccel_virtual_inlines(QAccel)
public:
    PQAccel(QWidget *parent, const char *name = 0) : QAccel(parent, name) {}
};

typedef const QAccel CQAccel;

#endif  // PQACCEL_H
