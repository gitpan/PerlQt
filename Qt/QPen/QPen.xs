/*
 * PerlQt interface to QPen (qpen.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqpen.h>

static struct pqt_const_hash pqt_const_hash_Pen[] = {
    { "None",	    NoPen	   },
    { "Solid",	    SolidLine	   },
    { "Dash",	    DashLine	   },
    { "Dot",	    DotLine	   },
    { "DashDot",    DashDotLine    },
    { "DashDotDot", DashDotDotLine },
    { 0,	    0		   }
};

static struct pqt_export QPen_export[] = {
    { "%Pen", pqt_const_hash_Pen }, { 0, 0 }
};

static const char *QPen_require[] = { "QColor", 0 };
static const char *QPen_overload[] = { "==", "!=", "<<", ">>", 0 };

MODULE = Qt::QPen		PACKAGE = QPen
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QPen",
	NULL,
	QPen_require,
	QPen_export,
	QPen_overload
    );
