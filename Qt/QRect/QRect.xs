/*
 * PerlQt interface to QRect (qrect.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqrect.h>

static const char *QRect_require[] = { "QPoint", "QSize", 0 };
static const char *QRect_overload[] = { "==", "!=", "<<", ">>", 0 };

MODULE = Qt::QRect		PACKAGE = QRect
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QRect",
	NULL,
	QRect_require,
	0,
	QRect_overload
    );
