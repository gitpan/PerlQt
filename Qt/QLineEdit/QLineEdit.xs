/*
 * PerlQt interface to QLineEdit (qlined.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqlined.h>

static struct pqt_const_hash pqt_const_hash_Echo[] = {
    { "None",	  QLineEdit::NoEcho   },
    { "Normal",   QLineEdit::Normal   },
    { "Password", QLineEdit::Password },
    { 0,	  0		      }
};

static struct pqt_export QLineEdit_export[] = {
    { "%Echo", pqt_const_hash_Echo }, { 0, 0 }
};

static const char *QLineEdit_require[] = { "QValidator", 0 };

MODULE = Qt::QLineEdit	PACKAGE = QLineEdit	PREFIX = v_
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QLineEdit",
	"QWidget",
	QLineEdit_require,
	QLineEdit_export
    );
