#ifndef PQCOLGRP_H
#define PQCOLGRP_H

/*
 * Definition of the CQColorGroup class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqt.h>
#include <qpalette.h>

class CQColorGroup {
    QColorGroup colorgroup;
public:
    CQColorGroup() {}
    CQColorGroup(const QColorGroup &cg) { *this = cg; }
    CQColorGroup(const QColorGroup *cg) { *this = cg; }
    QColorGroup &operator =(const QColorGroup &cg) {
	colorgroup = cg;
	return colorgroup;
    }
    QColorGroup &operator =(const QColorGroup *cg) {
	if(cg) colorgroup = *cg;
	return colorgroup;
    }
    operator void *() { return new QColorGroup(colorgroup); }
    operator QColorGroup &() { return colorgroup; }
};

typedef CQColorGroup MQColorGroup;

#endif  // PQCOLGRP_H
