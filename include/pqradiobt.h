#ifndef PQRADIOBT_H
#define PQRADIOBT_H

/*
 * QRadioButton interface.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqbutton.h>
#include <qradiobt.h>

#define QRadioButton_functions
#define QRadioButton_inlines(class)
#define QRadioButton_virtual_functions					\
    QButton_virtual_functions						\
    QRadioButton_functions
#define QRadioButton_virtual_inlines(class)				\
    QButton_virtual_inlines(class)					\
    QRadioButton_inlines(class)

class QRadioButton_virtualize : public QButton_virtualize {};

class VQRadioButton : public QRadioButton, public QRadioButton_virtualize {
    QRadioButton_virtual_functions
public:
    VQRadioButton(QWidget *parent = 0, const char *name = 0) :
	QRadioButton(parent, name) {}
    VQRadioButton(const char *text, QWidget *parent = 0, const char *name = 0) :
	QRadioButton(text, parent, name) {}
};

class PQRadioButton : public QRadioButton {
    QRadioButton_virtual_inlines(QRadioButton)
};

typedef const QRadioButton CQRadioButton;

#endif  // PQRADIOBT_H
