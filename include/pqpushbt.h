#ifndef PQPUSHBT_H
#define PQPUSHBT_H

/*
 * Declaration of the VQPushButton class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqbutton.h>
#include <qpushbt.h>

#define QPushButton_functions
#define QPushButton_inlines(class)

#define QPushButton_virtual_functions					\
    QButton_virtual_functions						\
    QPushButton_functions

#define QPushButton_virtual_inlines(class)				\
    QButton_virtual_inlines(class)					\
    QPushButton_inlines(class)

class QPushButton_virtualize : public QButton_virtualize {};

class VQPushButton : public QPushButton, public QPushButton_virtualize {
    QPushButton_virtual_functions
public:
    VQPushButton(QWidget *parent = 0, const char *name = 0) :
	QPushButton(parent, name) {}
    VQPushButton(const char *text, QWidget *parent = 0, const char *name = 0) :
	QPushButton(text, parent, name) {}
};

class PQPushButton : public QPushButton {
    QPushButton_virtual_inlines(QPushButton)
};

typedef const QPushButton CQPushButton;
typedef const PQPushButton CPQPushButton;

#endif  // PQPUSHBT_H
