/*
 * PerlQt interface to QWindow (qwindow.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqwindow.h>

MODULE = Qt::QWindow	PACKAGE = QWindow	PREFIX = v_
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QWindow",
	"QWidget"
    );
