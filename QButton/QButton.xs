/*
 * PerlQt interface to qbutton.h
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pbutton.h"
#include "ppixmap.h"

MODULE = QButton		PACKAGE = QButton

PROTOTYPES: DISABLE

PButton *
PButton::new(parent = 0, name = 0)
    pWidget *parent
    pChar *name

void
QButton::DESTROY()
    CODE:
    if(want_destroy(ST(0)))
	delete THIS;

bool
QButton::autoRepeat()

bool
QButton::autoResize()

bool
QButton::isDown()

bool
QButton::isOn()

bool
QButton::isToggleButton()

PPixmap *
QButton::pixmap()
    CODE:
    RETVAL = new PPixmap(*(THIS->pixmap()));
    OUTPUT:
    RETVAL

void
QButton::setAutoRepeat(b)
    bool b

void
QButton::setAutoResize(b)
    bool b

void
QButton::setPixmap(pixmap)
    QPixmap *pixmap
    CODE:
    THIS->setPixmap(*pixmap);

void
QButton::setText(text)
    char *text

const char *
QButton::text()


MODULE = QButton	PACKAGE = QButton	PREFIX = virtual_

void
pButton::virtual_drawButton(p)
    QPainter *p

void
pButton::virtual_drawButtonLabel(p)
    QPainter *p

void
pButton::virtual_focusInEvent(event)
    QFocusEvent *event

void
pButton::virtual_focusOutEvent(event)
    QFocusEvent *event

bool
pButton::virtual_hitButton(p)
    QPoint *p
    CODE:
    RETVAL = THIS->virtual_hitButton(*p);
    OUTPUT:
    RETVAL

void
pButton::virtual_keyPressEvent(event)
    QKeyEvent *event

void
pButton::virtual_mouseMoveEvent(event)
    QMouseEvent *event

void
pButton::virtual_mousePressEvent(event)
    QMouseEvent *event

void
pButton::virtual_mouseReleaseEvent(event)
    QMouseEvent *event

void
pButton::virtual_paintEvent(event)
    QPaintEvent *event

void
pButton::virtual_setDown(b)
    bool b

void
pButton::virtual_setOn(b)
    bool b

void
pButton::virtual_setToggleButton(b)
    bool b
