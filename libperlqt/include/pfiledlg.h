#ifndef PFILEDLG_H
#define PFILEDLG_H

/*
 * Declaration of the PFileDialog class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qfiledlg.h"
#include "virtual.h"

class PFileDialog : public QFileDialog, public PFileDialog_virtualize {
    QFileDialog_virtual_functions
public:
    PFileDialog(const char *dirName, const char *filter = 0,
		QWidget *parent = 0, const char *name = 0,
		bool modal = FALSE) :
	QFileDialog(dirName, filter, parent, name, modal) {}
    PFileDialog(QWidget *parent = 0, const char *name = 0,
		bool modal = FALSE) :
	QFileDialog(parent, name, modal) {}
};

class pFileDialog : public QFileDialog {
public:
    void virtual_resizeEvent(QResizeEvent *e) { QFileDialog::resizeEvent(e); }
};

#endif  // PFILEDLG_H
