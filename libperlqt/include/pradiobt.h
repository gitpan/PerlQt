#ifndef PRADIOBT_H
#define PRADIOBT_H

/*
 * Declaration of the PRadioButton class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qradiobt.h"
#include "psize.h"
#include "virtual.h"

class PRadioButton : public QRadioButton, public PRadioButton_virtualize {
    QRadioButton_virtual_functions
public:
    PRadioButton(QWidget *parent = 0, const char *name = 0) :
	QRadioButton(parent, name) {}
    PRadioButton(const char *text, QWidget *parent = 0, const char *name = 0) :
	QRadioButton(text, parent, name) {}
};

class pRadioButton : public QRadioButton {
public:
    bool virtual_hitButton(const QPoint &p) const {
	QRadioButton::hitButton(p);
    }
    void virtual_drawButton(QPainter *p) { QRadioButton::drawButton(p); }
    void virtual_drawButtonLabel(QPainter *p) {
	QRadioButton::drawButtonLabel(p);
    }
    void virtual_mouseReleaseEvent(QMouseEvent *e) {
	QRadioButton::mouseReleaseEvent(e);
    }
    QSize virtual_sizeHint() const { return QRadioButton::sizeHint(); }
};

#endif  // PRADIOBT_H
