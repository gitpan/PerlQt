/*
 * PAccel definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "paccel.h"

const char *PAccel::className() const {
    return PObject_className();
}

bool PAccel::event(QEvent *event) {
    bool ret = PObject_event(event);
    if(pfailed) ret = QAccel::event(event);
    return ret;
}

bool PAccel::eventFilter(QObject *obj, QEvent *event) {
    bool ret = PObject_eventFilter(obj, event);
    if(pfailed) ret = QAccel::eventFilter(obj, event);
    return ret;
}

QMetaObject *PAccel::metaObject() const {
    QMetaObject *ret = PObject_metaObject();
    if(pfailed) ret = QAccel::metaObject();
    return ret;
}

void PAccel::initMetaObject() {
    if(!QAccel::metaObject()) QAccel::initMetaObject();
    PObject_initMetaObject();
}

void PAccel::timerEvent(QTimerEvent *event) {
    PObject_timerEvent(event);
    if(pfailed) QAccel::timerEvent(event);
}


