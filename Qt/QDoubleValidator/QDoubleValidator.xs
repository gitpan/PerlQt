/*
 * PerlQt interface to QDoubleValidator (qvalidator.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqdvalidator.h>

static const char *QDoubleValidator_require[] = { "QWidget", 0 };

MODULE = Qt::QDoubleValidator	PACKAGE = QDoubleValidator	PREFIX = v_
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QDoubleValidator",
	"QValidator",
	QDoubleValidator_require
    );
