#ifndef PSLIDER_H
#define PSLIDER_H

/*
 * Declaration of the PSlider class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include <qslider.h>
#include "virtual.h"

typedef QSlider::Orientation QSlider__Orientation;
typedef QSlider::TickSetting QSlider__TickSetting;

class PSlider : public QSlider, public PSlider_virtualize {
    QSlider_virtual_functions
public:
    PSlider(QWidget *parent = 0, const char *name = 0) :
	QSlider(parent, name) {}
    PSlider(QSlider::Orientation orientation, QWidget *parent = 0,
	    const char *name = 0) :
	QSlider(orientation, parent, name) {}
    PSlider(int minValue, int maxValue, int step, int value,
	    QSlider::Orientation orientation, QWidget *parent = 0,
	    const char *name = 0) :
	QSlider(minValue, maxValue, step, value, orientation, parent, name) {}
};

class pSlider : public QSlider {
public:
    void virtual_keyPressEvent(QKeyEvent *e) { QSlider::keyPressEvent(e); }
    void virtual_mouseMoveEvent(QMouseEvent *e) { QSlider::mouseMoveEvent(e); }
    void virtual_mousePressEvent(QMouseEvent *e) {
	QSlider::mousePressEvent(e);
    }
    void virtual_mouseReleaseEvent(QMouseEvent *e) {
	QSlider::mouseReleaseEvent(e);
    }
    void virtual_paintEvent(QPaintEvent *e) { QSlider::paintEvent(e); }
    void virtual_paintSlider(QPainter *p, const QRect &r) {
	QSlider::paintSlider(p, r);
    }
    void virtual_rangeChange() { QSlider::rangeChange(); }
    void virtual_resizeEvent(QResizeEvent *e) { QSlider::resizeEvent(e); }
    void virtual_setPalette(const QPalette &p) { QSlider::setPalette(p); }
    void virtual_setTickInterval(int i) { QSlider::setTickInterval(i); }
    void virtual_setTickmarks(QSlider::TickSetting s) {
	QSlider::setTickmarks(s);
    }
    QSize virtual_sizeHint() const { return QSlider::sizeHint(); }
    int virtual_thickness() const { return QSlider::thickness(); }
    void virtual_valueChange() { QSlider::valueChange(); }

    void protected_drawTicks(QPainter *p, int d, int w, int i = 1) {
	QSlider::drawTicks(p, d, w, i);
    }
    void protected_drawWinGroove(QPainter *p, QCOORD c) {
	QSlider::drawWinGroove(p, c);
   }
};

#endif  // PSLIDER_H
