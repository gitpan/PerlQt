/*
 * PerlQt interface to qdialog.h
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pdialog.h"
#include "pqt.h"
#include "enum.h"

#define STORE_key(key) enumIV(hv, MSTR(key), QDialog::key)
inline void init_enum() {
    HV *hv = perl_get_hv("QDialog::Dialog", TRUE | GV_ADDMULTI);

    STORE_key(Rejected);
    STORE_key(Accepted);
}

MODULE = QDialog		PACKAGE = QDialog

PROTOTYPES: ENABLE

BOOT:
     init_enum();

PDialog *
PDialog::new(parent = 0, name = 0, modal = FALSE, f = 0)
    QWidget *parent
    char *name
    bool modal
    WFlags f

int
QDialog::exec()

int
QDialog::result()


MODULE = QDialog	PACKAGE = QDialog	PREFIX = virtual_

void
pDialog::virtual_closeEvent(event)
    QCloseEvent *event

void
pDialog::virtual_done(result)
    int result

void
pDialog::virtual_keyPressEvent(event)
    QKeyEvent *event

void
pDialog::virtual_move(...)
    CASE: items > 2
	PREINIT:
	int x = SvIV(ST(1));
	int y = SvIV(ST(2));
	CODE:
	THIS->virtual_move(x, y);
    CASE: items > 1
	PREINIT:
	QPoint *point = pextract(QPoint, 1);
	CODE:
	THIS->QDialog::move(*point);

void
pDialog::virtual_resize(...)
    CASE: items > 2
	PREINIT:
	int w = SvIV(ST(1));
	int h = SvIV(ST(2));
	CODE:
	THIS->virtual_resize(w, h);
    CASE: items > 1
	PREINIT:
	QSize *size = pextract(QSize, 1);
	CODE:
	THIS->QDialog::resize(*size);

void
pDialog::virtual_setGeometry(...)
    CASE: items > 4
	PREINIT:
	int x = SvIV(ST(1));
	int y = SvIV(ST(2));
	int w = SvIV(ST(3));
	int h = SvIV(ST(4));
	CODE:
	THIS->virtual_setGeometry(x, y, w, h);
    CASE: items > 1
	PREINIT:
	QRect *rect = pextract(QRect, 1);
	CODE:
	THIS->QDialog::setGeometry(*rect);

void
pDialog::virtual_show()


MODULE = QDialog	PACKAGE = QDialog	PREFIX = protected_

void
pDialog::protected_accept()

void
pDialog::protected_reject()

void
pDialog::protected_setResult(r)
    int r