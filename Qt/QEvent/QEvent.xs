/*
 * PerlQt interface to QEvent (qaccel.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqaccel.h>

static const char *QEvent_require[] = { "QWidget", 0 };
static struct pqt_const_hash pqt_const_hash_Event[] = {
    { "None",		Event_None	},
    { "Timer",		Event_Timer	},
    { "MouseButtonPress",    Event_MouseButtonPress	},
    { "MouseButtonRelease",  Event_MouseButtonRelease	},
    { "MouseButtonDblClick", Event_MouseButtonDblClick	},
    { "MouseMove",	Event_MouseMove	},
    { "KeyPress",	Event_KeyPress	},
    { "KeyRelease",	Event_KeyRelease},
    { "FocusIn",	Event_FocusIn	},
    { "FocusRestore",	Event_FocusRestore },
    { "FocusOut",	Event_FocusOut	},
    { "Enter",		Event_Enter	},
    { "Leave",		Event_Leave	},
    { "Paint",		Event_Paint	},
    { "Move",		Event_Move	},
    { "Resize",		Event_Resize	},
    { "Create",		Event_Create	},
    { "Destroy",	Event_Destroy	},
    { "Show",		Event_Show	},
    { "Hide",		Event_Hide	},
    { "Close",		Event_Close	},
    { "Quit",		Event_Quit	},
    { "Accel",		Event_Accel	},
    { "Clipboard",	Event_Clipboard	},
    { "SockAct",	Event_SockAct	},
    { "DragMove",	Event_DragMove	},
    { "DragLeave",	Event_DragLeave },
    { "Drop",		Event_Drop	},
    { "User",		Event_User	},
    { 0,		0		},
};
static struct pqt_export QEvent_export[] = {
    { "%Event", pqt_const_hash_Event }, { 0, 0 }
};

MODULE = Qt::QEvent	PACKAGE = QEvent
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QEvent",
	NULL,
	QEvent_require,
	QEvent_export
    );
