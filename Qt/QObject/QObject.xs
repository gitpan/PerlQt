/*
 * PerlQt interface to QObject (qobject.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqobject.h>

static const char *QObject_require[] = { "QEvent", 0 };

MODULE = Qt::QObject	 PACKAGE = QObject	PREFIX = v_
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QObject",		// QObject::
	NULL,			// @ISA = ();
	QObject_require		// require QEvent;
    );

VQObject *
VQObject::new(parent = 0, name = 0)
    QObject *parent
    pcchar name

void
QObject::DESTROY()
    CODE:
    if(want_destroy(ST(0)))
	delete THIS;

void
QObject::blockSignals(block)
    bool block

const QObjectList *
CQObject::children()

bool
CQObject::connect(sender, signal, member)
    CASE: pqt_object(ST(2))
	const QObject DEF *sender
	pcchar DEF signal
	pcchar DEF member
	INIT:
	sigslot(sender, &signal, &THIS, &member, "QObject::connect");
    CASE:
	PREINIT:
	pcchar DEF signal = pcdPV(1);
	const QObject DEF *receiver = pdQ(2, const QObject);
	pcchar DEF member = pcdPV(3);
	INIT:
	sigslot(THIS, &signal, &receiver, &member, "QObject::connect");
	CODE:
	RETVAL = QObject::connect(THIS, signal, receiver, member);
	OUTPUT:
	RETVAL

void
PQObject::v_connectNotify(signal)
    pcchar DEF signal

bool
CQObject::disconnect(signal = 0, receiver = 0, member = 0)
    CASE: items == 1 || !sv_isobject(ST(1))
	pcchar signal
	const QObject *receiver
	pcchar member
	INIT:
	sigslot(THIS, &signal, receiver, &member, "QObject::disconnect");
	CODE:
	RETVAL = ((QObject *)THIS)->disconnect(signal, receiver, member);
	OUTPUT:
	RETVAL
    CASE:
	PREINIT:
	const QObject DEF *receiver = pdQ(1, const QObject);
	pcchar member = pcPV(2);
	INIT:
	member = sigslot(receiver, member, "QObject::disconnect");
	CODE:
	RETVAL = ((QObject *)THIS)->disconnect(receiver, member);
	OUTPUT:
	RETVAL

void
PQObject::v_disconnectNotify(signal)
    pcchar DEF signal

void
QObject::dumpObjectInfo()

void
QObject::dumpObjectTree()

bool
PQObject::v_event(event)
    QEvent DEF *event

bool
PQObject::v_eventFilter(obj, event)
    QObject *obj
    QEvent *event

bool
CQObject::highPriority()

void
QObject::insertChild(obj)
    QObject DEF *obj

void
QObject::installEventFilter(obj)
    const QObject DEF *obj

bool
CQObject::isWidgetType()

void
QObject::killTimer(id)
    int id

void
QObject::killTimers()

pcchar
CQObject::name()

QObject *
CQObject::parent()

QConnectionList *
PQObject::receivers(signal)
    pcchar signal

void
QObject::removeChild(obj)
    QObject *obj

void
QObject::removeEventFilter(obj)
    const QObject *obj

const QObject *
PQObject::sender()

void
QObject::setName(name)
    pcchar name

bool
CQObject::signalsBlocked()

int
QObject::startTimer(interval)
    int interval

void
PQObject::v_timerEvent(event)
    QTimerEvent *event
