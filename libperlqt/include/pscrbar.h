#ifndef PSCRBAR_H
#define PSCRBAR_H

/*
 * Declaration of the PScrollBar class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qscrbar.h"
#include "prect.h"
#include "psize.h"
#include "enum.h"
#include "pqt.h"
#include "virtual.h"

typedef QScrollBar::Orientation QScrollBar__Orientation;

class PScrollBar : public QScrollBar, public PScrollBar_virtualize {
    QScrollBar_virtual_functions
public:
    PScrollBar(QWidget *parent = 0, const char *name = 0) :
	QScrollBar(parent, name) {}
    PScrollBar(QScrollBar::Orientation orientation, QWidget *parent = 0,
	       const char *name = 0) :
	QScrollBar(orientation, parent, name) {}
    PScrollBar(int minValue, int maxValue, int LineStep, int PageStep,
	       int value, QScrollBar::Orientation orientation,
	       QWidget *parent = 0, const char *name = 0) :
	QScrollBar(minValue, maxValue, LineStep, PageStep, value, orientation,
		   parent, name) {}
};

class pScrollBar : public QScrollBar {
public:
    void virtual_keyPressEvent(QKeyEvent *e) { QScrollBar::keyPressEvent(e); }
    void virtual_mouseMoveEvent(QMouseEvent *e) {
	QScrollBar::mouseMoveEvent(e);
    }
    void virtual_mousePressEvent(QMouseEvent *e) {
	QScrollBar::mousePressEvent(e);
    }
    void virtual_mouseReleaseEvent(QMouseEvent *e) {
	QScrollBar::mouseReleaseEvent(e);
    }
    void virtual_paintEvent(QPaintEvent *e) { QScrollBar::paintEvent(e); }
    void virtual_rangeChange() { QScrollBar::rangeChange(); }
    void virtual_resizeEvent(QResizeEvent *e) { QScrollBar::resizeEvent(e); }
    void virtual_setPalette(const QPalette &p) { QScrollBar::setPalette(p); }
    QSize virtual_sizeHint() const { return QScrollBar::sizeHint(); }
    void virtual_stepChange() { QScrollBar::stepChange(); }
    void virtual_timerEvent(QTimerEvent *e) { QScrollBar::timerEvent(e); }
    void virtual_valueChange() { QScrollBar::valueChange(); }

    QRect protected_sliderRect() const { return QScrollBar::sliderRect(); }
    int protected_sliderStart() const { return QScrollBar::sliderStart(); }
};

#endif  // PSCRBAR_H
