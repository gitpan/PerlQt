/*
 * PerlQt interface to QRegion (qregion.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqregion.h>

static const char *QRegion_require[] = { "QPoint", "QPointArray", "QRect", 0 };
static const char *QRegion_overload[] = { "==", "!=", "<<", ">>", 0 };

MODULE = Qt::QRegion		PACKAGE = QRegion
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QRegion",
	NULL,
	QRegion_require,
	0,
	QRegion_overload
    );
