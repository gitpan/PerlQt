/*
 * PTimer definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "ptimer.h"

const char *PTimer::className() const {
    return PObject_className();
}

bool PTimer::event(QEvent *event) {
    bool ret = PObject_event(event);
    if(pfailed) ret = QTimer::event(event);
    return ret;
}

bool PTimer::eventFilter(QObject *obj, QEvent *event) {
    bool ret = PObject_eventFilter(obj, event);
    if(pfailed) ret = QTimer::eventFilter(obj, event);
    return ret;
}

QMetaObject *PTimer::metaObject() const {
    QMetaObject *ret = PObject_metaObject();
    if(pfailed) ret = QTimer::metaObject();
    return ret;
}

void PTimer::initMetaObject() {
    if(!QTimer::metaObject()) QTimer::initMetaObject();
    PObject_initMetaObject();
}

void PTimer::timerEvent(QTimerEvent *event) {
    PObject_timerEvent(event);
    if(pfailed) QTimer::timerEvent(event);
}


