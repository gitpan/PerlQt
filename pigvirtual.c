/*
 * Definition and export of functions declared in pigvirtual.h
 *
 * Copyright (C) 1999, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README.LICENSE file which should be included with this library.
 *
 */

#include "pig.h"
#include "pigperl.h"
#include "pigvirtual.h"

PIG_DEFINE_VOID_FUNC_2(pig_virtual_dereference, const class pig_virtual *, void *) {
    SvFLAGS((SV *)pig0->pig_rv) = (SvFLAGS((SV *)pig0->pig_rv) & ~SVTYPEMASK) | SVt_NULL;
    SvREFCNT_dec((SV *)pig0->pig_rv);
}

PIG_DEFINE_VOID_FUNC_2(pig_virtual_setobject, const class pig_virtual *, void *) {
    pig_virtual *pigv = (pig_virtual *)pig0;
    pigv->pig_rv = newSVsv((SV *)pig1);
}

PIG_EXPORT_TABLE(pigvirtual)
    PIG_EXPORT_FUNC(pig_virtual_dereference)
    PIG_EXPORT_FUNC(pig_virtual_setobject)
PIG_EXPORT_ENDTABLE
