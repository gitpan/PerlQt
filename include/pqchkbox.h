#ifndef PQCHKBOX_H
#define PQCHKBOX_H

/*
 * Declaration of the VQCheckBox class.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqbutton.h>
#include <qchkbox.h>

#define QCheckBox_functions
#define QCheckBox_inlines(class)
#define QCheckBox_virtual_functions					\
    QButton_virtual_functions						\
    QCheckBox_functions
#define QCheckBox_virtual_inlines(class)				\
    QButton_virtual_inlines(class)					\
    QCheckBox_inlines(class)

class QCheckBox_virtualize : public QButton_virtualize {};

class VQCheckBox : public QCheckBox, public QCheckBox_virtualize {
    QCheckBox_virtual_functions
public:
    VQCheckBox(QWidget *parent = 0, const char *name = 0) :
	QCheckBox(parent, name) {}
    VQCheckBox(const char *text, QWidget *parent, const char *name = 0) :
	QCheckBox(text, parent, name) {}
};

class PQCheckBox : public QCheckBox { QCheckBox_virtual_inlines(QCheckBox) };

typedef const QCheckBox CQCheckBox;

#endif  // PQCHKBOX_H
