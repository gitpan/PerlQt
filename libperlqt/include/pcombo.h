#ifndef PCOMBO_H
#define PCOMBO_H

/*
 * Declaration of the PComboBox class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qcombo.h"
#include "pwidget.h"

#define QComboBox_virtual_functions QWidget_virtual_functions

class PComboBox_virtualize : public PWidget_virtualize {};

class PComboBox : public QComboBox, public PComboBox_virtualize {
    QComboBox_virtual_functions
public:
    PComboBox(QWidget *parent = 0, const char *name = 0) :
	QComboBox(parent, name) {}
    PComboBox(bool rw, QWidget *parent = 0, const char *name = 0) :
	QComboBox(rw, parent, name) {}
};

class pComboBox : public QComboBox {
public:
    void virtual_keyPressEvent(QKeyEvent *e) { QComboBox::keyPressEvent(e); }
    void virtual_mouseDoubleClickEvent(QMouseEvent *e) {
	QComboBox::mouseDoubleClickEvent(e);
    }
    void virtual_mouseMoveEvent(QMouseEvent *e) {
	QComboBox::mouseMoveEvent(e);
    }
    void virtual_mousePressEvent(QMouseEvent *e) {
	QComboBox::mousePressEvent(e);
    }
    void virtual_mouseReleaseEvent(QMouseEvent *e) {
	QComboBox::mouseReleaseEvent(e);
    }
    void virtual_paintEvent(QPaintEvent *e) { QComboBox::paintEvent(e); }
    void virtual_resizeEvent(QResizeEvent *e) { QComboBox::resizeEvent(e); }
    void virtual_setBackgroundColor(const QColor &c) {
	QComboBox::setBackgroundColor(c);
    }
    void virtual_setEnabled(bool b) { QComboBox::setEnabled(b); }
    void virtual_setFont(const QFont &f) { QComboBox::setFont(f); }
    void virtual_setPalette(const QPalette &p) { QComboBox::setPalette(p); }
    QSize virtual_sizeHint() { return QComboBox::sizeHint(); }

    void protected_popup() { QComboBox::popup(); }
};

typedef QComboBox::Policy QComboBox__Policy;

#endif  // PCOMBO_H
