/*
 * PObject definitions and sig/slot implementation.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pobject.h"
#include "psigslot.h"

HV *Signals = NULL;
HV *Slots = NULL;
HV *MetaObjects = NULL;

char *getPerlSuperClass(char *clname) {
    dSP;
    int count;
    SV *ret;

    PUSHMARK(sp);
    XPUSHs(sv_2mortal(newSVpv(clname, 0)));
    PUTBACK;

    count = perl_call_pv("QObject::find_superclass", G_SCALAR);
    SPAGAIN;
    if(count != 1) croak("Bad perl_call_pv, bad");
    ret = POPs;
    PUTBACK;

    return SvTRUE(ret) ? SvPV(ret, na) : 0;
}

QMetaData *initMetaData(HV *hv) {
    if(!hv || HvKEYS(hv) < 1) return NULL;
    int keys = HvKEYS(hv);
    QMetaData *tbl = new QMetaData[keys];

    SV *value;
    char *key;
    I32 klen;

    hv_iterinit(hv);
    for(int i = 0; i < keys; i++) {
	value = hv_iternextsv(hv, &key, &klen);
	SvREFCNT_inc(value);
	tbl[i].name = SvPV(value, na);
	tbl[i].ptr = stub_func(tbl[i].name);
    }

    return tbl;
}

QMetaObject *metaObjectSetup(char *clname) {
    int cllen = strlen(clname);
    if(hv_exists(MetaObjects, clname, cllen)) {
	SV **ret = hv_fetch(MetaObjects, clname, cllen, 0);
	if(ret) {
	    QMetaObject *obj = (QMetaObject *)SvIV(*ret);
	    return (QMetaObject *)SvIV(*ret);
	}
	return NULL;
    }

    SV **svp;
    HV *slothv = NULL, *signalhv = NULL; //, *metaData = newHV();
    int slot_keys = 0, signal_keys = 0;
    QMetaData *slot_tbl = NULL, *signal_tbl = NULL;
    QMetaObject *metaObj;
    char *superclass;

    char *s = getPerlSuperClass(clname);
    if(!s) croak("Class '%s' is not derived from QObject\n", clname);

    superclass = (char *)malloc(strlen(s)+1);
    strcpy(superclass, s);

    svp = hv_fetch(Signals, clname, cllen, 0);
    if(svp) {
	signalhv = (HV *)rv_check(*svp);
	signal_keys = HvKEYS(signalhv) > 0 ? HvKEYS(signalhv) : 0;
    }
    svp = hv_fetch(Slots, clname, cllen, 0);
    if(svp) {
	slothv = (HV *)rv_check(*svp);
	slot_keys = HvKEYS(slothv) > 0 ? HvKEYS(slothv) : 0;
    }

    slot_tbl = initMetaData(slothv);
    signal_tbl = initMetaData(signalhv);
    metaObj = new QMetaObject(clname, superclass,
	slot_tbl, slot_keys,
	signal_tbl, signal_keys);
    safe_hv_store(MetaObjects, clname, newSViv((IV)metaObj));
    return metaObj;
}

const char *PObject::className() const {
    return PObject_className();
}

bool PObject::event(QEvent *event) {
    bool ret = PObject_event(event);
    if(pfailed) ret = QObject::event(event);
    return ret;
}

bool PObject::eventFilter(QObject *obj, QEvent *event) {
    bool ret = PObject_eventFilter(obj, event);
    if(pfailed) ret = QObject::eventFilter(obj, event);
    return ret;
}

QMetaObject *PObject::metaObject() const {
    QMetaObject *ret = PObject_metaObject();
    if(pfailed) ret = QObject::metaObject();
    return ret;
}

void PObject::initMetaObject() {
    if(!QObject::metaObject()) QObject::initMetaObject();
    PObject_initMetaObject();
}

void PObject::timerEvent(QTimerEvent *event) {
    PObject_timerEvent(event);
    if(pfailed) QObject::timerEvent(event);
}


const char *PObject_virtualize::PObject_className() const {
    return getQtClassName();
}

bool PObject_virtualize::PObject_event(QEvent *event) {
    SV *r = retCallObj("event", event, "QEvent");
    if(pfailed) return FALSE;
    bool ret = SvTRUE(r) ? TRUE : FALSE;
    SvREFCNT_dec(r);
    return ret;
}

bool PObject_virtualize::PObject_eventFilter(QObject *obj, QEvent *event) {
    SV *r = retCallObj("eventFilter", obj, "QObject", event, "QEvent");
    if(pfailed) return FALSE;
    bool ret = SvTRUE(r) ? TRUE : FALSE;
    SvREFCNT_dec(r);
    return ret;
}

void PObject_virtualize::PObject_initMetaObject() {
    char *clname = (char *)getQtClassName();
    SV **svp = hv_fetch(MetaObjects, clname, strlen(clname), 1);

    if(svp && SvTRUE(*svp)) return;
    safe_hv_store(MetaObjects, clname, newSViv(0));
}

QMetaObject *PObject_virtualize::PObject_metaObject() const {
    pfailed = FALSE;
    char *clname = (char *)getQtClassName();
    if(!hv_exists(Signals, clname, strlen(clname)) &&
       !hv_exists(Slots, clname, strlen(clname))) {
	pfailed = TRUE;
	return NULL;
    }
    return metaObjectSetup(clname);
}

void PObject_virtualize::PObject_timerEvent(QTimerEvent *event) {
    voidCallObj("timerEvent", event, "QTimerEvent");
}
