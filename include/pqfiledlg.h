#ifndef PQFILEDLG_H
#define PQFILEDLG_H

/*
 * QFileDialog interface.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqdialog.h>
#include <qfiledlg.h>

#define QFileDialog_functions
#define QFileDialog_inlines(class)
#define QFileDialog_virtual_functions					\
    QDialog_virtual_functions						\
    QFileDialog_functions
#define QFileDialog_virtual_inlines(class)				\
    QDialog_virtual_inlines(class)					\
    QFileDialog_inlines(class)

class QFileDialog_virtualize : public QDialog_virtualize {};

class VQFileDialog : public QFileDialog, public QFileDialog_virtualize {
    QFileDialog_virtual_functions
public:
    VQFileDialog(QWidget *parent = 0, const char *name = 0,
		 bool modal = FALSE) : QFileDialog(parent, name, modal) {}
    VQFileDialog(const char *dirName, const char *filter,
		 QWidget *parent = 0, const char *name = 0) :
	QFileDialog(dirName, filter, parent, name) {}
};

class PQFileDialog : public QFileDialog {
    QFileDialog_virtual_inlines(QFileDialog)
};

typedef const QFileDialog CQFileDialog;

#endif  // PQFILEDLG_H
