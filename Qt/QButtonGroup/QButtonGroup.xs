/*
 * PerlQt interface to QButtonGroup (qbttngrp.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqbttngrp.h>

static const char *QButtonGroup_require[] = { "QButton", 0 };

MODULE = Qt::QButtonGroup    PACKAGE = QButtonGroup	PREFIX = v_
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QButtonGroup",
	"QGroupBox",
	QButtonGroup_require
    );
