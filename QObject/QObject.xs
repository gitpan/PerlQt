/*
 * PerlQt interface to qobject.h
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qmetaobj.h"
#include "pobject.h"
#include "psigslot.h"

#if !defined(Q_MOC_CONNECTIONLIST_DECLARED)
#define Q_MOC_CONNECTIONLIST_DECLARED
#include <qlist.h>
#if defined(Q_DECLARE)
Q_DECLARE(QListM,QConnection);
Q_DECLARE(QListIteratorM,QConnection);
#else
// for compatibility with old header files
declare(QListM,QConnection);
declare(QListIteratorM,QConnection);
#endif
#endif

void activate(QObject *self, const char *signal) {
    QConnectionList *clist = ((pObject *)self)->protected_receivers(signal);
    if(!clist || self->signalsBlocked()) return;
    typedef void (QObject::*RT)();
    typedef RT *PRT;
    RT r;

    QConnectionListIt it(*clist);
    QConnection *c;
    QSenderObject *object;
    while((c=it.current())) {
	++it;
	object = (QSenderObject*)c->object();
	object->setSender(self);
	r = *((PRT)(c->member()));
	(object->*r)();
    }
}

void activateI(QObject *self, const char *signal, IV t0) {
    QConnectionList *clist = ((pObject *)self)->protected_receivers(signal);
    if(!clist || self->signalsBlocked()) return;
    typedef void (QObject::*RT0)();
    typedef RT0 *PRT0;
    typedef void (QObject::*RT1)(IV);
    typedef RT1 *PRT1;
    RT0 r0;
    RT1 r1;

    QConnectionListIt it(*clist);
    QConnection *c;
    QSenderObject *object;
    while((c=it.current())) {
	++it;
	object = (QSenderObject*)c->object();
	object->setSender(self);
	if(c->numArgs()) {
	    r1 = *((PRT1)(c->member()));
	    (object->*r1)(t0);
	} else {
	    r0 = *((PRT0)(c->member()));
	    (object->*r0)();
	}
    }
}

void activateII(QObject *self, const char *signal, IV t0, IV t1) {
    QConnectionList *clist = ((pObject *)self)->protected_receivers(signal);
    if(!clist || self->signalsBlocked()) return;
    typedef void (QObject::*RT0)();
    typedef RT0 *PRT0;
    typedef void (QObject::*RT1)(IV);
    typedef RT1 *PRT1;
    typedef void (QObject::*RT2)(IV, IV);
    typedef RT2 *PRT2;
    RT0 r0;
    RT1 r1;
    RT2 r2;

    QConnectionListIt it(*clist);
    QConnection *c;
    QSenderObject *object;
    while((c=it.current())) {
	++it;
	object = (QSenderObject*)c->object();
	object->setSender(self);
	switch(c->numArgs()) {
	    case 0:
		r0 = *((PRT0)(c->member()));
		(object->*r0)();
		break;
	    case 1:
		r1 = *((PRT1)(c->member()));
		(object->*r1)(t0);
		break;
	    case 2:
		r2 = *((PRT2)(c->member()));
		(object->*r2)(t0, t1);
		break;
	}
    }
}

IV gimmie_iv(SV *sv, char **proto) {
    bool fin = FALSE;
    IV ret;

    while(!fin) {
	fin = TRUE;
	switch(**proto) {
	case 0:				// const
	    fin = FALSE;
	    break;   // ignore const
	case 1:				// object
	    (*proto)++;
	    ret = (IV)extract_ptr(sv, (*proto)+1);
	    *proto += **proto;
	    break;
	case 2:				// int
	    ret = SvIV(sv);
	    break;
	case 3:				// float
	    if(sizeof(int) == sizeof(float)) {
		union { int i; float f; } n;
		n.f = SvNV(sv);
		ret = (IV)n.i;
	    } else {
		warn("sizeof(int) != sizeof(float) in signal");
		ret = (IV)-1;
	    }
	    break;
//	case 4:  // this is a double
	case 5:				// bool
	    ret = SvTRUE(sv) ? TRUE : FALSE;
	    break;
	case 6:				// string
	    ret = (IV)SvPV(sv, na);
//	    printf("str = %p\n", (char *)ret);
	    break;
	case 8:
	case 9:
	case 10:
	case 11:
	    ret = (IV)sv;
	    break;
	}
	(*proto)++;
    }
    return ret;
}

XS(perl_emit_signal) {
    dXSARGS;
    char *sname = HvNAME(GvSTASH(CvGV(cv)));
    char *fname = GvNAME(CvGV(cv));
    char *proto;
    SV **svp = hv_fetch(Signals, sname, strlen(sname), 0);
    if(!svp) {
	warn("Not a signal!\n");
	return;
    }
    svp = hv_fetch((HV *)rv_check(*svp), fname, strlen(fname), 0);
    if(!svp) {
	warn("Not a signal!\n");
	return;
    }
    STRLEN plen;
    char *p = SvPV(*svp, plen);
    proto = SvPV(unproto(*svp), na);
//    printf("proto = %s\n", proto);

    PObject *obj = (PObject *)pextract(QObject, 0);

    int argcnt = *p;
    p = 1 + p[1] + p;
    if(argcnt == 0)
	activate(obj, proto);
    else if(argcnt == 1) {
//	printf("argcnt == 1\n");
	IV i1 = gimmie_iv(ST(1), &p);
//	printf("IV = %#x\n", i1);
	activateI(obj, proto, i1);
    } else if(argcnt == 2) {
//	printf("argcnt == 2\n");
	IV i1 = gimmie_iv(ST(1), &p);
	IV i2 = gimmie_iv(ST(2), &p);
	activateII(obj, proto, i1, i2);
    }
/*
    if(items == 1)
	activate(obj, proto);
    else if(items > 1) {
	if(SvIOK(ST(1)))
	    activateI(obj, proto, SvIV(ST(1)));
	else if(SvPOK(ST(1)))
	    activateI(obj, proto, (IV)SvPV(ST(1), na));
    }*/
}

MODULE = QObject		PACKAGE = signals

void
addSignal(name)
    char *name
    CODE:
    newXS(name, perl_emit_signal, __FILE__);

MODULE = QObject		PACKAGE = QObject

PROTOTYPES: DISABLE

BOOT:
    MetaObjects = newHV();
//    Protos = newHV();
    Protos = perl_get_hv("QObject::Protos", TRUE);
    Signals = perl_get_hv("signals::signals", TRUE);
    Slots = perl_get_hv("slots::slots", TRUE);
    SvREFCNT_inc((SV *)Signals);
    SvREFCNT_inc((SV *)Slots);

PObject *
PObject::new(parent=0, name=0)
    QObject *parent
    char *name

void
QObject::DESTROY()
    CODE:
    if(want_destroy(ST(0)))
	delete THIS;

void
QObject::refcnt()
    CODE:
    printf("qobject refcnt %p: %d %d\n", THIS, SvREFCNT(ST(0)), SvREFCNT(obj_check(ST(0))));

void
QObject::blockSignals(b)
    bool b

const char *
QObject::className()

bool
connect(...)
    PREINIT:
    if(items < 4)
        croak("Usage: QObject::connect(sender, signal, receiver, member);\nUsage: $receiver->connect(sender, signal, member);");
    bool virtual_call = sv_isobject(ST(1));
    QObject *receiver = pextract(QObject, virtual_call ? 0 : 2);
    QObject *sender = pextract(QObject, virtual_call ? 1 : 0);
//    SV *si = parse_member(ST(virtual_call ? 2 : 1));
//    SV *m = parse_member(ST(3));
//    SV *si = unproto(proto(ST(virtual_call ? 2 : 1)));
//    SV *m = unproto(proto(ST(3)));
//    printf("'%s'; '%s'\n", SvPV(si, na), SvPV(m, na));

    SV *sproto = proto(ST(virtual_call ? 2 : 1));
    SV *mproto = proto(ST(3));
//    STRLEN slen;
//    char *stype = SvPV(sproto, slen);
    STRLEN mlen;
    char *mtype = SvPV(mproto, mlen);

    SV *sp = unproto(sproto);
    SV *mp = unproto(mproto);

    char *signal = SvPV(sp, na);
    char *member = SvPV(mp, na);

    SV *sig = sv_2mortal(newSViv(SIGNAL_CODE));		// Emulate SIGNAL()
    SV *memb = sv_newmortal();

    char *s = find_signal(ST(virtual_call ? 0 : 2), member);  // FIX ME
    sv_setiv(memb, s ? SIGNAL_CODE : SLOT_CODE);
    if(s) {
//	receiver = new pQtSigSlot(ST(virtual_call ? 0 : 2), s);
	receiver = new pQtSigSlot(ST(virtual_call ? 0 : 2), mtype, mlen);
    }
    else {
	s = find_slot(ST(virtual_call ? 0 : 2), member);  // FIX ME
	if(s) receiver = new pQtSigSlot(ST(virtual_call ? 0 : 2), mtype, mlen);
    }
    CODE:
    sv_catpv(sig, signal);
    sv_catpv(memb, member);
//    printf("'%s'; '%s'\n", SvPV(sig, na), SvPV(memb, na));
    RETVAL = receiver->connect(sender, SvPV(sig, na), SvPV(memb, na));
    OUTPUT:
    RETVAL

bool
disconnect(...)
    CASE: items > 1 && sv_isobject(ST(1))
	PREINIT:
	QObject *sender   = pextract(QObject, 0);
	QObject *receiver = pextract(QObject, 1);
	pChar *member = (items > 2 && SvOK(ST(2))) ? SvPV(ST(2), na) : 0;
	SV *memb;
	CODE:
	if(member) {
	    memb = sv_2mortal(newSViv(find_signal(ST(1), member) ?
		SIGNAL_CODE : SLOT_CODE));
	    sv_catpv(memb, member);
	    member = SvPVX(memb);
	}
	RETVAL = sender->disconnect(receiver, member);
	OUTPUT:
	RETVAL
    CASE: items > 1
	PREINIT:
	QObject *sender = pextract(QObject, 0);
	pChar *signal = (items > 1 && SvOK(ST(3))) ? SvPV(ST(1), na) : 0;
	pObject *receiver = (items > 2) ? pextract(pObject, 2) : 0;
	pChar *member = (items > 3 && SvOK(ST(3))) ? SvPV(ST(3), na) : 0;
	SV *sv;
	CODE:
	if(signal) {
	    sv = sv_2mortal(newSViv(SIGNAL_CODE));
	    sv_catpv(sv, signal);
	    signal = SvPVX(sv);
	}
	if(member) {
	    sv = sv_2mortal(newSViv(find_signal(ST(2), member) ?
		SIGNAL_CODE : SLOT_CODE));
	    sv_catpv(sv, member);
	    member = SvPVX(sv);
	}
	RETVAL = sender->disconnect(signal, receiver, member);
	OUTPUT:
	RETVAL
    CASE:
	CODE:
	croak("Usage: $sender->disconnect(signal = undef, receiver = undef, member = undef);\nUsage: $sender->disconnect(receiver, member = undef);");

void
QObject::dumpObjectInfo()

void
QObject::dumpObjectTree()

bool
QObject::event(event)
    QEvent *event

bool
QObject::eventFilter(obj, event)
    QObject *obj
    QEvent *event

bool
QObject::highPriority()

bool
QObject::inherits(classname)
    char *classname

void
QObject::insertChild(obj)
    QObject *obj

void
QObject::installEventFilter(obj)
    QObject *obj

bool
QObject::isA(classname)
    char *classname

bool
QObject::isWidgetType()

void
QObject::killTimer(id)
    int id

void
QObject::killTimers()

const char *
QObject::name()

QObject *
QObject::parent()

void
QObject::removeChild(obj)
    QObject *obj

void
QObject::removeEventFilter(obj)
    QObject *obj

void
QObject::setName(name)
    char *name

bool
QObject::signalsBlocked()

int
QObject::startTimer(interval)
    int interval

MODULE = QObject	PACKAGE = QObject	PREFIX = virtual_

void
pObject::virtual_timerEvent(event)
    QTimerEvent *event
