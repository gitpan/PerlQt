/*
 * PerlQt interface to QToolTipGroup (qtooltip.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqtooltipgrp.h>

MODULE = Qt::QToolTipGroup	PACKAGE = QToolTipGroup
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QToolTipGroup",
	"QObject"
    );
