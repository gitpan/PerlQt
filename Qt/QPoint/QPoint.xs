/*
 * PerlQt interface to QPoint (qpoint.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqpoint.h>

static const char *QPoint_overload[] = {
    "==", "!=", "+=", "-=", "*=", "/=", "+", "-", "*", "-", "/", "<<", ">>", 0
};

MODULE = Qt::QPoint		PACKAGE = QPoint
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QPoint",
	NULL,
	0,
	0,
	QPoint_overload
    );
