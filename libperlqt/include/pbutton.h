#ifndef PBUTTON_H
#define PBUTTON_H

/*
 * Declaration of the PButton class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qbutton.h"
#include "ppixmap.h"
#include "pqt.h"
#include "virtual.h"

class PButton : public QButton, public PButton_virtualize {
    QButton_virtual_functions
public:
    PButton(QWidget *parent = 0, const char *name = 0) :
	QButton(parent, name) {}
};

class pButton : public QButton {
public:
    void virtual_drawButton(QPainter *p) { QButton::drawButton(p); }
    void virtual_drawButtonLabel(QPainter *p) { QButton::drawButtonLabel(p); }
    void virtual_focusInEvent(QFocusEvent *e) { QButton::focusInEvent(e); }
    void virtual_focusOutEvent(QFocusEvent *e) { QButton::focusOutEvent(e); }
    bool virtual_hitButton(const QPoint &p) const {
	return QButton::hitButton(p);
    }
    void virtual_keyPressEvent(QKeyEvent *e) { QButton::keyPressEvent(e); }
    void virtual_mouseMoveEvent(QMouseEvent *e) { QButton::mouseMoveEvent(e); }
    void virtual_mousePressEvent(QMouseEvent *e) {
	QButton::mousePressEvent(e);
    }
    void virtual_mouseReleaseEvent(QMouseEvent *e) {
	QButton::mouseReleaseEvent(e);
    }
    void virtual_paintEvent(QPaintEvent *e) { QButton::paintEvent(e); }
    void virtual_setDown(bool b) { QButton::setDown(b); }
    void virtual_setOn(bool b) { QButton::setOn(b); }
    void virtual_setToggleButton(bool b) { QButton::setToggleButton(b); }
};

#endif  // PBUTTON_H
