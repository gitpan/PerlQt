#ifndef PQCOLOR_H
#define PQCOLOR_H

/*
 * Definition of the CQColor class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqt.h>
#include <qcolor.h>

class CQColor {
    QColor color;
public:
    CQColor() {}
    CQColor(const QColor &c) { *this = c; }
    CQColor(const QColor *c) { *this = c; }
    QColor &operator =(const QColor &c) { color = c; return color; }
    QColor &operator =(const QColor *c) { if(c) color = *c; return color; }
    operator void *() { return new QColor(color); }
    operator QColor &() { return color; }
};

typedef CQColor MQColor;

#endif  // PQCOLOR_H
