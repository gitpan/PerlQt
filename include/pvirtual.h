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

#include <pqt.h>
#include <qobject.h>
#include <qmetaobj.h>

class virtualize {
    SV *obj;
    char *classname;
public:
    virtualize();
    virtual ~virtualize();
    void setQtObject(SV *);
    SV *getQtObject() const;
    const char *setClassName(const char *);
    const char *getClassName() const;
    void voidCall(const char *, SV * = Nullsv, SV * = Nullsv, SV * = Nullsv,
				SV * = Nullsv, SV * = Nullsv, SV * = Nullsv);
    SV *retCall(const char *, SV * = Nullsv, SV * = Nullsv, SV * = Nullsv,
			      SV * = Nullsv, SV * = Nullsv, SV * = Nullsv);
    void voidCallConst(const char *, SV * = Nullsv, SV * = Nullsv,
				     SV * = Nullsv, SV * = Nullsv,
				     SV * = Nullsv, SV * = Nullsv) const;
    SV *retCallConst(const char *, SV * = Nullsv, SV * = Nullsv,
				   SV * = Nullsv, SV * = Nullsv,
				   SV * = Nullsv, SV * = Nullsv) const;
};

#endif  // PVIRTUAL_H
