#ifndef PQSCRBAR_H
#define PQSCRBAR_H

/*
 * QScrollBar interface.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqwidget.h>
#include <pqrangect.h>
#include <qscrbar.h>

#define QScrollBar_functions
#define QScrollBar_inlines(class)
#define QScrollBar_virtual_functions					\
    QWidget_virtual_functions						\
    QRangeControl_virtual_functions					\
    QScrollBar_functions
#define QScrollBar_virtual_inlines(class)				\
    QWidget_virtual_inlines(class)					\
    QRangeControl_virtual_inlines(class)				\
    QScrollBar_inlines(class)

class QScrollBar_virtualize :
    public QWidget_virtualize, public QRangeControl_virtualize {};

class VQScrollBar : public QScrollBar, public QScrollBar_virtualize {
    QScrollBar_virtual_functions
public:
    VQScrollBar(QWidget *parent = 0, const char *name = 0) :
	QScrollBar(parent, name) {}
    VQScrollBar(QScrollBar::Orientation orientation, QWidget *parent = 0,
		const char *name = 0) :
	QScrollBar(orientation, parent, name) {}
    VQScrollBar(int minValue, int maxValue, int lineStep, int pageStep,
		int value, QScrollBar::Orientation orientation,
		QWidget *parent = 0, const char *name = 0) :
	QScrollBar(minValue, maxValue, lineStep, pageStep, value, orientation,
		   parent, name) {}
};

class PQScrollBar : public QScrollBar {
    QScrollBar_virtual_inlines(QScrollBar)
public:
    QRect sliderRect() const { return QScrollBar::sliderRect(); }
    int sliderStart() const { return QScrollBar::sliderStart(); }
};

typedef const QScrollBar CQScrollBar;

#endif  // PQSCRBAR_H
