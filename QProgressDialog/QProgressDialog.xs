/*
 * PerlQt interface to qprogdlg.h
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pprogdlg.h"
#include "psize.h"

MODULE = QProgressDialog	PACKAGE = QProgressDialog

PROTOTYPES: DISABLE

PProgressDialog *
PProgressDialog::new(...)
    CASE: items > 3 && !sv_isobject(ST(1))
	PREINIT:
	char *labelText = SvPV(ST(1), na);
	char *cancelButtonText = SvPV(ST(2), na);
	int totalSteps = SvIV(ST(3));
	pWidget *parent = (items > 4) ? pextract(pWidget, 4) : 0;
	pChar *name = (items > 5 && SvOK(ST(5))) ? SvPV(ST(5), na) : 0;
	bool modal = (items > 6) ? (SvTRUE(ST(6)) ? TRUE : FALSE) : FALSE;
	WFlags f = (items > 7) ? SvIV(ST(7)) : 0;
	CODE:
	RETVAL = new PProgressDialog(labelText, cancelButtonText, totalSteps,
				     parent, name, modal, f);
	OUTPUT:
	RETVAL
    CASE:
	PREINIT:
	pWidget *parent = (items > 1) ? pextract(pWidget, 1) : 0;
	pChar *name = (items > 2 && SvOK(ST(2))) ? SvPV(ST(2), na) : 0;
	bool modal = (items > 3) ? (SvTRUE(ST(3)) ? TRUE : FALSE) : FALSE;
	WFlags f = (items > 4) ? SvIV(ST(4)) : 0;
	CODE:
	RETVAL = new PProgressDialog(parent, name, modal, f);
	OUTPUT:
	RETVAL

void
QProgressDialog::DESTROY()
    CODE:
    if(want_destroy(ST(0)))
        delete THIS;

void
QProgressDialog::cancel()

int
QProgressDialog::progress()

void
QProgressDialog::reset()

void
QProgressDialog::setBar(bar)
    QProgressBar *bar

void
QProgressDialog::setCancelButton(button)
    QPushButton *button

void
QProgressDialog::setCancelButtonText(text)
    const char *text

void
QProgressDialog::setLabel(label)
    QLabel *label

void
QProgressDialog::setLabelText(text)
    const char *text

void
QProgressDialog::setProgress(progress)
    int progress

void
QProgressDialog::setTotalSteps(totalSteps)
    int totalSteps

int
QProgressDialog::totalSteps()

bool
QProgressDialog::wasCancelled()


MODULE = QProgressDialog    PACKAGE = QProgressDialog	PREFIX = virtual_

void
pProgressDialog::virtual_resizeEvent(event)
    QResizeEvent *event

QSize *
pProgressDialog::virtual_sizeHint()
    CODE:
    RETVAL = new PSize(THIS->virtual_sizeHint());
    OUTPUT:
    RETVAL
