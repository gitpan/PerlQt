/*
 * PerlQt interface to QMouseEvent (qevent.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqmouseev.h>

static struct pqt_const_hash pqt_const_hash_Button[] = {
    { "None",      NoButton	   },
    { "Left",      LeftButton	   },
    { "Right",     RightButton	   },
    { "Mid",	   MidButton	   },
    { "MouseMask", MouseButtonMask },
    { "Shift",     ShiftButton	   },
    { "Control",   ControlButton   },
    { "Alt",	   AltButton	   },
    { "KeyMask",   KeyButtonMask   },
    { 0,	  0		   }
};

static struct pqt_export QMouseEvent_export[] = {
    { "%Button", pqt_const_hash_Button }, { 0, 0 }
};

static const char *QMouseEvent_require[] = { "QPoint", 0 };

MODULE = Qt::QMouseEvent	PACKAGE = QMouseEvent
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QMouseEvent",
	"QEvent",
	QMouseEvent_require,
	QMouseEvent_export
    );
