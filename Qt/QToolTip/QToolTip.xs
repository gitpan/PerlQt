/*
 * PerlQt interface to QToolTip (qtooltip.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqtooltip.h>

static const char *QToolTip_require[] = {
    "QFont",
    "QPalette",
    "QRect",
    "QToolTipGroup",
    "QWidget",
    0
};

MODULE = Qt::QToolTip		PACKAGE = QToolTip
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QToolTip",
	NULL,
	QToolTip_require
    );
