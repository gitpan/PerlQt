#ifndef PQPALETTE_H
#define PQPALETTE_H

/*
 * Definition of the CQPalette class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqt.h>
#include <qpalette.h>

class CQPalette {
    QPalette palette;
public:
    CQPalette() {}
    CQPalette(const QPalette &p) { *this = p; }
    CQPalette(const QPalette *p) { *this = p; }
    QPalette &operator =(const QPalette &p) { palette = p; return palette; }
    QPalette &operator =(const QPalette *p) {
	if(p) palette = *p;
	return palette;
    }
    operator void *() { return new QPalette(palette); }
    operator QPalette &() { return palette; }
};

typedef CQPalette MQPalette;

#endif  // PQPALETTE_H
