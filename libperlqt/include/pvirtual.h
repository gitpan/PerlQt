#ifndef PVIRTUAL_H
#define PVIRTUAL_H

/*
 * Declaration of the virtualize class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pqt.h"

class virtualize {
    SV *qtObject;
    char *qtClassName;
public:
    virtualize() { qtObject = NULL; }
    virtual ~virtualize();
    void setQtObject(SV *obj) { qtObject = obj; SvREFCNT_inc(obj); }
    SV *getQtObject() const { return qtObject; }
    char *setQtClassName(char *cname);
    char *getQtClassName() const { return qtClassName; }
    void callQtMethod(CV *method, SV *arg1 = Nullsv, SV *arg2 = Nullsv,
		      SV *arg3 = Nullsv, SV *arg4 = Nullsv) const;
    void voidCall(char *methodName, SV *arg1 = Nullsv, SV *arg2 = Nullsv,
		  SV *arg3 = Nullsv, SV *arg4 = Nullsv) const;
    SV *retCall(char *methodName, SV *arg1 = Nullsv, SV *arg2 = Nullsv,
		SV *arg3 = Nullsv, SV *arg4 = Nullsv) const;
    void voidCallObj(char *methodName, const void *arg, char *type) const;
    void voidCallObj(char *methodName, const void *arg1, char *type1,
		     const void *arg2, char *type2) const;
    SV *retCallObj(char *methodName, const void *arg, char *type) const;
    SV *retCallObj(char *methodName, const void *arg1, char *type1,
		   const void *arg2, char *type2) const;
};

extern int pfailed;

#define pQtTHIS(type) ((p ## type *)(Q ## type *)(P ## type *)this)

#endif  // PVIRTUAL_H
