/*
 * PerlQt interface to qscrbar.h
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pscrbar.h"
#include "prect.h"
#include "psize.h"
#include "penum.h"

#define STORE_key(key) enumIV(hv, MSTR(key), QScrollBar::key)

inline HV *init_Orientation(HV *hv) {
    register SV **svp = NULL;

    STORE_key(Horizontal);
    STORE_key(Vertical);

    return hv;
}

inline void load_enum() {
    SvREADONLY_on(init_Orientation(perl_get_hv("QScrollBar::Orientation",
					       TRUE | GV_ADDMULTI)));
}

MODULE = QScrollBar		PACKAGE = QScrollBar

PROTOTYPES: DISABLE

BOOT:
    load_enum();

PScrollBar *
PScrollBar::new(...)
    CASE: items == 1
	CODE:
	RETVAL = new PScrollBar();
	OUTPUT:
	RETVAL
    CASE: items < 4 && sv_isobject(ST(1))
	PREINIT:
	pWidget *parent = pextract(pWidget, 1);
	pChar *name = (items > 2 && SvOK(ST(2))) ? SvPV(ST(2), na) : 0;
	CODE:
	RETVAL = new PScrollBar(parent, name);
	OUTPUT:
	RETVAL
    CASE: items < 5 && sv_isobject(ST(2))
	PREINIT:
	QScrollBar::Orientation orientation =
	    (QScrollBar::Orientation) SvIV(ST(1));
	pWidget *parent = (items > 2) ? pextract(pWidget, 2) : 0;
	pChar *name = (items > 3 && SvOK(ST(3))) ? SvPV(ST(3), na) : 0;
	CODE:
	RETVAL = new PScrollBar(orientation, parent, name);
	OUTPUT:
	RETVAL
    CASE: items > 6
	PREINIT:
	int minValue = SvIV(ST(1));
	int maxValue = SvIV(ST(2));
	int lineStep = SvIV(ST(3));
	int pageStep = SvIV(ST(4));
	int value = SvIV(ST(5));
	QScrollBar::Orientation orientation =
	    (QScrollBar::Orientation) SvIV(ST(6));
	pWidget *parent = (items > 7) ? pextract(pWidget, 7) : 0;
	pChar *name = (items > 8 && SvOK(ST(8))) ? SvPV(ST(8), na) : 0;
	CODE:
	RETVAL = new PScrollBar(minValue, maxValue, lineStep, pageStep, value,
				orientation, parent, name);
	OUTPUT:
	RETVAL
    CASE:
	CODE:
	croak("Usage: new %s(QWidget = undef, name = undef);\nUsage: new %s(orientation, QWidget = undef, name = undef);\nUsage: new %s(minValue, maxValue, LineStep, PageStep, value, orientation, QWidget = undef, name = undef);", CLASS, CLASS, CLASS);

void
QScrollBar::DESTROY()
    CODE:
    if(want_destroy(ST(0)))
	delete THIS;

bool
QScrollBar::draggingSlider()

QScrollBar::Orientation
QScrollBar::orientation()

void
QScrollBar::setOrientation(orientation)
    QScrollBar::Orientation orientation

void
QScrollBar::setRange(minValue, maxValue)
    int minValue
    int maxValue

void
QScrollBar::setTracking(enable)
    bool enable

void
QScrollBar::setValue(value)
    int value

bool
QScrollBar::tracking()


MODULE = QScrollBar	PACKAGE = QScrollBar	PREFIX = virtual_

void
pScrollBar::virtual_keyPressEvent(event)
    QKeyEvent *event

void
pScrollBar::virtual_mouseMoveEvent(event)
    QMouseEvent *event

void
pScrollBar::virtual_mousePressEvent(event)
    QMouseEvent *event

void
pScrollBar::virtual_mouseReleaseEvent(event)
    QMouseEvent *event

void
pScrollBar::virtual_paintEvent(event)
    QPaintEvent *event

void
pScrollBar::virtual_rangeChange()

void
pScrollBar::virtual_resizeEvent(event)
    QResizeEvent *event

void
pScrollBar::virtual_setPalette(palette)
    QPalette *palette
    CODE:
    THIS->virtual_setPalette(*palette);

PSize *
pScrollBar::virtual_sizeHint()
    CODE:
    RETVAL = new PSize(THIS->virtual_sizeHint());
    OUTPUT:
    RETVAL

void
pScrollBar::virtual_stepChange()

void
pScrollBar::virtual_timerEvent(event)
    QTimerEvent *event

void
pScrollBar::virtual_valueChange()


MODULE = QScrollBar	PACKAGE = QScrollBar	PREFIX = protected_

PRect *
pScrollBar::protected_sliderRect()
    CODE:
    RETVAL = new PRect(THIS->protected_sliderRect());
    OUTPUT:
    RETVAL

int
pScrollBar::protected_sliderStart()
