/*
 * PerlQt interface to QColorGroup (qpalette.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqcolgrp.h>

static const char *QColorGroup_require[] = { "QColor", 0 };
static const char *QColorGroup_overload[] = { "==", "!=", ">>", "<<", 0 };

MODULE = Qt::QColorGroup	PACKAGE = QColorGroup
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QColorGroup",
	NULL,
	QColorGroup_require,
	0,
	QColorGroup_overload
    );
