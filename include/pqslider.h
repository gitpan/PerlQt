#ifndef PQSLIDER_H
#define PQSLIDER_H

/*
 * QSlider interface.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqwidget.h>
#include <pqrangect.h>
#include <qslider.h>

#define QSlider_functions
#define QSlider_inlines(class)
#define QSlider_virtual_functions					\
    QWidget_virtual_functions						\
    QRangeControl_virtual_functions					\
    QSlider_functions
#define QSlider_virtual_inlines(class)					\
    QWidget_virtual_inlines(class)					\
    QRangeControl_virtual_inlines(class)				\
    QSlider_inlines(class)

class QSlider_virtualize :
    public QWidget_virtualize, public QRangeControl_virtualize {};

class VQSlider : public QSlider, public QSlider_virtualize {
    QSlider_virtual_functions
public:
    VQSlider(QWidget *parent = 0, const char *name = 0) :
	QSlider(parent, name) {}
    VQSlider(QSlider::Orientation orientation, QWidget *parent = 0,
	     const char *name = 0) :
	QSlider(orientation, parent, name) {}
    VQSlider(int minValue, int maxValue, int step, int value,
	     QSlider::Orientation orientation,
	     QWidget *parent = 0, const char *name = 0) :
	QSlider(minValue, maxValue, step, value, orientation, parent, name) {}
};

class PQSlider : public QSlider {
    QSlider_virtual_inlines(QSlider)
};

typedef const QSlider CQSlider;

#endif  // PQSLIDER_H
