#ifndef PQPROGBAR_H
#define PQPROGBAR_H

/*
 * QProgressBar interface.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqframe.h>
#include <qprogbar.h>

#define QProgressBar_functions
#define QProgressBar_inlines(class)
#define QProgressBar_virtual_functions					\
    QFrame_virtual_functions						\
    QProgressBar_functions
#define QProgressBar_virtual_inlines(class)				\
    QFrame_virtual_inlines(class)					\
    QProgressBar_inlines(class)

class QProgressBar_virtualize : public QFrame_virtualize {};

class VQProgressBar : public QProgressBar, public QProgressBar_virtualize {
    QProgressBar_virtual_functions
public:
    VQProgressBar(QWidget *parent = 0, const char *name = 0, WFlags f) :
	QProgressBar(parent, name, f) {}
    VQProgressBar(int totalSteps, QWidget *parent = 0, const char *name = 0,
		  WFlags f = 0) : QProgressBar(totalSteps, parent, name, f) {}
};

class PQProgressBar : public QProgressBar {
    QProgressBar_virtual_inlines(QProgressBar)
};

typedef const QProgressBar CQProgressBar;

#endif  // PQPROGBAR_H
