#ifndef PPROGDLG_H
#define PPROGDLG_H

/*
 * Declaration of the PProgressDialog class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qprogdlg.h"
#include "psemimodal.h"

#define QProgressDialog_virtual_functions QSemiModal_virtual_functions

class PProgressDialog_virtualize : public PSemiModal_virtualize {};

class PProgressDialog : public QProgressDialog, public PProgressDialog_virtualize {
    QProgressDialog_virtual_functions
public:
    PProgressDialog(QWidget *parent = 0, const char *name = 0,
		    bool modal = FALSE, WFlags f = 0) :
	QProgressDialog(parent, name, f) {}
    PProgressDialog(const char *labelText, const char *cancelButtonText,
		    int totalSteps, QWidget *parent = 0, const char *name = 0,
		    bool modal = FALSE, WFlags f = 0) :
	QProgressDialog(labelText, cancelButtonText, totalSteps, parent, name,
			modal, f) {}
};

class pProgressDialog : public QProgressDialog {
public:
    void virtual_resizeEvent(QResizeEvent *e) {
	QProgressDialog::resizeEvent(e);
    }
    QSize virtual_sizeHint() { return QProgressDialog::sizeHint(); }
};

#endif  // PPROGDLG_H
