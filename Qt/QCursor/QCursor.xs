/*
 * PerlQt interface to QCursor (qcursor.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqcursor.h>

static const char *qcursor_str = "QCursor";

static const char *QCursor_require[] = { "QBitmap", "QPoint", 0 };
static struct pqt_const_object pqt_const_QCursor_objects[] = {
    { "arrow",		&arrowCursor,		qcursor_str },
    { "upArrow",	&upArrowCursor,		qcursor_str },
    { "cross",		&crossCursor,		qcursor_str },
    { "wait",		&waitCursor,		qcursor_str },
    { "ibeam",		&ibeamCursor,		qcursor_str },
    { "sizeVer",	&sizeVerCursor,		qcursor_str },
    { "sizeHor",	&sizeHorCursor,		qcursor_str },
    { "sizeBDiag",	&sizeBDiagCursor,	qcursor_str },
    { "sizeFDiag",	&sizeFDiagCursor,	qcursor_str },
    { "sizeAll",	&sizeAllCursor,		qcursor_str },
    { "blank",		&blankCursor,		qcursor_str },
    { 0,		0,			0	    }
};
static struct pqt_const_hash pqt_const_hash_Shape[] = {
    { "Arrow",		ArrowCursor	},
    { "UpArrow",	UpArrowCursor	},
    { "Cross",		CrossCursor	},
    { "Wait",		WaitCursor	},
    { "Ibeam",		IbeamCursor	},
    { "SizeVer",	SizeVerCursor	},
    { "SizeHor",	SizeHorCursor	},
    { "SizeBDiag",	SizeBDiagCursor	},
    { "SizeFDiag",	SizeFDiagCursor	},
    { "SizeAll",	SizeAllCursor	},
    { "Blank",		BlankCursor	},
    { 0,		0		}
};
static struct pqt_export QCursor_export[] = {
    { "%Cursor", pqt_const_QCursor_objects },
    { "%Shape",  pqt_const_hash_Shape	   },
    { 0, 0 }
};
static const char *QCursor_overload[] = { "<<", ">>", 0 };

MODULE = Qt::QCursor	PACKAGE = QCursor
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QCursor",
	NULL,
	QCursor_require,
	QCursor_export,
	QCursor_overload
    );
