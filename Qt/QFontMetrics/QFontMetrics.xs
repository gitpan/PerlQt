/*
 * PerlQt interface to QFontMetrics (qfontmet.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqfontmet.h>

static const char *QFontMetrics_require[] = { "QFont", "QRect", 0 };

MODULE = Qt::QFontMetrics	PACKAGE = QFontMetrics
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QFontMetrics",
	NULL,
	QFontMetrics_require
    );
