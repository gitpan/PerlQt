/*
 * PerlQt interface to qevent.h
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pevent.h"
#include "ppoint.h"
#include "prect.h"
#include "psize.h"
#include "penum.h"

#define STORE_key(key) enumIV(hv, MSTR(key), key ## Button)

inline void init_enum() {
    HV *hv = perl_get_hv("QEvent::Button", TRUE | GV_ADDMULTI);

    STORE_key(No);
    STORE_key(Left);
    STORE_key(Right);
    STORE_key(Mid);
    STORE_key(Shift);
    STORE_key(Control);
    STORE_key(Alt);
    enumIV(hv, "MouseMask", MouseButtonMask);
    enumIV(hv, "KeyMask", KeyButtonMask);
}

#define STORE_Event(name) enumIV(hv, MSTR(name), Event_ ## name)

inline void init_Event() {
    HV *hv = perl_get_hv("QEvent::Event", TRUE | GV_ADDMULTI);

    STORE_Event(None);
    STORE_Event(Timer);
    STORE_Event(MouseButtonPress);
    STORE_Event(MouseButtonRelease);
    STORE_Event(MouseButtonDblClick);
    STORE_Event(MouseMove);
    STORE_Event(KeyPress);
    STORE_Event(KeyRelease);
    STORE_Event(FocusIn);
    STORE_Event(FocusOut);
    STORE_Event(Enter);
    STORE_Event(Leave);
    STORE_Event(Paint);
    STORE_Event(Move);
    STORE_Event(Resize);
    STORE_Event(Create);
    STORE_Event(Destroy);
    STORE_Event(Show);
    STORE_Event(Hide);
    STORE_Event(Close);
    STORE_Event(Quit);
    STORE_Event(Accel);
    STORE_Event(Clipboard);
    STORE_Event(SockAct);
    STORE_Event(User);
}

MODULE = QEvent		PACKAGE = QEvent

PROTOTYPES: DISABLE

BOOT:
    init_enum();
    init_Event();

PEvent *
PEvent::new(type)
    int type

void
QEvent::DESTROY()
    CODE:
    if(want_destroy(ST(0)))
	delete THIS;

int
QEvent::type()

MODULE = QEvent		PACKAGE = QCloseEvent

PCloseEvent *
PCloseEvent::new()

void
QCloseEvent::DESTROY()
    CODE:
    if(want_destroy(ST(0)))
	delete THIS;

void
QCloseEvent::accept()

void
QCloseEvent::ignore()

bool
QCloseEvent::isAccepted()

MODULE = QEvent		PACKAGE = QFocusEvent

PFocusEvent *
PFocusEvent::new(type)
    int type

void
QFocusEvent::DESTROY()
    CODE:
    if(want_destroy(ST(0)))
	delete THIS;

bool
QFocusEvent::gotFocus()

bool
QFocusEvent::lostFocus()

MODULE = QEvent		PACKAGE = QKeyEvent

PKeyEvent *
PKeyEvent::new(type, key, ascii, state)
    int type
    int key
    int ascii
    int state

void
QKeyEvent::DESTROY()
    CODE:
    if(want_destroy(ST(0)))
	delete THIS;

void
QKeyEvent::accept()

int
QKeyEvent::ascii()

void
QKeyEvent::ignore()

bool
QKeyEvent::isAccepted()

int
QKeyEvent::key()

int
QKeyEvent::state()

MODULE = QEvent		PACKAGE = QMouseEvent

PMouseEvent *
PMouseEvent::new(type, pos, button, state)
    int type
    QPoint *pos
    int button
    int state
    CODE:
    RETVAL = new PMouseEvent(type, *pos, button, state);
    OUTPUT:
    RETVAL

void
QMouseEvent::DESTROY()
    CODE:
    if(want_destroy(ST(0)))
	delete THIS;

int
QMouseEvent::button()

PPoint *
QMouseEvent::pos()
    CODE:
    RETVAL = new PPoint(THIS->pos());
    OUTPUT:
    RETVAL

int
QMouseEvent::state()

int
QMouseEvent::x()

int
QMouseEvent::y()

MODULE = QEvent		PACKAGE = QMoveEvent

PMoveEvent *
PMoveEvent::new(pos, oldPos)
    QPoint *pos
    QPoint *oldPos
    CODE:
    RETVAL = new PMoveEvent(*pos, *oldPos);
    OUTPUT:
    RETVAL

void
QMoveEvent::DESTROY()
    CODE:
    if(want_destroy(ST(0)))
	delete THIS;

PPoint *
QMoveEvent::oldPos()
    CODE:
    RETVAL = new PPoint(THIS->oldPos());
    OUTPUT:
    RETVAL

PPoint *
QMoveEvent::pos()
    CODE:
    RETVAL = new PPoint(THIS->pos());
    OUTPUT:
    RETVAL

MODULE = QEvent		PACKAGE = QPaintEvent

PPaintEvent *
PPaintEvent::new(paintRect)
    QRect *paintRect
    CODE:
    RETVAL = new PPaintEvent(*paintRect);
    OUTPUT:
    RETVAL

void
QPaintEvent::DESTROY()
    CODE:
    if(want_destroy(ST(0)))
	delete THIS;

PRect *
QPaintEvent::rect()
    CODE:
    RETVAL = new PRect(THIS->rect());
    OUTPUT:
    RETVAL

MODULE = QEvent		PACKAGE = QResizeEvent

PResizeEvent *
PResizeEvent::new(size, oldSize)
    QSize *size
    QSize *oldSize
    CODE:
    RETVAL = new PResizeEvent(*size, *oldSize);
    OUTPUT:
    RETVAL

void
QResizeEvent::DESTROY()
    CODE:
    if(want_destroy(ST(0)))
	delete THIS;

PSize *
QResizeEvent::oldSize()
    CODE:
    RETVAL = new PSize(THIS->oldSize());
    OUTPUT:
    RETVAL

PSize *
QResizeEvent::size()
    CODE:
    RETVAL = new PSize(THIS->size());
    OUTPUT:
    RETVAL

MODULE = QEvent		PACKAGE = QTimerEvent

PTimerEvent *
PTimerEvent::new(timerId)
    int timerId

void
QTimerEvent::DESTROY()
    CODE:
    if(want_destroy(ST(0)))
	delete THIS;

int
QTimerEvent::timerId()