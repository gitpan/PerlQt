/*
 * This file apparently defines the basic variables for PerlQt
 *
 * Copyright (C) 1999, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README.LICENSE file which should be included with this library.
 *
 */

#include "pigperl.h"

PIG_DEFINE_VARIABLE(SV *, pig_virtual_return);
PIG_DEFINE_VARIABLE(int, pig_argument_idx);
PIG_DEFINE_VARIABLE(int, pig_argument_max_idx);
PIG_DEFINE_VARIABLE(int, pig_depth);

PIG_EXPORT_TABLE(pigperl)
    PIG_EXPORT_VARIABLE(pig_virtual_return)
    PIG_EXPORT_VARIABLE(pig_argument_idx)
    PIG_EXPORT_VARIABLE(pig_argument_max_idx)
    PIG_EXPORT_VARIABLE(pig_depth)
PIG_EXPORT_ENDTABLE
