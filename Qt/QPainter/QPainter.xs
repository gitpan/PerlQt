/*
 * PerlQt interface to QPainter (qpainter.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqpainter.h>

static struct pqt_const_hash pqt_const_hash_BGMode[] = {
    { "Transparent", TransparentMode },
    { "Opaque",      OpaqueMode      },
    { 0,	  0		     }
};

static struct pqt_const_hash pqt_const_hash_RasterOp[] = {
    { "Copy",	  CopyROP	},
    { "Or",	  OrROP		},
    { "Xor",	  XorROP	},
    { "Erase",	  EraseROP	},
    { "NotCopy",  NotCopyROP	},
    { "NotOr",	  NotOrROP	},
    { "NotXor",   NotXorROP	},
    { "NotErase", NotEraseROP	},
    { "Not",	  NotROP	},
    { 0,	  0		}
};


static struct pqt_export QPainter_export[] = {
    { "%Align",    0			   },
    { "%BGMode",   pqt_const_hash_BGMode   },
    { "%RasterOp", pqt_const_hash_RasterOp },
    { 0, 0 }
};

static const char *QPainter_require[] = {
    "QBrush",
    "QColor",
    "QColorGroup",
    "QFont",
    "QFontInfo",
    "QFontMetrics",
    "QPaintDevice",
    "QPen",
    "QPicture",
    "QPixmap",
    "QPoint",
    "QPointArray",
    "QRect",
    "QRegion",
    "QWMatrix",
    0
};

MODULE = Qt::QPainter		PACKAGE = QPainter
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QPainter",
	NULL,
	QPainter_require,
	QPainter_export
    );
