/*
 * PRangeControl definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "prangect.h"

void PRangeControl::rangeChange() {
    PRangeControl_rangeChange();
    if(pfailed) QRangeControl::rangeChange();
}

void PRangeControl::stepChange() {
    PRangeControl_stepChange();
    if(pfailed) QRangeControl::stepChange();
}

void PRangeControl::valueChange() {
    PRangeControl_valueChange();
    if(pfailed) QRangeControl::valueChange();
}


void PRangeControl_virtualize::PRangeControl_rangeChange() {
    voidCall("rangeChange");
}

void PRangeControl_virtualize::PRangeControl_stepChange() {
    voidCall("stepChange");
}

void PRangeControl_virtualize::PRangeControl_valueChange() {
    voidCall("valueChange");
}
