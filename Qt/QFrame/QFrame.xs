/*
 * PerlQt interface to QFrame (qframe.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqframe.h>

static struct pqt_const_hash pqt_const_hash_Frame[] = {
    { "None",	    QFrame::NoFrame  },
    { "Box",	    QFrame::Box      },
    { "Panel",	    QFrame::Panel    },
    { "WinPanel",   QFrame::WinPanel },
    { "HLine",	    QFrame::HLine    },
    { "VLine",	    QFrame::VLine    },
    { "ShapeMask",  QFrame::MShape   },
    { "Plain",	    QFrame::Plain    },
    { "Raised",     QFrame::Raised   },
    { "Sunken",     QFrame::Sunken   },
    { "ShadowMask", QFrame::MShadow  },
    { 0,	    0		     }
};

static const char *QFrame_require[] = { "QRect", 0 };

static struct pqt_export QFrame_export[] = {
    { "%Frame", pqt_const_hash_Frame },
    { 0, 0 }
};

MODULE = Qt::QFrame	PACKAGE = QFrame	PREFIX = v_
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QFrame",
	"QWidget",
	QFrame_require,
	QFrame_export
    );
