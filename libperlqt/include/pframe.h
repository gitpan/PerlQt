#ifndef PFRAME_H
#define PFRAME_H

/*
 * Declaration of the PFrame class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qframe.h"
#include "pwidget.h"

#define QFrame_virtual_functions					\
    QWidget_virtual_functions						\
protected:								\
    void drawFrame(QPainter *);						\
    void drawContents(QPainter *);					\
    void frameChanged();

class PFrame_virtualize : public PWidget_virtualize {
protected:
    void PFrame_drawContents(QPainter *);
    void PFrame_drawFrame(QPainter *);
    void PFrame_frameChanged();
};

class PFrame : public QFrame, public PFrame_virtualize {
    QFrame_virtual_functions
public:
    PFrame(QWidget *parent = 0, const char *name = 0, WFlags f = 0,
	   bool allowLines = TRUE) : QFrame(parent, name, f, allowLines) {}
};

class pFrame : public QFrame {
public:
    void virtual_drawContents(QPainter *p) { QFrame::drawContents(p); }
    void virtual_drawFrame(QPainter *p) { QFrame::drawFrame(p); }
    void virtual_frameChanged() { QFrame::frameChanged(); }
    void virtual_paintEvent(QPaintEvent *e) { QFrame::paintEvent(e); }
    void virtual_resizeEvent(QResizeEvent *e) { QFrame::resizeEvent(e); }

    void protected_setFrameRect(const QRect &r) { QFrame::setFrameRect(r); }
};

#endif  // PFRAME_H
