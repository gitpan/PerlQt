/*
 * PerlQt interface to QBrush (qbrush.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqbrush.h>

static const char *QBrush_require[] = { "QColor", "QPixmap", 0 };
static const char *QBrush_overload[] = { "==", "!=", "<<", ">>", 0 };
static struct pqt_export QBrush_export[] = { { "%Key", 0 }, { 0, 0 } };

MODULE = Qt::QBrush	PACKAGE = QBrush
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QBrush",
	NULL,
	QBrush_require,
	QBrush_export,
	QBrush_overload
    );
