/*
 * PerlQt interface to QBoxLayout (qlayout.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqblayout.h>

static struct pqt_const_hash pqt_const_hash_Direction[] = {
    { "LeftToRight", QBoxLayout::LeftToRight },
    { "RightToLeft", QBoxLayout::RightToLeft },
    { "TopToBottom", QBoxLayout::TopToBottom },
    { "BottomToTop", QBoxLayout::BottomToTop },
    { "Down",	     QBoxLayout::Down	     },
    { "Up",	     QBoxLayout::Up	     },
    { 0,	     0			     }
};

static const char *QBoxLayout_require[] = { "QWidget", 0 };

static struct pqt_export QBoxLayout_export[] = {
    { "%Direction", pqt_const_hash_Direction },
    { 0, 0 }
};

MODULE = Qt::QBoxLayout	     PACKAGE = QBoxLayout
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QBoxLayout",
	"QLayout",
	QBoxLayout_require,
	QBoxLayout_export
    );
