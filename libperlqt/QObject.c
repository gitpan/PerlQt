/*
 * VQObject definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqobject.h>

const char *VQObject::className() const {
    return QObject_className();
}

void VQObject::connectNotify(const char *signal) {
    QObject_connectNotify(signal);
}

void VQObject::disconnectNotify(const char *signal) {
    QObject_disconnectNotify(signal);
}

bool VQObject::event(QEvent *event) {
    return QObject_event(event);
}

bool VQObject::eventFilter(QObject *obj, QEvent *event) {
    return QObject_eventFilter(obj, event);
}

void VQObject::initMetaObject() {
    if(!QObject::metaObject()) QObject::initMetaObject();
    QObject_initMetaObject();
}

QMetaObject *VQObject::metaObject() const {
    return QObject_metaObject();
}

void VQObject::timerEvent(QTimerEvent *event) {
    QObject_timerEvent(event);
}


const char *QObject_virtualize::QObject_className() const {
    return getClassName();
}

void QObject_virtualize::QObject_connectNotify(const char *signal) {
    voidCall("connectNotify", pArgPV(signal));
}

void QObject_virtualize::QObject_disconnectNotify(const char *signal) {
    voidCall("disconnectNotify", pArgPV(signal));
}

bool QObject_virtualize::QObject_event(QEvent *event) {
    return prBOOL(retCall("event", pArgREF(event, QEvent)));
}

bool QObject_virtualize::QObject_eventFilter(QObject *obj, QEvent *event) {
    return prBOOL(
	retCall("eventFilter", pArgREF(obj, QObject), pArgREF(event, QEvent))
    );
}

void QObject_virtualize::QObject_initMetaObject() {
    char *superClass = NULL;
    {
	QString name = getClassName();
	name += "::ISA";
	AV *av = perl_get_av(name.data(), TRUE);
	I32 len = av_len(av) + 1;
	for(int i = 0; i < len; i++) {
	    SV *sv = safe_av_fetch(av, i);
	    if(sv_derived_from(sv, "QObject")) {
		superClass = SvPV(sv, na);
		break;
	    }
	}
    }
}

#include <qdict.h>
#include <qmetaobj.h>

QMetaObject *QObject_virtualize::QObject_metaObject() const {
    QDict<QMetaObject> MetaObjectDict;
    return MetaObjectDict[getClassName()];
}

void QObject_virtualize::QObject_timerEvent(QTimerEvent *event) {
    voidCall("timerEvent", pArgREF(event, QTimerEvent));
}
