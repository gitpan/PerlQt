/*
 * PerlQt interface to QMenuBar (qmenubar.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqmenubar.h>

static struct pqt_const_hash pqt_const_hash_SeparateMenu[] = {
    { "Never",		QMenuBar::Never		 },
    { "InWindowsStyle", QMenuBar::InWindowsStyle },
    { 0,		0			 }
};

static struct pqt_export QMenuBar_export[] = {
    { "%SeparateMenu", pqt_const_hash_SeparateMenu }, { 0, 0 }
};

static const char *QMenuBar_isa[] = { "QFrame", "QMenuData", 0 };

MODULE = Qt::QMenuBar	PACKAGE = QMenuBar	PREFIX = v_
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QMenuBar",
	QMenuBar_isa,
	0,
	QMenuBar_export
    );
