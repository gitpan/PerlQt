#ifndef POBJECT_H
#define POBJECT_H

/*
 * Declaration of the PObject class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qobject.h"
#include "pvirtual.h"

#define QObject_virtual_functions					\
public:									\
    const char *className() const;					\
    bool event(QEvent *);						\
    bool eventFilter(QObject *, QEvent *);				\
    QMetaObject *metaObject() const;					\
protected:								\
    void initMetaObject();						\
    void timerEvent(QTimerEvent *);

class PObject_virtualize : virtual public virtualize {
public:
    const char *PObject_className() const;
    bool PObject_event(QEvent *);
    bool PObject_eventFilter(QObject *, QEvent *);
    QMetaObject *PObject_metaObject() const;
protected:
    void PObject_initMetaObject();
    void PObject_timerEvent(QTimerEvent *);
};

class PObject : public QObject, public PObject_virtualize {
    QObject_virtual_functions
public:
    PObject(QObject *parent=0, const char *name=0) : QObject(parent, name) {}
};

class pObject : public QObject {	// fix me
public:
    QConnectionList *protected_receivers(const char *signal) const {
	return receivers(signal);
    }
    void virtual_initMetaObject() { initMetaObject(); }
    void virtual_timerEvent(QTimerEvent *);
};

extern char *getPerlSuperClass(char *clname);
extern QMetaObject *metaObjectSetup(char *clname);

#endif  // POBJECT_H
