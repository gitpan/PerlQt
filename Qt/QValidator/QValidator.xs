/*
 * PerlQt interface to QValidator (qvalidator.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqvalidator.h>

static struct pqt_const_hash pqt_const_hash_Input[] = {
    { "Invalid",    QValidator::Invalid    },
    { "Valid",      QValidator::Valid      },
    { "Acceptable", QValidator::Acceptable },
    { 0,	    0			   }
};

static struct pqt_export QValidator_export[] = {
    { "%Input", pqt_const_hash_Input }, { 0, 0 }
};

static const char *QValidator_require[] = { "QWidget", 0 };

MODULE = Qt::QValidator	PACKAGE = QValidator	PREFIX = v_
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QValidator",
	"QObject",
	QValidator_require,
	QValidator_export
    );
