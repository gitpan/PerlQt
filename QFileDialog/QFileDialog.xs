/*
 * PerlQt interface to qfiledlg.h
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pfiledlg.h"

MODULE = QFileDialog		PACKAGE = QFileDialog

PROTOTYPES: DISABLE

PFileDialog *
PFileDialog::new(...)
    CASE: items == 1
	CODE:
	RETVAL = new PFileDialog();
	OUTPUT:
	RETVAL
    CASE: sv_isobject(ST(1))
	PREINIT:
	QWidget *parent = pextract(QWidget, 1);
	char *name = (items > 2 && SvOK(ST(2))) ? SvPV(ST(2), na) : 0;
	bool modal = (items > 3) ? (SvTRUE(ST(3)) ? TRUE : FALSE) : FALSE;
	CODE:
	RETVAL = new PFileDialog(parent, name, modal);
	OUTPUT:
	RETVAL
    CASE:
	PREINIT:
	char *dirName = SvPV(ST(1), na);
	char *filter = (items > 2 && SvOK(ST(2))) ? SvPV(ST(2), na) : 0;
	pWidget *parent = (items > 3) ? pextract(pWidget, 3) : 0;
	char *name = (items > 4 && SvOK(ST(4))) ? SvPV(ST(4), na) : 0;
	bool modal = (items > 5) ? (SvTRUE(ST(5)) ? TRUE : FALSE) : FALSE;
	CODE:
	RETVAL = new PFileDialog(dirName, filter, parent, name, modal);
	OUTPUT:
	RETVAL

void
QFileDialog::DESTROY()
    CODE:
    if(want_destroy(ST(0)))
	delete THIS;

const char *
QFileDialog::dirPath()

const char *
getOpenFileName(dir = 0, filter = 0, parent = 0, name = 0)
    pChar *dir
    pChar *filter
    pWidget *parent
    pChar *name
    CODE:
    RETVAL = QFileDialog::getOpenFileName(dir, filter, parent, name);
    OUTPUT:
    RETVAL

const char *
getSaveFileName(dir = 0, filter = 0, parent = 0, name = 0)
    pChar *dir
    pChar *filter
    pWidget *parent
    pChar *name
    CODE:
    RETVAL = QFileDialog::getSaveFileName(dir, filter, parent, name);
    OUTPUT:
    RETVAL

void
QFileDialog::rereadDir()

const char *
QFileDialog::selectedFile()

void
QFileDialog::setDir(dir)
    char *dir


MODULE = QFileDialog	PACKAGE = QFileDialog	PREFIX = virtual_

void
pFileDialog::virtual_resizeEvent(event)
    QResizeEvent *event
