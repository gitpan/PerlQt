#ifndef PQFONTINF_H
#define PQFONTINF_H

/*
 * Definition of the CQFontInfo class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqt.h>
#include <qfontinf.h>

class CQFontInfo {
    QFontInfo *fontinfo;
public:
    CQFontInfo() { fontinfo = new QFontInfo(QFont()); }
    CQFontInfo(const QFontInfo &i) {
	fontinfo = new QFontInfo(QFont());
	*this = i;
    }
    CQFontInfo(const QFontInfo *i) {
	fontinfo = new QFontInfo(QFont());
	*this = i;
    }
    CQFontInfo(const QFont &f) {
	fontinfo = new QFontInfo(QFont());
	*this = f;
    }
    CQFontInfo(const QFont *f) {
	fontinfo = new QFontInfo(QFont());
	*this = f;
    }
    ~CQFontInfo() { delete fontinfo; }
    QFontInfo &operator =(const QFontInfo &i) {
	delete fontinfo;
	fontinfo = new QFontInfo(i);
	return *fontinfo;
    }
    QFontInfo &operator =(const QFontInfo *i) {
	delete fontinfo;
	fontinfo = i ? new QFontInfo(*i) : new QFontInfo(QFont());
	return *fontinfo;
    }
    QFontInfo &operator =(const QFont &f) {
	delete fontinfo;
	fontinfo = new QFontInfo(f);
	return *fontinfo;
    }
    QFontInfo &operator =(const QFont *f) {
	delete fontinfo;
	fontinfo = new QFontInfo(f ? *f : QFont());
	return *fontinfo;
    }
    operator void *() { return new QFontInfo(*fontinfo); }
    operator QFontInfo &() { return *fontinfo; }
};

typedef CQFontInfo MQFontInfo;

#endif  // PQFONTINF_H
