/*
 * PerlQt interface to QWMatrix (qwmatrix.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqwmatrix.h>

static const char *QWMatrix_require[] = { "QPoint", "QPointArray", "QRect", 0 };
static const char *QWMatrix_overload[] = {
    "==", "!=", "*=", "*", "<<", ">>", 0
};

MODULE = Qt::QWMatrix		PACKAGE = QWMatrix
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QWMatrix",
	NULL,
	QWMatrix_require,
	0,
	QWMatrix_overload
    );
