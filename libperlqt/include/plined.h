#ifndef PLINED_H
#define PLINED_H

/*
 * Declaration of the PLineEdit class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qlined.h"
#include "virtual.h"

class PLineEdit : public QLineEdit, public PLineEdit_virtualize {
    QLineEdit_virtual_functions
public:
    PLineEdit(QWidget *parent = 0, const char *name = 0) :
	QLineEdit(parent, name) {}
};

class pLineEdit : public QLineEdit {
public:
    void virtual_focusInEvent(QFocusEvent *e) { QLineEdit::focusInEvent(e); }
    void virtual_focusOutEvent(QFocusEvent *e) { QLineEdit::focusOutEvent(e); }
    void virtual_keyPressEvent(QKeyEvent *e) { QLineEdit::keyPressEvent(e); }
    void virtual_mouseDoubleClickEvent(QMouseEvent *e) {
	QLineEdit::mouseDoubleClickEvent(e);
    }
    void virtual_mouseMoveEvent(QMouseEvent *e) {
	QLineEdit::mouseMoveEvent(e);
    }
    void virtual_mousePressEvent(QMouseEvent *e) {
	QLineEdit::mousePressEvent(e);
    }
    void virtual_mouseReleaseEvent(QMouseEvent *e) {
	QLineEdit::mouseReleaseEvent(e);
    }
    void virtual_paintEvent(QPaintEvent *e) { QLineEdit::paintEvent(e); }
    void virtual_resizeEvent(QResizeEvent *e) { QLineEdit::resizeEvent(e); }
    void virtual_timerEvent(QTimerEvent *e) { QLineEdit::timerEvent(e); }

    bool protected_hasMarkedText() { return QLineEdit::hasMarkedText(); }
    const char *protected_markedText() { return QLineEdit::markedText(); }
};

#endif  // PLINED_H
