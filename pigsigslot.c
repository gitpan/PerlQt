/*
 * Wrapper file for the file generated by SigSlot.pm through gensigslot
 *
 * Copyright (C) 1999, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README.LICENSE file which should be included with this library.
 *
 */

#include "pig.h"
#include "pigtype_base.h"
#include "pigtype_object.h"
#include "pigtype_qt.h"
#include <qobject.h>
#include <qmetaobj.h>
#include "pigsigslot.h"
#include "pigperl.h"

QObject *pig_signal_object;
QMember *pig_signal_member;

typedef void (*pig_signal)();

#define pig_func (*((PIG)pig_signal_member))

void pigslot(class pig_S *);

pig_S::pig_S() {

}

pig_S::~pig_S() {
    SvFLAGS(pigsd->pigreceiver) = (SvFLAGS(pigsd->pigreceiver) & ~SVTYPEMASK) | SVt_NULL;
    SvREFCNT_dec(pigsd->pigreceiver);
    delete pigsd;
}

const char *pig_S::className() const {
    return HvNAME(SvSTASH(SvRV(pigsd->pigreceiver)));
}

QMetaObject *pig_S::metaObject() const {
    return pigsd->pigmeta;
}

void pig_S::pig_S_destroyed() {
printf("Thi wasn't very successful\n");
    delete this;
}

#include "_pigsigslot.c"
