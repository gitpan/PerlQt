/*
 * Definition and export of functions in pigfunc_qt.h
 *
 * Copyright (C) 1999, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README.LICENSE file which should be included with this library.
 *
 */

#include "pigperl.h"
#include "pigfunc_qt.h"

PIG_DEFINE_STUB_1(const char *, pig_munge_qdatastream, class QDataStream &)
PIG_DEFINE_VOID_STUB_1(pig_unmunge_qdatastream, const char *)

#undef pig_dstreamptr
PIG_DEFINE_VARIABLE(class QDataStream *, pig_dstreamptr) = 0;

PIG_EXPORT_TABLE(pigfunc_qt)
    PIG_EXPORT_FUNC(pig_munge_qdatastream)
    PIG_EXPORT_FUNC(pig_unmunge_qdatastream)
    PIG_EXPORT_VARIABLE(pig_dstreamptr)
PIG_EXPORT_ENDTABLE
