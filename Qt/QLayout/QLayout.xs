/*
 * PerlQt interface to QLayout (qlayout.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqlayout.h>

static const char *QLayout_require[] = { "QMenuBar", "QWidget", 0 };

MODULE = Qt::QLayout	PACKAGE = QLayout
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QLayout",
	NULL,
	QLayout_require
    );
