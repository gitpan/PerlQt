/*
 * PerlQt interface to qlined.h
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "plined.h"
#include "penum.h"

#define STORE_key(key) enumIV(hv, MSTR(key), QLineEdit::key)

inline void init_enum() {
    HV *hv = perl_get_hv("QLineEdit::Echo", TRUE | GV_ADDMULTI);

    enumIV(hv, "None", QLineEdit::NoEcho);
    STORE_key(Normal);
    STORE_key(Password);
}

MODULE = QLineEdit		PACKAGE = QLineEdit

PROTOTYPES: DISABLE

PLineEdit *
PLineEdit::new(parent, name)
    QWidget *parent
    char *name

void
QLineEdit::deselect()

QLineEdit::EchoMode
QLineEdit::echoMode()

bool
QLineEdit::frame()

int
QLineEdit::maxLength()

void
QLineEdit::selectAll()

void
QLineEdit::setEchoMode(mode)
   QLineEdit::EchoMode mode

void
QLineEdit::setFrame(b)
    bool b

void
QLineEdit::setMaxLength(length)
    int length

void
QLineEdit::setText(text)
    char *text

const char *
QLineEdit::text()


MODULE = QLineEdit	PACKAGE = QLineEdit	PREFIX = virtual_

void
pLineEdit::virtual_focusInEvent(event)
    QFocusEvent *event

void
pLineEdit::virtual_focusOutEvent(event)
    QFocusEvent *event

void
pLineEdit::virtual_keyPressEvent(event)
    QKeyEvent *event

void
pLineEdit::virtual_mouseDoubleClickEvent(event)
    QMouseEvent *event

void
pLineEdit::virtual_mouseMoveEvent(event)
    QMouseEvent *event

void
pLineEdit::virtual_mousePressEvent(event)
    QMouseEvent *event

void
pLineEdit::virtual_mouseReleaseEvent(event)
    QMouseEvent *event

void
pLineEdit::virtual_paintEvent(event)
    QPaintEvent *event

void
pLineEdit::virtual_resizeEvent(event)
    QResizeEvent *event

void
pLineEdit::virtual_timerEvent(event)
    QTimerEvent *event


MODULE = QLineEdit	PACKAGE = QLineEdit	PREFIX = protected_

bool
pLineEdit::protected_hasMarkedText()

const char *
pLineEdit::protected_markedText()
