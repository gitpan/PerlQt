/*
 * VQAccel definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqaccel.h>

const char *VQAccel::className() const {
    return QObject_className();
}

void VQAccel::connectNotify(const char *signal) {
    QObject_connectNotify(signal);
}

void VQAccel::disconnectNotify(const char *signal) {
    QObject_disconnectNotify(signal);
}

bool VQAccel::event(QEvent *event) {
    return QObject_event(event);
}

bool VQAccel::eventFilter(QObject *obj, QEvent *event) {
    return QObject_eventFilter(obj, event);
}

void VQAccel::initMetaObject() {
    if(!QAccel::metaObject()) QAccel::initMetaObject();
    QObject_initMetaObject();
}

QMetaObject *VQAccel::metaObject() const {
    return QObject_metaObject();
}

void VQAccel::timerEvent(QTimerEvent *event) {
    QObject_timerEvent(event);
}


