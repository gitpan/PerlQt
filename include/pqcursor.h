#ifndef PQCURSOR_H
#define PQCURSOR_H

/*
 * Definition of the CQCursor class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqt.h>
#include <qcursor.h>

class CQCursor {
    QCursor cursor;
public:
    CQCursor() {}
    CQCursor(const QCursor &c) { *this = c; }
    CQCursor(const QCursor *c) { *this = c; }
    QCursor &operator =(const QCursor &c) { cursor = c; return cursor; }
    QCursor &operator =(const QCursor *c) { if(c) cursor = *c; return cursor; }
    operator void *() { return new QCursor(cursor); }
    operator QCursor &() { return cursor; }
};

typedef CQCursor MQCursor;

#endif  // PQCURSOR_H
