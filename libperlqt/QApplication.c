/*
 * PApplication definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "papp.h"

const char *PApplication::className() const {
    return PObject_className();
}

bool PApplication::event(QEvent *event) {
    bool ret = PObject_event(event);
    if(pfailed) ret = QApplication::event(event);
    return ret;
}

bool PApplication::eventFilter(QObject *obj, QEvent *event) {
    bool ret = PObject_eventFilter(obj, event);
    if(pfailed) ret = QApplication::eventFilter(obj, event);
    return ret;
}

QMetaObject *PApplication::metaObject() const {
    QMetaObject *ret = PObject_metaObject();
    if(pfailed) ret = QApplication::metaObject();
    return ret;
}

void PApplication::initMetaObject() {
    if(!QApplication::metaObject()) QApplication::initMetaObject();
    PObject_initMetaObject();
}

void PApplication::timerEvent(QTimerEvent *event) {
    PObject_timerEvent(event);
    if(pfailed) QApplication::timerEvent(event);
}


bool PApplication::notify(QObject *receiver, QEvent *event) {
    bool ret = PApplication_notify(receiver, event);
    if(pfailed) ret = QApplication::notify(receiver, event);
    return ret;
}


bool PApplication_virtualize::PApplication_notify(QObject *o, QEvent *e) {
    SV *r = retCallObj("notify", o, "QObject", e, "QEvent");
    if(pfailed) return FALSE;
    bool ret = SvTRUE(r) ? TRUE : FALSE;
    SvREFCNT_dec(r);
    return ret;
}
