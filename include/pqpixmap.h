#ifndef PQPIXMAP_H
#define PQPIXMAP_H

/*
 * Definition of the CQPixmap class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqt.h>
#include <qpixmap.h>

class CQPixmap {
    QPixmap pixmap;
public:
    CQPixmap() {}
    CQPixmap(const QPixmap &pm) { *this = pm; }
    CQPixmap(const QPixmap *pm) { *this = pm; }
    QPixmap &operator =(const QPixmap &pm) { pixmap = pm; return pixmap; }
    QPixmap &operator =(const QPixmap *pm) {
	if(pm) pixmap = *pm;
	return pixmap;
    }
    operator void *() { return new QPixmap(pixmap); }
    operator QPixmap &() { return pixmap; }
};

typedef CQPixmap MQPixmap;

#endif  // PQPIXMAP_H
