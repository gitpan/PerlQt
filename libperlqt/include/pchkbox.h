#ifndef PCHKBOX_H
#define PCHKBOX_H

/*
 * Declaration of the PCheckBox class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qchkbox.h"
#include "pbutton.h"

#define QCheckBox_virtual_functions QButton_virtual_functions

class PCheckBox_virtualize : public PButton_virtualize {};

class PCheckBox : public QCheckBox, public PCheckBox_virtualize {
    QCheckBox_virtual_functions
public:
    PCheckBox(QWidget *parent = 0, const char *name = 0) :
	QCheckBox(parent, name) {}
    PCheckBox(const char *text, QWidget *parent, const char *name = 0) :
	QCheckBox(text, parent, name) {}
};

class pCheckBox : public QCheckBox {
public:
    void virtual_drawButton(QPainter *p) { QCheckBox::drawButton(p); }
    void virtual_drawButtonLabel(QPainter *p) {
	QCheckBox::drawButtonLabel(p);
    }
    QSize virtual_sizeHint() const { return QCheckBox::sizeHint(); }
};

#endif  // PCHKBOX_H
