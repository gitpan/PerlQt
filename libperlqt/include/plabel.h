#ifndef PLABEL_H
#define PLABEL_H

/*
 * Declaration of the PLabel class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qlabel.h"
#include "psize.h"
#include "pqt.h"
#include "virtual.h"

class PLabel : public QLabel, public PLabel_virtualize {
    QLabel_virtual_functions
public:
    PLabel(QWidget *parent = 0, const char *name = 0, WFlags f = 0) :
	QLabel(parent, name, f) {}
    PLabel(const char *text, QWidget *parent = 0, const char *name = 0,
	   WFlags f = 0) : QLabel(text, parent, name, f) {}
};

class pLabel : public QLabel {
public:
    QSize virtual_sizeHint() const { return QLabel::sizeHint(); }
    void virtual_drawContents(QPainter *p) { QLabel::drawContents(p); }
};

#endif  // PLABEL_H
