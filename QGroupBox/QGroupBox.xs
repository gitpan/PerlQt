/*
 * PerlQt interface to qgrpbox.h
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pgrpbox.h"
#include "pwidget.h"
#include "pqt.h"

MODULE = QGroupBox		PACKAGE = QGroupBox

PROTOTYPES: ENABLE

PGroupBox *
PGroupBox::new(...)
    CASE: items == 1
	CODE:
	RETVAL = new PGroupBox();
	OUTPUT:
	RETVAL
    CASE: sv_isobject(ST(1))
	PREINIT:
	pWidget *parent = pextract(pWidget, 1);
	pChar *name = (items > 2 && SvOK(ST(2))) ? SvPV(ST(2), na) : 0;
	CODE:
	RETVAL = new PGroupBox(parent, name);
	OUTPUT:
	RETVAL
    CASE:
	PREINIT:
	char *title = SvPV(ST(1), na);
	pWidget *parent = (items > 2) ? pextract(pWidget, 2) : 0;
	pChar *name = (items > 3 && SvOK(ST(3))) ? SvPV(ST(3), na) : 0;
	CODE:
	RETVAL = new PGroupBox(title, parent, name);
	OUTPUT:
	RETVAL

int
QGroupBox::alignment()

void
QGroupBox::setAlignment(alignment)
    int alignment

void
QGroupBox::setTitle(title)
    char *title

const char *
QGroupBox::title()


MODULE = QGroupBox	PACKAGE = QGroupBox	PREFIX = virtual_

void
pGroupBox::virtual_paintEvent(event)
    QPaintEvent *event
