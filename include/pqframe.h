#ifndef PQFRAME_H
#define PQFRAME_H

/*
 * Declaration of the VQFrame class.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqwidget.h>
#include <qframe.h>

#define QFrame_functions						\
protected:								\
    void drawContents(QPainter *);					\
    void drawFrame(QPainter *);						\
    void frameChanged();

#define QFrame_inlines(class)						\
public:									\
    void v_drawContents(QPainter *a) { class::drawContents(a); }	\
    void v_drawFrame(QPainter *a) { class::drawFrame(a); }		\
    void v_frameChanged() { class::frameChanged(); }

#define QFrame_virtual_functions QWidget_virtual_functions QFrame_functions
#define QFrame_virtual_inlines(class)					\
    QWidget_virtual_inlines(class)					\
    QFrame_inlines(class)

class QFrame_virtualize : public QWidget_virtualize {
public:
    void QFrame_drawContents(QPainter *);
    void QFrame_drawFrame(QPainter *);
    void QFrame_frameChanged();
};

class VQFrame : public QFrame, public QFrame_virtualize {
    QFrame_virtual_functions
public:
    VQFrame(QWidget *parent = 0, const char *name = 0, WFlags f = 0,
	    bool allowLines = TRUE) : QFrame(parent, name, f, allowLines) {}
};

class PQFrame : public QFrame {
    QFrame_virtual_inlines(QFrame)
public:
    void setFrameRect(const QRect &a) { QFrame::setFrameRect(a); }
};

typedef const QFrame CQFrame;

#endif  // PQFRAME_H
