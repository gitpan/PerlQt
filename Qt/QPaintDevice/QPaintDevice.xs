/*
 * PerlQt interface to QPaintDevice (qpaintd.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqpaintd.h>
#include <pqpoint.h>
#include <pqrect.h>

static struct pqt_const_hash pqt_const_hash_PaintDevice[] = {
    { "None",		PDT_UNDEF	},
    { "Widget",		PDT_WIDGET	},
    { "Pixmap",		PDT_PIXMAP	},
    { "Printer",	PDT_PRINTER	},
    { "Picture",	PDT_PICTURE	},
    { "TypeMask",	PDT_MASK	},
    { "ExtDev",		PDF_EXTDEV	},
    { "PaintActive",	PDF_PAINTACTIVE	},
    { 0,		0		}
};

static struct pqt_export QPaintDevice_export[] = {
    { "%PaintDevice", pqt_const_hash_PaintDevice }, { 0, 0 }
};

MODULE = Qt::QPaintDevice	PACKAGE = QPaintDevice
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QPaintDevice",
	NULL,
	0,
	QPaintDevice_export
    );

int
CQPaintDevice::devType()

HANDLE
CQPaintDevice::handle()

bool
CQPaintDevice::isExtDev()

bool
CQPaintDevice::paintingActive()

Display *
CQPaintDevice::x11Display()


void
bitBlt(THIS, a1, a2, a3 = 0, ...)
    CASE: items > 2 && pqt_object(ST(1))
	QPaintDevice DEF *THIS
	CQPoint a1
	const QPaintDevice DEF *a2
	CODE:
	bitBlt(THIS, a1, a2, ((items > 3) ?
	       (QRect)CQRect(pQ(3, const QRect)) : QRect(0, 0, -1, -1)),
	       (RasterOp)pDefIV(4, CopyROP), pfBOOL(5));
    CASE: items > 3
	QPaintDevice DEF *THIS
	int a1
	int a2
	const QPaintDevice DEF *a3
	CODE:
	bitBlt(THIS, a1, a2, a3, pzIV(4), pzIV(5), pnIV(6), pnIV(7),
	       (RasterOp)pDefIV(8, CopyROP), pfBOOL(9));
