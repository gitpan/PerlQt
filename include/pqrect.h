#ifndef PQRECT_H
#define PQRECT_H

/*
 * Definition of the CQRect class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqt.h>
#include <qrect.h>

class CQRect {
    QRect rect;
public:
    CQRect() {}
    CQRect(const QRect &r) { *this = r; }
    CQRect(const QRect *r) { *this = r; }
    QRect &operator =(const QRect &r) { rect = r; return rect; }
    QRect &operator =(const QRect *r) { if(r) rect = *r; return rect; }
    operator void *() { return new QRect(rect); }
    operator QRect &() { return rect; }
};

typedef CQRect MQRect;

#endif  // PQRECT_H
