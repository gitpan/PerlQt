#ifndef PSIGSLOT_H
#define PSIGSLOT_H

/*
 * PerlQt Signals and Slots.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqt.h>

void sigslot(const QObject *, const char **, const QObject **,
	     const char **, const char *);
void sigslot(const QObject *, const char **, const QObject *,
	     const char **, const char *);
const char *sigslot(const QObject *, const char *, const char *);

#endif  // PSIGSLOT_H
