/*
 * PerlQt interface to QCloseEvent (qevent.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqcloseev.h>

MODULE = Qt::QCloseEvent	PACKAGE = QCloseEvent
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QCloseEvent",
	"QEvent"
    );
