/*
 * virtualize definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pvirtual.h>

virtualize::virtualize() {
    obj = 0;
    classname = 0;
}

virtualize::~virtualize() {
    if(obj) {
	warn("We had an object!!\n");
	SvFLAGS(obj) = (SvFLAGS(obj) & ~SVTYPEMASK) | SVt_NULL;
	SvREFCNT_dec(obj);
    }
    if(classname) delete [] classname;
    warn("Woo hoo!!!!!!!\n");
}

void virtualize::setQtObject(SV *sv) {
    obj = newRV_noinc((SV *)obj_check(sv));
}

SV *virtualize::getQtObject() const {
    return obj;
}

const char *virtualize::setClassName(const char *name) {
    if(classname) delete [] classname;
    classname = new char[strlen(name)+1];
    strcpy(classname, name);
}

const char *virtualize::getClassName() const {
    return classname;
}

void virtualize::voidCall(const char *name,
			  SV *a1, SV *a2, SV *a3, SV *a4, SV *a5, SV *a6) {
    warn("virtual void %s::%s(...);\n", HvNAME(SvSTASH((SV *)obj)), name);
}

SV *virtualize::retCall(const char *name,
			SV *a1, SV *a2, SV *a3, SV *a4, SV *a5, SV *a6) {
    warn("virtual ??? %s::%s(...);\n", HvNAME(SvSTASH((SV *)obj)), name);
}

void virtualize::voidCallConst(const char *name, SV *a1, SV *a2, SV *a3,
			       SV *a4, SV *a5, SV *a6) const {
    warn("virtual void %s::%s(...) const;\n", HvNAME(SvSTASH((SV *)obj)), name);
}

SV *virtualize::retCallConst(const char *name, SV *a1, SV *a2, SV *a3,
			     SV *a4, SV *a5, SV *a6) const {
    warn("virtual ??? %s::%s(...) const;\n", HvNAME(SvSTASH((SV *)obj)), name);
}
