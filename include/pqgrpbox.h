#ifndef PQGRPBOX_H
#define PQGRPBOX_H

/*
 * QGroupBox interface.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqframe.h>
#include <qgrpbox.h>

#define QGroupBox_functions
#define QGroupBox_inlines(class)
#define QGroupBox_virtual_functions					\
    QFrame_virtual_functions						\
    QGroupBox_functions
#define QGroupBox_virtual_inlines(class)				\
    QFrame_virtual_inlines(class)					\
    QGroupBox_inlines(class)

class QGroupBox_virtualize : public QFrame_virtualize {};

class VQGroupBox : public QGroupBox, public QGroupBox_virtualize {
    QGroupBox_virtual_functions
public:
    VQGroupBox(QWidget *parent = 0, const char *name = 0) :
	QGroupBox(parent, name) {}
    VQGroupBox(const char *title, QWidget *parent = 0, const char *name = 0) :
	QGroupBox(title, parent, name) {}
};

class PQGroupBox : public QGroupBox { QGroupBox_virtual_inlines(QGroupBox) };

typedef const QGroupBox CQGroupBox;

#endif  // PQGRPBOX_H
