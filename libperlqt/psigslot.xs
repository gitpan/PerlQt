/*
 * pQtSigSlot definition
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "psigslot.h"

void pQtSigSlot::initMetaObject() {
    char *clname = (char *)qobj->className();
    SV **svp = hv_fetch(MetaObjects, clname, strlen(clname), 0);

    if(svp && SvTRUE(*svp)) return;
    if(!qobj->metaObject()) qobj->virtual_initMetaObject();  // Paranoia?
    safe_hv_store(MetaObjects, clname, newSViv((IV)qobj->metaObject()));
}

const char *pQtSigSlot::className() const {
    return qobj->className();
}

QMetaObject *pQtSigSlot::metaObject() const {
    return qobj->metaObject();
}
/*
SV *getMemberArgs(char *member) {
    dSP;
    int count;
    SV *ret;

    ENTER;		// This can be called in the global Perl scope
    SAVETMPS;

    PUSHMARK(sp);
    XPUSHs(sv_2mortal(newSVpv(member, 0)));
    PUTBACK;

    count = perl_call_pv("QObject::getMemberArgs", G_SCALAR);
    SPAGAIN;
    if(count != 1) croak("Bad perl_call_pv, bad");
    ret = newSVsv(POPs);
    PUTBACK;

    FREETMPS;
    LEAVE;

    return ret;
}
*/

QMember stub_func(char *member) {
    char len = *member;
//    printf("len = %d\n", len);
    if(len == 0) return (QMember)&pQtSigSlot::s;
    if(len == 1) return (QMember)&pQtSigSlot::sI;
    if(len == 2) return (QMember)&pQtSigSlot::sII;
}

/*
QMember stub_func(char *member) {
    SV *rv = getMemberArgs(member);
    AV *args = (AV *)rv_check(rv);
    int len = av_len(args)+1;

    if(len == 0) return (QMember)&pQtSigSlot::s;
    if(len == 1) return (QMember)&pQtSigSlot::sI;
    else if(len == 2) return (QMember)&pQtSigSlot::sII;
    SvREFCNT_dec(args);  // test
    SvREFCNT_dec(rv);
}
*/

void pQtSigSlot::gimmie_iv(IV i) {
//    printf("dSP;\n");
    dSP;
//    printf("ret = NULL\n");
    SV *ret = NULL;
    while(!ret) {
//	printf("switch\n");
	switch(*ptr) {
	case 0:
	    break;
	case 1:
//	printf("a 1\n");
	    ptr++;
	    ret = objectify_ptr((void *)i, ptr+1);
	    ptr += *ptr;
	    break;
	case 2:
//	printf("a 2\n");
	    ret = newSViv(i);
	    break;
	case 3:
//	printf("a 3\n");
	    if(sizeof(int) == sizeof(float)) {
		union { int i; float f; } n;
		n.i = i;
		ret = newSVnv(n.f);
	    } else {
		warn("sizeof(int) != sizeof(float) in slot");
		XPUSHs(&sv_undef);
		PUTBACK;
		return;
	    }
	    break;
//	case 4:   // This is a double
	case 5:
//	printf("a 5\n");
	    XPUSHs(boolSV(i));
	    PUTBACK;
	    return;
	case 6:
//	printf("a 6\n");
	    ret = newSVpv((char *)i, 0);
	    break;
	case 8:
	case 9:    // no checking for now
	case 10:
	case 11:
//	printf("a 11\n");
	    XPUSHs((SV *)i);
	    PUTBACK;
	    return;
	case 12:
//	printf("a 12\n");
	    AV *av = (AV *)i;
	    I32 len = av_len(av);
	    SV **elem;
	    for(int k = 0; k <= len; k++) {
		elem = av_fetch(av, k, 0);
		if(elem) XPUSHs(*elem);
	    }
	    PUTBACK;
	    return;
	}
	ptr++;
    }
//    printf("pushs\n");
    XPUSHs(sv_2mortal(ret));
    PUTBACK;
}

void pQtSigSlot::s() {
//    printf("WHOOPIE!\n");
    dSP;
    GV *meth = gv_fetchmethod(SvSTASH(SvRV(object)), sname);

    ENTER;
    SAVETMPS;

    PUSHMARK(sp);
    XPUSHs(object);
    PUTBACK;

    perl_call_sv((SV *)GvCV(meth), G_DISCARD);

    FREETMPS;
    LEAVE;
}

char *proto_args(char *proto) {
    return 1 + proto[1] + proto;  // proto + *++proto
}

void pQtSigSlot::sI(IV i) {
    dSP;
    GV *meth = gv_fetchmethod(SvSTASH(SvRV(object)), sname);

    ENTER;
    SAVETMPS;
    
    PUSHMARK(sp);
    XPUSHs(object);
    PUTBACK;  // stack was modified...
    ptr = proto_args(proto);
    gimmie_iv(i);
    SPAGAIN;  // stack was modified...

    perl_call_sv((SV *)GvCV(meth), G_DISCARD);

    FREETMPS;
    LEAVE;
}

void pQtSigSlot::sII(IV i1, IV i2) {
    dSP;
    GV *meth = gv_fetchmethod(SvSTASH(SvRV(object)), sname);

    ENTER;
    SAVETMPS;
    
    PUSHMARK(sp);
    XPUSHs(object);
    PUTBACK;  // stack was modified...
    ptr = proto_args(proto);
    gimmie_iv(i1);
    gimmie_iv(i2);
    SPAGAIN;  // stack was modified...

    perl_call_sv((SV *)GvCV(meth), G_DISCARD);

    FREETMPS;
    LEAVE;
}

/*
void pQtSigSlot::sI(IV i) {
    ptr = proto_args(proto);
//    SV *sv = gimmie_iv(i); //newSViv(i);

    slot1(sv);
    SvREFCNT_dec(sv);
}

void pQtSigSlot::sII(IV i1, IV i2) {
    SV *sv1 = newSViv(i1), *sv2 = newSViv(i2);

    slot2(sv1, sv2);

    SvREFCNT_dec(sv1);
    SvREFCNT_dec(sv2);
}

void pQtSigSlot::slot1(SV *sv1) {
    dSP;
    GV *meth = gv_fetchmethod(SvSTASH(SvRV(object)), sname);

    ENTER;
    SAVETMPS;

//    if(SvREFCNT(sv1)) sv1);	// scope it here

    PUSHMARK(sp);
    XPUSHs(object);
    XPUSHs(sv1);
    PUTBACK;

    perl_call_sv((SV *)GvCV(meth), G_DISCARD);

    FREETMPS;
    LEAVE;
}

void pQtSigSlot::slot2(SV *sv1, SV *sv2) {
    dSP;
    GV *meth = gv_fetchmethod(SvSTASH(SvRV(object)), sname);

    ENTER;
    SAVETMPS;

//    if(SvREFCNT(sv1)) sv_2mortal(sv1);	// scope it here
//    if(SvREFCNT(sv2)) sv_2mortal(sv2);

    PUSHMARK(sp);
    XPUSHs(object);
    XPUSHs(sv1);
    XPUSHs(sv2);
    PUTBACK;

    perl_call_sv((SV *)GvCV(meth), G_DISCARD);

    FREETMPS;
    LEAVE;
}
*/