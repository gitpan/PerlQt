#ifndef PQFONT_H
#define PQFONT_H

/*
 * Definition of the CQFont class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqt.h>
#include <qfont.h>

class CQFont {
    QFont font;
public:
    CQFont() {}
    CQFont(const QFont &f) { *this = f; }
    CQFont(const QFont *f) { *this = f; }
    QFont &operator =(const QFont &f) { font = f; return font; }
    QFont &operator =(const QFont *f) { if(f) font = *f; return font; }
    operator void *() { return new QFont(font); }
    operator QFont &() { return font; }
};

typedef CQFont MQFont;

#endif  // PQFONT_H
