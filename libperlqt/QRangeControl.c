/*
 * VQRangeControl definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqrangect.h>

void VQRangeControl::rangeChange() {
    QRangeControl_rangeChange();
}

void VQRangeControl::stepChange() {
    QRangeControl_stepChange();
}

void VQRangeControl::valueChange() {
    QRangeControl_valueChange();
}


void QRangeControl_virtualize::QRangeControl_rangeChange() {
    voidCall("rangeChange");
}

void QRangeControl_virtualize::QRangeControl_stepChange() {
    voidCall("stepChange");
}

void QRangeControl_virtualize::QRangeControl_valueChange() {
    voidCall("valueChange");
}
