/*
 * PerlQt interface to QDialog (qdialog.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqdialog.h>

static struct pqt_const_hash pqt_const_hash_Dialog[] = {
    { "Accepted", QDialog::Accepted },
    { "Rejected", QDialog::Rejected },
    { 0,	  0		    }
};
static struct pqt_export QDialog_export[] = {
    { "%Dialog", pqt_const_hash_Dialog }, { 0, 0 }
};

MODULE = Qt::QDialog	PACKAGE = QDialog	PREFIX = v_
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QDialog",
	"QWidget",
	0,
	QDialog_export
    );
