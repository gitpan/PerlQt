/*
 * PerlQt interface to qsocknot.h
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "psocknot.h"
#include "penum.h"

#define STORE_key(key) enumIV(hv, MSTR(key), QSocketNotifier::key)

inline void init_enum() {
    HV *hv = perl_get_hv("QSocketNotifier::Type", TRUE | GV_ADDMULTI);

    STORE_key(Read);
    STORE_key(Write);
    STORE_key(Exception);
}

MODULE = QSocketNotifier	PACKAGE = QSocketNotifier

PROTOTYPES: DISABLE

BOOT:
    init_enum();

PSocketNotifier *
PSocketNotifier::new(socket, type, parent = 0, name = 0)
    int socket
    QSocketNotifier::Type type
    QObject *parent
    char *name

void
QSocketNotifier::DESTROY()
    CODE:
    if(want_destroy(ST(0)))
        delete THIS;

bool
QSocketNotifier::isEnabled()

void
QSocketNotifier::setEnabled(enable)
    bool enable

int
QSocketNotifier::socket()

QSocketNotifier::Type
QSocketNotifier::type()
