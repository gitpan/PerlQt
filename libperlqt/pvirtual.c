/*
 * virtualize definition
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pvirtual.h"

int pfailed = FALSE;

virtualize::~virtualize() {
//    warn("~virtualize()\n");
    if(qtClassName) free(qtClassName);
//    if(qtObject && SvREFCNT(qtObject)) SvREFCNT_dec(qtObject);
    if(qtObject) {
//	warn("SvROK_off\n");
//	SvROK_off(qtObject);     // cross fingers
	HV *obj = (HV *)obj_check(qtObject);  // I hope qtObject is still valid
	safe_hv_store(obj, "DELETE", &sv_no);    // Do not delete again
	safe_hv_store(obj, "DELETED", &sv_yes);  // Do not attempt to use me
	SvFLAGS(qtObject) = (SvFLAGS(qtObject) & ~SVTYPEMASK) | SVt_NULL;
//	warn("SvREFCNT_dec %d\n", SvTYPE(qtObject));
	SvREFCNT_dec(qtObject);		// Only the reference, not the object
//	warn("shit\n");
    }
}

void virtualize::setQtObject(SV *obj) {
//    qtObject = newSVsv(obj); //SvREFCNT_inc(obj);
//    SvREFCNT_dec(obj_check(obj));
//printf("setQtObject refcnt of %p: %d %d\n", obj_check(obj), SvREFCNT(obj), SvREFCNT(obj_check(obj)));
    qtObject = newRV_noinc(obj_check(obj));
}

void virtualize::callQtMethod(CV *method, SV *arg1, SV *arg2, SV *arg3,
			      SV *arg4) const {
    dSP;
//    dXSARGS;

    ENTER;
    SAVETMPS;

    PUSHMARK(sp);
    XPUSHs(qtObject);
    if(arg1) XPUSHs(arg1);
    if(arg2) XPUSHs(arg2);
    if(arg3) XPUSHs(arg3);
    if(arg4) XPUSHs(arg4);
    PUTBACK;

//    warn("perl_call_sv\n");
    int i = perl_call_sv((SV *)method, G_SCALAR);
    if(i < 1) croak("perl_call_sv croaked\n");
//    SPAGAIN;

//    warn("ST(0) is currently %p\n", ST(0));

//    FREETMPS;
//    LEAVE;
}

void virtualize::voidCall(char *methodName, SV *arg1, SV *arg2, SV *arg3,
                          SV *arg4) const {
    pfailed = FALSE;
//    printf("obj_checking this puppy\n");
    SV *obj = obj_check(getQtObject());
    GV *gv = gv_fetchmethod(SvSTASH(obj), methodName);
    CV *method = GvCV(gv);
    if(CvXSUB(method)) { pfailed = TRUE; return; }
    callQtMethod(method, arg1, arg2, arg3, arg4);
    FREETMPS; LEAVE;
}

SV *virtualize::retCall(char *methodName, SV *arg1, SV *arg2, SV *arg3,
			SV *arg4) const {
    dSP;
    pfailed = FALSE;
    SV *obj = obj_check(getQtObject());
    GV *gv = gv_fetchmethod(SvSTASH(obj), methodName);
    CV *method = GvCV(gv);
    if(CvXSUB(method)) { pfailed = TRUE; return &sv_undef; }
    callQtMethod(method, arg1, arg2, arg3, arg4);
    SPAGAIN;
    SV *ret = newSVsv(POPs);
    PUTBACK;
    FREETMPS; LEAVE;
    return ret;
}

/*
SV *virtualize::retCall(char *methodName, SV *arg1, SV *arg2, SV *arg3,
			SV *arg4) {
    warn("retCall\n");
    dXSARGS;
    pfailed = FALSE;
    SV *obj = obj_check(getQtObject());
    GV *gv = gv_fetchmethod(SvSTASH(obj), methodName);
    CV *method = GvCV(gv);
    if(CvXSUB(method)) { pfailed = TRUE; return &sv_undef; }
    warn("calling callQtMethod\n");
    callQtMethod(method, arg1, arg2, arg3, arg4);
//    SPAGAIN;
//    warn("successful callQtMethod: %p\n", ST(0));
//    SV *ret = newSVsv(ST(0));
    warn("got ST(0)\n");
    FREETMPS; LEAVE;
    warn("end of retCall\n");
    return &sv_yes;
}
*/
void virtualize::voidCallObj(char *methodName, const void *arg,
			     char *type) const {
//    printf("vco %p\n", arg);
    SV *obj = objectify_ptr((void *)arg, type);
    voidCall(methodName, obj);
//    printf("SvREFCNT_dec\n");
//    printf("obj_check(%p)\n", obj_check(obj));
    SvREFCNT_dec(obj);
}

void virtualize::voidCallObj(char *methodName, const void *arg1, char *type1,
			     const void *arg2, char *type2) const {
//    printf("vco %p %p\n", arg1, arg2);
    SV *obj1 = objectify_ptr((void *)arg1, type1);
    SV *obj2 = objectify_ptr((void *)arg2, type2);
    voidCall(methodName, obj1, obj2);
    SvREFCNT_dec(obj1);
    SvREFCNT_dec(obj2);
}

SV *virtualize::retCallObj(char *methodName, const void *arg,
			   char *type) const {
    SV *obj = objectify_ptr((void *)arg, type);
    SV *ret = retCall(methodName, obj);
    SvREFCNT_dec(obj);
    return ret;
}

SV *virtualize::retCallObj(char *methodName, const void *arg1, char *type1,
			   const void *arg2, char *type2) const {
    SV *obj1 = objectify_ptr((void *)arg1, type1);
    SV *obj2 = objectify_ptr((void *)arg2, type2);
    SV *ret = retCall(methodName, obj1, obj2);
    SvREFCNT_dec(obj1);
    SvREFCNT_dec(obj2);
    return ret;
}

char *virtualize::setQtClassName(char *cname) {
    qtClassName = (char *)malloc(strlen(cname)+1);
    strcpy(qtClassName, cname);

    return cname;
}

