/*
 * PerlQt interface to qlined.h
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "plined.h"
#include "pqt.h"

MODULE = QLineEdit		PACKAGE = QLineEdit

PROTOTYPES: ENABLE

PLineEdit *
PLineEdit::new(parent, name)
    QWidget *parent
    char *name

void
QLineEdit::deselect()

int
QLineEdit::maxLength()

void
QLineEdit::selectAll()

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
