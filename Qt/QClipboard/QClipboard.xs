/*
 * PerlQt interface to QClipboard (qclipbrd.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqclipbrd.h>

static const char *QClipboard_require[] = { "QPixmap", 0 };

MODULE = Qt::QClipboard		PACKAGE = QClipboard
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QClipboard",
	"QObject",
	QClipboard_require
    );
