/*
 * PerlQt interface to QPushButton (qpushbt.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqpushbt.h>
#include <pqpoint.h>
#include <pqrect.h>
#include <pqsize.h>

MODULE = Qt::QPushButton	PACKAGE = QPushButton		PREFIX = v_
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QPushButton",		// QPushButton::
	"QButton"		// @ISA = ('QButton');
    );

VQPushButton *
VQPushButton::new(...)
    CASE: items == 1 || pqt_object(ST(1)) || (items == 3 && pqt_object(ST(2)))
	PREINIT:
	QWidget *parent = pzQ(1, QWidget);
	pcchar name = pczPV(2);
	CODE:
	RETVAL = new VQPushButton(parent, name);
	OUTPUT:
	RETVAL
    CASE:
	PREINIT:
	pcchar text = pcPV(1);
	QWidget *parent = pzQ(2, QWidget);
	pcchar name = pczPV(3);
	CODE:
	RETVAL = new VQPushButton(text, parent, name);
	OUTPUT:
	RETVAL

bool
CQPushButton::autoDefault()

void
PQPushButton::v_drawButton(p)
    QPainter *p

void
PQPushButton::v_drawButtonLabel(p)
    QPainter *p

void
PQPushButton::v_focusInEvent(event)
    QFocusEvent *event

bool
CQPushButton::isDefault()

void
PQPushButton::v_move(...)
    CASE: items == 1
	PREINIT:
	CQPoint point = pQ(1, const QPoint);
	CODE:
	THIS->move(point);
    CASE:
	PREINIT:
	int x = pIV(1);
	int y = pIV(2);
	CODE:
	THIS->v_move(x, y);

void
PQPushButton::v_resize(...)
    CASE: items == 1
	PREINIT:
	CQSize size = pQ(1, const QSize);
	CODE:
	THIS->resize(size);
    CASE:
	PREINIT:
	int w = pIV(1);
	int h = pIV(2);
	CODE:
	THIS->v_resize(w, h);

void
QPushButton::setAutoDefault(autoDef)
    bool autoDef

void
QPushButton::setDefault(def)
    bool def

void
PQPushButton::v_setGeometry(...)
    CASE: items == 1
	PREINIT:
	CQRect rect = pQ(1, const QRect);
	CODE:
	THIS->setGeometry(rect);
    CASE:
	PREINIT:
	int x = pIV(1);
	int y = pIV(2);
	int w = pIV(3);
	int h = pIV(4);
	CODE:
	THIS->v_setGeometry(x, y, w, h);

void
QPushButton::setOn(enable)
    bool enable

void
QPushButton::setToggleButton(enable)
    bool enable

MQSize
CPQPushButton::v_sizeHint()

void
QPushButton::toggle()