/*
 * PerlQt interface to QButton (qbutton.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqbutton.h>
#include <pqpixmap.h>
#include <pqpoint.h>

static const char *QButton_require[] = { "QPixmap", 0 };

MODULE = Qt::QButton	 PACKAGE = QButton	PREFIX = v_
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QButton",		// QButton::
	"QWidget",		// @ISA = ('QWidget');
	QButton_require		// require QPixmap;
    );

VQButton *
VQButton::new(parent = 0, name = 0)
    QWidget *parent
    pcchar name

void
QButton::DESTROY()
    CODE:
    if(want_destroy(ST(0)))
	delete THIS;

int
CQButton::accel()

void
QButton::animateClick()

bool
CQButton::autoRepeat()

bool
CQButton::autoResize()

void
PQButton::v_drawButton(p)
    QPainter *p

void
PQButton::v_drawButtonLabel(p)
    QPainter *p

void
PQButton::v_enabledChange(oldEnabled)
    bool oldEnabled

void
PQButton::v_focusInEvent(event)
    QFocusEvent *event

void
PQButton::v_focusOutEvent(event)
    QFocusEvent *event

bool
CPQButton::v_hitButton(pos)
    CQPoint pos

bool
CQButton::isDown()

bool
CQButton::isOn()

bool
CQButton::isToggleButton()

void
PQButton::v_keyPressEvent(event)
    QKeyEvent *event

void
PQButton::v_mouseMoveEvent(event)
    QMouseEvent *event

void
PQButton::v_mousePressEvent(event)
    QMouseEvent *event

void
PQButton::v_mouseReleaseEvent(event)
    QMouseEvent *event

void
PQButton::v_paintEvent(event)
    QPaintEvent *event

const QPixmap *
CQButton::pixmap()

void
QButton::setAccel(key)
    int key

void
QButton::setAutoRepeat(enable)
    bool enable

void
QButton::setAutoResize(enable)
    bool enable

void
PQButton::setDown(enable)
    bool enable

void
PQButton::setOn(enable)
    bool enable

void
QButton::setPixmap(pm)
    CQPixmap pm

void
QButton::setText(text)
    pcchar text

void
PQButton::setToggleButton(enable)
    bool enable

pcchar
CQButton::text()
