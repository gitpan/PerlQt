/*
 * PerlQt interface to QPrinter (qprinter.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqprinter.h>

static struct pqt_const_hash pqt_const_hash_Orientation[] = {
    { "Portrait",  QPrinter::Portrait  },
    { "Landscape", QPrinter::Landscape },
    { 0,	  0		       }
};

static struct pqt_const_hash pqt_const_hash_Page[] = {
    { "A4",	   QPainter::A4		},
    { "B5",	   QPainter::B5		},
    { "Letter",    QPainter::Letter	},
    { "Legal",     QPainter::Legal	},
    { "Executive", QPainter::Executive	},
    { 0,	   0			}
};

static struct pqt_export QPrinter_export[] = {
    { "%Orientation", pqt_const_hash_Orientation },
    { "%Page",	      pqt_const_hash_Page	 },
    { 0, 0 }
};

static const char *QPrinter_require[] = { "QWidget", 0 };

MODULE = Qt::QPrinter		PACKAGE = QPrinter
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QPrinter",
	"QPaintDevice",
	QPrinter_require,
	QPrinter_export
    );
