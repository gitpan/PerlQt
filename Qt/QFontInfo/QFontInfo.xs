/*
 * PerlQt interface to QFontInfo (qfontinf.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqfontinf.h>

static const char *QFontInfo_require[] = { "QFont", 0 };

MODULE = Qt::QFontInfo	PACKAGE = QFontInfo
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QFontInfo",
	NULL,
	QFontInfo_require
    );
