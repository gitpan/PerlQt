/*
 * PerlQt interface to QGroupBox (qgrpbox.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqgrpbox.h>

static struct pqt_export QGroupBox_export[] = {
    { "%Align", 0 },
    { 0, 0 }
};

MODULE = Qt::QGroupBox	     PACKAGE = QGroupBox	PREFIX = v_
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QGroupBox",
	"QFrame",
	0,
	QGroupBox_export
    );
