#ifndef PQOBJECT_H
#define PQOBJECT_H

/*
 * Declaration of the VQObject class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <psigslot.h>
#include <pvirtual.h>
#include <qobject.h>

#define QObject_functions						\
public:									\
    const char *className() const;					\
    bool event(QEvent *);						\
    bool eventFilter(QObject *, QEvent *);				\
    QMetaObject *metaObject() const;					\
protected:								\
    void connectNotify(const char *);					\
    void disconnectNotify(const char *);				\
    void initMetaObject();						\
    void timerEvent(QTimerEvent *);

#define QObject_inlines(class)						\
public:									\
    const char *v_className() const { return class::className(); }	\
    void v_connectNotify(const char *a) { class::connectNotify(a); }	\
    void v_disconnectNotify(const char *a) {				\
	class::disconnectNotify(a);					\
    }									\
    bool v_event(QEvent *a) { return class::event(a); }			\
    bool v_eventFilter(QObject *a1, QEvent *a2) {			\
	return class::eventFilter(a1, a2);				\
    }									\
    void v_initMetaObject() { class::initMetaObject(); }		\
    QMetaObject *v_metaObject() const { return class::metaObject(); }	\
    void v_timerEvent(QTimerEvent *a1) { class::timerEvent(a1); }

#define QObject_virtual_functions QObject_functions
#define QObject_virtual_inlines(class) QObject_inlines(class)

class QObject_virtualize : virtual public virtualize {
public:
    const char *QObject_className() const;
    void QObject_connectNotify(const char *);
    void QObject_disconnectNotify(const char *);
    bool QObject_event(QEvent *);
    bool QObject_eventFilter(QObject *, QEvent *);
    void QObject_initMetaObject();
    QMetaObject *QObject_metaObject() const;
    void QObject_timerEvent(QTimerEvent *);
};

class VQObject : public QObject, public QObject_virtualize {
    QObject_virtual_functions
public:
    VQObject(QObject *parent = 0, const char *name = 0) :
	QObject(parent, name) {}
};

class PQObject : public QObject {
    QObject_virtual_inlines(QObject)
public:
    void initMetaObject() { QObject::initMetaObject(); }
    QConnectionList *receivers(const char *signal) const {
	return QObject::receivers(signal);
    }
    const QObject *sender() { return QObject::sender(); }
};

typedef const QObject CQObject;

#endif  // PQOBJECT_H
