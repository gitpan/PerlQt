#ifndef PQPROGDLG_H
#define PQPROGDLG_H

/*
 * QProgressDialog interface.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqsemimodal.h>
#include <qprogdlg.h>

#define QProgressDialog_functions
#define QProgressDialog_inlines(class)
#define QProgressDialog_virtual_functions      				\
    QSemiModal_virtual_functions	       				\
    QProgressDialog_functions
#define QProgressDialog_virtual_inlines(class)				\
    QSemiModal_virtual_inlines(class)					\
    QProgressDialog_inlines(class)

class QProgressDialog_virtualize : public QSemiModal_virtualize {};

class VQProgressDialog : public QProgressDialog,
			 public QProgressDialog_virtualize {
    QProgressDialog_virtual_functions
public:
    VQProgressDialog(QWidget *parent = 0, const char *name = 0,
		     bool modal = FALSE, WFlags f = 0) :
	QProgressDialog(parent, name, modal, f) {}
    VQProgressDialog(const char *labelText, const char *cancelButtonText,
		     int totalSteps, QWidget *parent = 0, const char *name = 0,
		     bool modal = FALSE, WFlags f = 0) :
	QProgressDialog(labelText, cancelButtonText, totalSteps, parent, name,
			modal, modal) {}
};

class PQProgressDialog : public QProgressDialog {
    QProgressDialog_virtual_inlines(QProgressDialog)
};

typedef const QProgressDialog CQProgressDialog;

#endif  // PQPROGDLG_H
