/*
 * PerlQt interface to QScrollBar (qscrbar.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqscrbar.h>

static struct pqt_const_hash pqt_const_hash_Orientation[] = {
    { "Horizontal", QScrollBar::Horizontal },
    { "Vertical",   QScrollBar::Vertical   },
    { 0,	    0			   }
};

static struct pqt_export QScrollBar_export[] = {
    { "%Orientation", pqt_const_hash_Orientation }, { 0, 0 }
};

static const char *QScrollBar_isa[] = { "QWidget", "QRangeControl", 0 };

MODULE = Qt::QScrollBar	  	PACKAGE = QScrollBar
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QScrollBar",
	QScrollBar_isa,
	0,
	QScrollBar_export
    );
