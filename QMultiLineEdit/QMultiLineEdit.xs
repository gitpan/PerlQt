/*
 * PerlQt interface to qmlined.h
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pmlined.h"

MODULE = QMultiLineEdit		PACKAGE = QMultiLineEdit

PROTOTYPES: DISABLE

PMultiLineEdit *
PMultiLineEdit::new(parent = 0, name = 0)
    pWidget *parent
    pChar *name

void
QMultiLineEdit::DESTROY()
    CODE:
    if(want_destroy(ST(0)))
	delete THIS;

void
QMultiLineEdit::append(text)
    char *text

bool
QMultiLineEdit::atBeginning()

bool
QMultiLineEdit::atEnd()

bool
QMultiLineEdit::autoUpdate()

void
QMultiLineEdit::clear()

void
QMultiLineEdit::copyText()

void
QMultiLineEdit::cut()

void
QMultiLineEdit::deselect()

void
QMultiLineEdit::getCursorPosition(line, col)
    int &line
    int &col
    OUTPUT:
    line
    col

bool
QMultiLineEdit::isOverwriteMode()

bool
QMultiLineEdit::isReadOnly()

int
QMultiLineEdit::numLines()

void
QMultiLineEdit::paste()

void
QMultiLineEdit::selectAll()

void
QMultiLineEdit::setAutoUpdate(b)
    bool b

void
QMultiLineEdit::setCursorPosition(line, col, mark = FALSE)
    int line
    int col
    bool mark

void
QMultiLineEdit::setOverwriteMode(b)
    bool b

void
QMultiLineEdit::setReadOnly(b)
    bool b

void
QMultiLineEdit::setText(text)
    char *text

QString
QMultiLineEdit::text()

const char *
QMultiLineEdit::textLine(line)
    int line


MODULE = QMultiLineEdit	PACKAGE = QMultiLineEdit	PREFIX = virtual_

void
pMultiLineEdit::virtual_backspace()

void
pMultiLineEdit::virtual_cursorDown(mark = FALSE)
    bool mark

void
pMultiLineEdit::virtual_cursorLeft(mark = FALSE, wrap = TRUE)
    bool mark
    bool wrap

void
pMultiLineEdit::virtual_cursorRight(mark = FALSE, wrap = TRUE)
    bool mark
    bool wrap

void
pMultiLineEdit::virtual_cursorUp(mark = FALSE)
    bool mark

void
pMultiLineEdit::virtual_del()

void
pMultiLineEdit::virtual_end(mark = FALSE)
    bool mark

void
pMultiLineEdit::virtual_focusInEvent(event)
    QFocusEvent *event

void
pMultiLineEdit::virtual_focusOutEvent(event)
    QFocusEvent *event

void
pMultiLineEdit::virtual_home(mark)
    bool mark

void
pMultiLineEdit::virtual_insertAt(s, line, col)
    char *s
    int line
    int col

void
pMultiLineEdit::virtual_insertChar(c)
    char *c

void
pMultiLineEdit::virtual_insertLine(s, line = -1)
    char *s
    int line

void
pMultiLineEdit::virtual_keyPressEvent(event)
    QKeyEvent *event

void
pMultiLineEdit::virtual_killLine()

void
pMultiLineEdit::virtual_mouseDoubleClickEvent(event)
    QMouseEvent *event

void
pMultiLineEdit::virtual_mouseMoveEvent(event)
    QMouseEvent *event

void
pMultiLineEdit::virtual_mousePressEvent(event)
    QMouseEvent *event

void
pMultiLineEdit::virtual_mouseReleaseEvent(event)
    QMouseEvent *event

void
pMultiLineEdit::virtual_newLine()

void
pMultiLineEdit::virtual_pageUp(mark)
    bool mark

void
pMultiLineEdit::virtual_pageDown(mark)
    bool mark

void
pMultiLineEdit::virtual_paintCell(p, row, col)
    QPainter *p
    int row
    int col

void
pMultiLineEdit::virtual_removeLine(line)
    int line

void
pMultiLineEdit::virtual_timerEvent(event)
    QTimerEvent *event


MODULE = QMultiLineEdit	   PACKAGE = QMultiLineEdit	PREFIX = protected_

const char *
pMultiLineEdit::protected_getString(row)
    int row

bool
pMultiLineEdit::protected_hasMarkedText()

int
pMultiLineEdit::protected_lineLength(row)
    int row

const char *
pMultiLineEdit::protected_markedText()

int
pMultiLineEdit::protected_textWidth(line)
    CASE: SvIOK(ST(1))
	int line
    CASE:
	char *line
