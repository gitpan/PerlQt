/*
 * PerlQt interface to QFocusEvent (qevent.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqfocusev.h>

MODULE = Qt::QFocusEvent	PACKAGE = QFocusEvent
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QFocusEvent",
	"QEvent"
    );
