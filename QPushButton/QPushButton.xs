/*
 * PerlQt interface to qpushbt.h
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "ppushbt.h"

MODULE = QPushButton		PACKAGE = QPushButton		

PROTOTYPES: ENABLE

PPushButton *
PPushButton::new(...)
    CASE: items == 1 || sv_isobject(ST(1))
	PREINIT:
	QWidget *parent = (items > 1) ?
	    (QWidget *)extract_ptr(ST(1), "QWidget") : 0;
        char *name = (items > 2) ? SvPV(ST(2), na) : 0;
	CODE:
	RETVAL = new PPushButton(parent, name);
	OUTPUT:
	RETVAL
    CASE:
	PREINIT:
	char *text = SvPV(ST(1), na);
	QWidget *parent = (items > 2) ?
	    (QWidget *)extract_ptr(ST(2), "QWidget") : 0;
	char *name = (items > 3) ? SvPV(ST(2), na) : 0;
	CODE:
	RETVAL = new PPushButton(text, parent, name);
	OUTPUT:
	RETVAL

bool
QPushButton::autoDefault()

bool
QPushButton::isDefault()

void
QPushButton::setAutoDefault(autoDef)
    bool autoDef

void
QPushButton::setDefault(def)
    bool def

void
QPushButton::setOn(b)
    bool b

void
QPushButton::setToggleButton(b)
    bool b

void
QPushButton::toggle()


MODULE = QPushButton	PACKAGE = QPushButton	PREFIX = virtual_

void
pPushButton::virtual_drawButton(p)
    QPainter *p

void
pPushButton::virtual_drawButtonLabel(p)
    QPainter *p

void
pPushButton::virtual_focusInEvent(event)
    QFocusEvent *event

void
pPushButton::virtual_move(...)
    CASE: items > 2
	PREINIT:
	int x = SvIV(ST(1));
	int y = SvIV(ST(2));
	CODE:
	THIS->virtual_move(x, y);
    CASE: items > 1
	PREINIT:
	QPoint *p = pextract(QPoint, 1);
	CODE:
	((QWidget *)THIS)->move(*p);

void
pPushButton::virtual_resize(...)
    CASE: items > 2
	PREINIT:
	int w = SvIV(ST(1));
	int h = SvIV(ST(2));
	CODE:
	THIS->virtual_resize(w, h);
    CASE: items > 1
	PREINIT:
	QSize *s = pextract(QSize, 1);
	CODE:
	((QWidget *)THIS)->resize(*s);

void
pPushButton::setGeometry(...)
    CASE: items > 4
	PREINIT:
	int x = SvIV(ST(1));
	int y = SvIV(ST(2));
	int w = SvIV(ST(3));
	int h = SvIV(ST(4));
	CODE:
	THIS->setGeometry(x, y, w, h);
    CASE: items > 1
	PREINIT:
	QRect *r = pextract(QRect, 1);
	CODE:
	((QWidget *)THIS)->setGeometry(*r);

PSize *
pPushButton::virtual_sizeHint()
    CODE:
    RETVAL = new PSize(THIS->virtual_sizeHint());
    OUTPUT:
    RETVAL
