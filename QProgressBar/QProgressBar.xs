/*
 * PerlQt interface to qprogbar.h
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pprogbar.h"
#include "psize.h"

MODULE = QProgressBar	PACKAGE = QProgressBar

PROTOTYPES: DISABLE

PProgressBar *
PProgressBar::new(...)
    CASE: items == 1 || sv_isobject(ST(1))
	PREINIT:
	pWidget *parent = (items > 1 && SvOK(ST(1))) ? pextract(pWidget, 1) : 0;
	pChar *name = (items > 2 && SvOK(ST(2))) ? SvPV(ST(2), na) : 0;
	WFlags f = (items > 3) ? (WFlags)SvIV(ST(3)) : 0;
	CODE:
	RETVAL = new PProgressBar(parent, name, f);
	OUTPUT:
	RETVAL
    CASE:
	PREINIT:
	int totalSteps = SvIV(ST(1));
	pWidget *parent = (items > 2 && SvOK(ST(2))) ? pextract(pWidget, 2) : 0;
	pChar *name = (items > 3 && SvOK(ST(3))) ? SvPV(ST(3), na) : 0;
	WFlags f = (items > 4) ? (WFlags)SvIV(ST(4)) : 0;
	CODE:
	RETVAL = new PProgressBar(totalSteps, parent, name, f);
	OUTPUT:
	RETVAL

void
QProgressBar::DESTROY()
    CODE:
    if(want_destroy(ST(0)))
        delete THIS;

int
QProgressBar::progress()

void
QProgressBar::reset()

void
QProgressBar::setProgress(progress)
    int progress

void
QProgressBar::setTotalSteps(totalSteps)
    int totalSteps

int
QProgressBar::totalSteps()


MODULE = QProgressBar	PACKAGE = QProgressBar	 PREFIX = virtual_

void
pProgressBar::virtual_drawContents(p)
    QPainter *p

bool
pProgressBar::virtual_setIndicator(progress_str, progress, totalSteps)
    QString progress_str
    int progress
    int totalSteps
    OUTPUT:
    progress_str

void
pProgressBar::virtual_show()

PSize *
pProgressBar::virtual_sizeHint()
    CODE:
    RETVAL = new PSize(THIS->virtual_sizeHint());
    OUTPUT:
    RETVAL
