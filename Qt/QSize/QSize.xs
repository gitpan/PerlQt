/*
 * PerlQt interface to QSize (qsize.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqsize.h>

static const char *QSize_overload[] = {
    "==", "!=", "+=", "-=", "*=", "/=", "+", "-", "*", "/", "<<", ">>", 0
};

MODULE = Qt::QSize		PACKAGE = QSize
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QSize",
	NULL,
	0,
	0,
	QSize_overload
    );
