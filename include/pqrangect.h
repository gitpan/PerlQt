#ifndef PQRANGECT_H
#define PQRANGECT_H

/*
 * QRangeControl interface.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pvirtual.h>
#include <qrangect.h>

#define QRangeControl_functions						\
protected:								\
    void rangeChange();							\
    void stepChange();							\
    void valueChange();

#define QRangeControl_inlines(class)					\
public:									\
    void v_rangeChange() { class::rangeChange(); }			\
    void v_stepChange() { class::stepChange(); }			\
    void v_valueChange() { class::valueChange(); }

#define QRangeControl_virtual_functions QRangeControl_functions
#define QRangeControl_virtual_inlines(class) QRangeControl_inlines(class)

class QRangeControl_virtualize : virtual public virtualize {
public:
    void QRangeControl_rangeChange();
    void QRangeControl_stepChange();
    void QRangeControl_valueChange();
};

class VQRangeControl : public QRangeControl, public QRangeControl_virtualize {
    QRangeControl_virtual_functions
public:
    VQRangeControl() {}
    VQRangeControl(int minValue, int maxValue, int lineStep, int pageStep,
		   int value) :
	QRangeControl(minValue, maxValue, lineStep, pageStep, value) {}
};

class PQRangeControl : public QRangeControl {
    QRangeControl_virtual_inlines(QRangeControl)
public:
    void directSetValue(int a) { QRangeControl::directSetValue(a); }
    int prevValue() const { return QRangeControl::prevValue(); }
};

typedef const QRangeControl CQRangeControl;

#endif  // PQRANGECT_H
