/*
 * PerlQt interface to QHBoxLayout (qlayout.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqhblayout.h>

static const char *QHBoxLayout_require[] = { "QWidget", 0 };

MODULE = Qt::QHBoxLayout     PACKAGE = QHBoxLayout
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QHBoxLayout",
	"QBoxLayout",
	QHBoxLayout_require
    );
