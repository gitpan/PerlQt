#ifndef PQAPP_H
#define PQAPP_H

/*
 * Declaration of the VQApplication class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqobject.h>
#include <qapp.h>

#define QApplication_functions						\
public:									\
    bool notify(QObject *, QEvent *);

#define QApplication_inlines(class)					\
public:									\
    bool v_notify(QObject *a1, QEvent *a2) {				\
	return class::notify(a1, a2);					\
    }

#define QApplication_virtual_functions					\
    QObject_virtual_functions						\
    QApplication_functions

#define QApplication_virtual_inlines(class)				\
    QObject_virtual_inlines(class)					\
    QApplication_inlines(class)

class QApplication_virtualize : public QObject_virtualize {
public:
    bool QApplication_notify(QObject *, QEvent *);
};

class VQApplication : public QApplication, public QApplication_virtualize {
    QApplication_virtual_functions
public:
    VQApplication(int &a1, char **a2) : QApplication(a1, a2) {}
};

class PQApplication : public QApplication {
    QApplication_virtual_inlines(QApplication)
public:
    PQApplication(int &a1, char **a2) : QApplication(a1, a2) {}
};    

typedef const QApplication CQApplication;
typedef const PQApplication CPQApplication;

#endif  // PQAPP_H
