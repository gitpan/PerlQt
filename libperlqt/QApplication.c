/*
 * VQApplication definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqapp.h>

const char *VQApplication::className() const {
    return QObject_className();
}

void VQApplication::connectNotify(const char *signal) {
    QObject_connectNotify(signal);
}

void VQApplication::disconnectNotify(const char *signal) {
    QObject_disconnectNotify(signal);
}

bool VQApplication::event(QEvent *event) {
    return QObject_event(event);
}

bool VQApplication::eventFilter(QObject *obj, QEvent *event) {
    return QObject_eventFilter(obj, event);
}

void VQApplication::initMetaObject() {
    if(!QApplication::metaObject()) QApplication::initMetaObject();
    QObject_initMetaObject();
}

QMetaObject *VQApplication::metaObject() const {
    return QObject_metaObject();
}

void VQApplication::timerEvent(QTimerEvent *event) {
    QObject_timerEvent(event);
}


bool VQApplication::notify(QObject *receiver, QEvent *event) {
    return QApplication_notify(receiver, event);
}


bool QApplication_virtualize::QApplication_notify(QObject *receiver,
						  QEvent *event) {
    return prBOOL(
	retCall("notify", pArgREF(receiver, QObject), pArgREF(event, QEvent))
    );
}
