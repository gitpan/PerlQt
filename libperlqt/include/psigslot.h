#ifndef PSIGSLOT_H
#define PSIGSLOT_H

/*
 * Declaration of the pQtSigSlot class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qmetaobj.h"
#include "pobject.h"
#include "pqt.h"

class pQtSigSlot : public QObject {
    SV *object;
    pObject *qobj;
    char *sname;
    char *ptr;           // semi-static pointer to proto
    char *proto;
protected:
    void initMetaObject();
public:
    pQtSigSlot(SV *obj, char *type, STRLEN tlen);
    ~pQtSigSlot();
    QMetaObject *metaObject() const;
    const char *className() const;
    void s();
    void sI(IV);
    void sII(IV, IV);
//    void sIII(IV, IV, IV);
    void gimmie_iv(IV);
};

QMember stub_func(char *member);

extern HV *Protos;
extern HV *Signals;
extern HV *Slots;
extern HV *MetaObjects;


#endif  // PSIGSLOT_H
