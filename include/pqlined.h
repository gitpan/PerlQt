#ifndef PQLINED_H
#define PQLINED_H

/*
 * QLineEdit interface.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqwidget.h>
#include <qlined.h>

#define QLineEdit_functions
#define QLineEdit_inlines(class)
#define QLineEdit_virtual_functions					\
    QWidget_virtual_functions						\
    QLineEdit_functions
#define QLineEdit_virtual_inlines(class)				\
    QWidget_virtual_inlines(class)					\
    QLineEdit_inlines(class)

class QLineEdit_virtualize : public QWidget_virtualize {};

class VQLineEdit : public QLineEdit, public QLineEdit_virtualize {
    QLineEdit_virtual_functions
public:
    VQLineEdit(QWidget *parent = 0, const char *name = 0) :
	QLineEdit(parent, name) {}
};

class PQLineEdit : public QLineEdit { QLineEdit_virtual_inlines(QLineEdit) };

typedef const QLineEdit CQLineEdit;

#endif  // PQLINED_H
