#ifndef PQFONTMET_H
#define PQFONTMET_H

/*
 * Definition of the CQFontMetrics class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqt.h>
#include <qfontmet.h>

class CQFontMetrics {
    QFontMetrics *fontmetrics;
public:
    CQFontMetrics() { fontmetrics = new QFontMetrics(QFont()); }
    CQFontMetrics(const QFontMetrics &m) {
	fontmetrics = new QFontMetrics(QFont());
	*this = m;
    }
    CQFontMetrics(const QFontMetrics *m) {
	fontmetrics = new QFontMetrics(QFont());
	*this = m;
    }
    CQFontMetrics(const QFont &f) {
	fontmetrics = new QFontMetrics(QFont());
	*this = f;
    }
    CQFontMetrics(const QFont *f) {
	fontmetrics = new QFontMetrics(QFont());
	*this = f;
    }
    ~CQFontMetrics() { delete fontmetrics; }
    QFontMetrics &operator =(const QFontMetrics &m) {
	delete fontmetrics;
	fontmetrics = new QFontMetrics(m);
	return *fontmetrics;
    }
    QFontMetrics &operator =(const QFontMetrics *m) {
	delete fontmetrics;
	fontmetrics = m ? new QFontMetrics(*m) : new QFontMetrics(QFont());
	return *fontmetrics;
    }
    QFontMetrics &operator =(const QFont &f) {
	delete fontmetrics;
	fontmetrics = new QFontMetrics(f);
	return *fontmetrics;
    }
    QFontMetrics &operator =(const QFont *f) {
	delete fontmetrics;
	fontmetrics = new QFontMetrics(f ? *f : QFont());
	return *fontmetrics;
    }
    operator void *() { return new QFontMetrics(*fontmetrics); }
    operator QFontMetrics &() { return *fontmetrics; }
};

typedef CQFontMetrics MQFontMetrics;

#endif  // PQFONTINF_H
