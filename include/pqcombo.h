#ifndef PQCOMBO_H
#define PQCOMBO_H

/*
 * QComboBox interface.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqwidget.h>
#include <qcombo.h>

#define QComboBox_functions
#define QComboBox_inlines(class)
#define QComboBox_virtual_functions					\
    QWidget_functions							\
    QComboBox_functions							\
public:									\
    const char *className() const;					\
    bool event(QEvent *);						\
    QMetaObject *metaObject() const;					\
protected:								\
    void connectNotify(const char *);					\
    void disconnectNotify(const char *);				\
    void initMetaObject();						\
    void timerEvent(QTimerEvent *);

#define QComboBox_virtual_inlines(class)				\
    QWidget_inlines(class)						\
    QComboBox_inlines(class)						\
public:									\
    const char *v_className() const { return class::className(); }	\
    void v_connectNotify(const char *a) { class::connectNotify(a); }	\
    void v_disconnectNotify(const char *a) {				\
	class::disconnectNotify(a);					\
    }									\
    bool v_event(QEvent *a) { return class::event(a); }			\
    void v_initMetaObject() { class::initMetaObject(); }		\
    QMetaObject *v_metaObject() const { return class::metaObject(); }	\
    void v_timerEvent(QTimerEvent *a1) { class::timerEvent(a1); }

class QComboBox_virtualize : public QWidget_virtualize {};

class VQComboBox : public QComboBox, public QComboBox_virtualize {
    QComboBox_virtual_functions
public:
    VQComboBox(QWidget *parent = 0, const char *name = 0) :
	QComboBox(parent, name) {}
    VQComboBox(bool rw, QWidget *parent = 0, const char *name = 0) :
	QComboBox(rw, parent, name) {}
};

class PQComboBox : public QComboBox { QComboBox_virtual_inlines(QComboBox) };

typedef const QComboBox CQComboBox;

#endif  // PQCOMBO_H

