/*
 * PerlQt interface to QPointArray (qpntarry.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqpntarry.h>

static const char *QPointArray_require[] = { "QPoint", "QRect", 0 };
static const char *QPointArray_overload[] = { "<<", ">>", 0 };

MODULE = Qt::QPointArray	PACKAGE = QPointArray
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QPointArray",
	NULL,
	QPointArray_require,
	0,
	QPointArray_overload
    );
