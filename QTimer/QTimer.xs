/*
 * PerlQt interface to qtimer.h
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "ptimer.h"
#include "pobject.h"
#include "psigslot.h"

MODULE = QTimer		PACKAGE = QTimer

PROTOTYPES: DISABLE

PTimer *
PTimer::new(parent = 0, name = 0)
    pObject *parent
    char *name

void
QTimer::changeInterval(msec)
    int msec

bool
QTimer::isActive()

void
singleShot(msec, receiver, member)
    int msec
    QObject *receiver
    CODE:
    SV *mproto = proto(ST(3));
    STRLEN mlen;
    char *mtype = SvPV(mproto, mlen);

    SV *mp = unproto(mproto);
    char *member = SvPV(mp, na);

    char *s = find_signal(ST(1), member);
    SV *memb = newSViv(s ? SIGNAL_CODE : SLOT_CODE);
    sv_catpv(memb, member);
    if(s) receiver = new pQtSigSlot(ST(1), mtype, mlen);
    else {
        s = find_slot(ST(1), member);
        if(s) receiver = new pQtSigSlot(ST(1), mtype, mlen);
    }
    QTimer::singleShot(msec, receiver, member);

int
QTimer::start(msec, sshot = FALSE)
    int msec
    bool sshot

void
QTimer::stop()
