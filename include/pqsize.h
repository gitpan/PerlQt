#ifndef PQSIZE_H
#define PQSIZE_H

/*
 * Definition of the CQSize class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqt.h>
#include <qsize.h>

class CQSize {
    QSize size;
public:
    CQSize() {}
    CQSize(const QSize &s) { *this = s; }
    CQSize(const QSize *s) { *this = s; }
    QSize &operator =(const QSize &s) { size = s; return size; }
    QSize &operator =(const QSize *s) { if(s) size = *s; return size; }
    operator void *() { return new QSize(size); }
    operator QSize &() { return size; }
};

typedef CQSize MQSize;

#endif  // PQSIZE_H
