#ifndef PQPOINT_H
#define PQPOINT_H

/*
 * Definition of the CQPoint class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqt.h>
#include <qpoint.h>

class CQPoint {
    QPoint point;
public:
    CQPoint() {}
    CQPoint(const QPoint &p) { *this = p; }
    CQPoint(const QPoint *p) { *this = p; }
    QPoint &operator =(const QPoint &p) { point = p; return point; }
    QPoint &operator =(const QPoint *p) { if(p) point = *p; return point; }
    operator void *() { return new QPoint(point); }
    operator QPoint &() { return point; }
};

typedef CQPoint MQPoint;

#endif  // PQPOINT_H
