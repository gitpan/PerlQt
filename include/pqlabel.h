#ifndef PQLABEL_H
#define PQLABEL_H

/*
 * QLabel interface.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqframe.h>
#include <qlabel.h>

#define QLabel_functions
#define QLabel_inlines(class)
#define QLabel_virtual_functions					\
    QFrame_virtual_functions						\
    QLabel_functions
#define QLabel_virtual_inlines(class)					\
    QFrame_virtual_inlines(class)					\
    QLabel_inlines(class)

class QLabel_virtualize : public QFrame_virtualize {};

class VQLabel : public QLabel, public QLabel_virtualize {
    QLabel_virtual_functions
public:
    VQLabel(QWidget *parent = 0, const char *name = 0, WFlags f = 0) :
	QLabel(parent, name, f) {}
    VQLabel(const char *text, QWidget *parent = 0, const char *name = 0,
	    WFlags f = 0) : QLabel(text, parent, name, f) {}
    VQLabel(QWidget *buddy, const char *text, QWidget *parent = 0,
	    const char *name = 0, WFlags f = 0) :
	QLabel(buddy, text, parent, name, f) {}
};

class PQLabel : public QLabel {
    QLabel_virtual_inlines(QLabel)
};

typedef const QLabel CQLabel;

#endif  // PQLABEL_H
