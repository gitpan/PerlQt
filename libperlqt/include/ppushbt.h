#ifndef PPUSHBT_H
#define PPUSHBT_H

/*
 * Declaration of the PPushButton class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qpushbt.h"
#include "pbutton.h"

#define QPushButton_virtual_functions QButton_virtual_functions

class PPushButton_virtualize : public PButton_virtualize {};

class PPushButton : public QPushButton, public PPushButton_virtualize {
    QPushButton_virtual_functions
public:
    PPushButton(QWidget *parent = 0, const char *name = 0) :
	QPushButton(parent, name) {}
    PPushButton(const char *text, QWidget *parent = 0, const char *name = 0) :
	QPushButton(text, parent, name) {}
};

class pPushButton : public QPushButton {
public:
    void virtual_drawButton(QPainter *p) { QPushButton::drawButton(p); }
    void virtual_drawButtonLabel(QPainter *p) {
	QPushButton::drawButtonLabel(p);
    }
    void virtual_focusInEvent(QFocusEvent *e) { QPushButton::focusInEvent(e); }
    void virtual_move(int x, int y) { QPushButton::move(x, y); }
    void virtual_resize(int w, int h) { QPushButton::resize(w, h); }
    void virtual_setGeometry(int x, int y, int w, int h) {
	QPushButton::setGeometry(x, y, w, h);
    }
    QSize virtual_sizeHint() const { return QPushButton::sizeHint(); }
};

#endif  // PPUSHBT_H
