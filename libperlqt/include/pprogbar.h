#ifndef PPROGBAR_H
#define PPROGBAR_H

/*
 * Declaration of the PProgressBar class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qprogbar.h"
#include "pframe.h"

#define QProgressBar_virtual_functions					\
    QFrame_virtual_functions						\
protected:								\
    bool setIndicator(QString &, int, int);

class PProgressBar_virtualize : public PFrame_virtualize {
protected:
    bool PProgressBar_setIndicator(QString &, int, int);
};

class PProgressBar : public QProgressBar, public PProgressBar_virtualize {
    QProgressBar_virtual_functions
public:
    PProgressBar(QWidget *parent = 0, const char *name = 0, WFlags f = 0) :
	QProgressBar(parent, name, f) {}
    PProgressBar(int totalSteps, QWidget *parent = 0, const char *name = 0,
		 WFlags f = 0) : QProgressBar(totalSteps, parent, name, f) {}
};

class pProgressBar : public QProgressBar {
public:
    void virtual_drawContents(QPainter *p) { QProgressBar::drawContents(p); }
    bool virtual_setIndicator(QString &ps, int p, int t) {
	return QProgressBar::setIndicator(ps, p, t);
    }
    void virtual_show() { QProgressBar::show(); }
    QSize virtual_sizeHint() const { return QProgressBar::sizeHint(); }
};

#endif  // PPROGBAR_H
