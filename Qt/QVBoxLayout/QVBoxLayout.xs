/*
 * PerlQt interface to QVBoxLayout (qlayout.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqvblayout.h>

static const char *QVBoxLayout_require[] = { "QWidget", 0 };

MODULE = Qt::QVBoxLayout	PACKAGE = QVBoxLayout
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QVBoxLayout",
	"QBoxLayout",
	QVBoxLayout_require
    );
