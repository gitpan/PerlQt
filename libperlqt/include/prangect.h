#ifndef PRANGECT_H
#define PRANGECT_H

/*
 * Declaration of the PRangeControl class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qrangect.h"
#include "qscrbar.h"
#include "qslider.h"
#include "pvirtual.h"

#define QRangeControl_virtual_functions					\
protected:								\
    void rangeChange();							\
    void stepChange();							\
    void valueChange();

class PRangeControl_virtualize : virtual public virtualize {
protected:
    void PRangeControl_rangeChange();
    void PRangeControl_stepChange();
    void PRangeControl_valueChange();
};

class PRangeControl : public QRangeControl, public PRangeControl_virtualize {
    QRangeControl_virtual_functions
public:
    PRangeControl() {}
    PRangeControl(int minValue, int maxValue, int lineStep, int pageStep,
		  int value) :
	QRangeControl(minValue, maxValue, lineStep, pageStep, value) {}
};

class pRangeControl : public QRangeControl {
public:
    void virtual_rangeChange() { QRangeControl::rangeChange(); }
    void virtual_stepChange() { QRangeControl::stepChange(); }
    void virtual_valueChange() { QRangeControl::valueChange(); }

    void protected_directSetValue(int v) { QRangeControl::directSetValue(v); }
    int protected_prevValue() const { return QRangeControl::prevValue(); }
};

#endif  // PRANGECT_H
