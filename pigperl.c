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

PIG_DEFINE_VOID_FUNC_2(pig_scope_argument, pigscopefptr, void *) {
    pig_sub_scope *pigscope;
    pigscope = new pig_sub_scope;
    pigscope->pignext = pig_frame->pigscope;
    pig_frame->pigscope = pigscope;
    pigscope->pigfptr = pig0;
    pigscope->pigdata = pig1;
}

PIG_DEFINE_VOID_FUNC_2(pig_scope_virtual, pigscopefptr, void *) {
    static pigscopefptr pigfptr = 0;
    static void *pigptr = 0;

    if(pigptr) (*pigfptr)(pigptr);
    pigfptr = pig0;
    pigptr = pig1;
}

PIG_DEFINE_VOID_FUNC_1(pig_scope_leave, pig_sub_scope *) {
    pig_sub_scope *pigold;
    if(!pig0) return;
    while(pig0) {
        (*pig0->pigfptr)(pig0->pigdata);
	pigold = pig0;
	pig0 = pig0->pignext;
	delete pigold;
    }
}

#undef pig_frame
PIG_DEFINE_VARIABLE(SV *, pig_virtual_return);
PIG_DEFINE_VARIABLE(int, pig_argument_idx);
PIG_DEFINE_VARIABLE(int, pig_argument_max_idx);
PIG_DEFINE_VARIABLE(int, pig_depth);
PIG_DEFINE_VARIABLE(struct pig_sub_frame *, pig_frame) = 0;

PIG_EXPORT_TABLE(pigperl)
    PIG_EXPORT_VARIABLE(pig_frame)
    PIG_EXPORT_VARIABLE(pig_virtual_return)
    PIG_EXPORT_VARIABLE(pig_argument_idx)
    PIG_EXPORT_VARIABLE(pig_argument_max_idx)
    PIG_EXPORT_VARIABLE(pig_depth)
    PIG_EXPORT_FUNC(pig_scope_argument)
    PIG_EXPORT_FUNC(pig_scope_virtual)
    PIG_EXPORT_FUNC(pig_scope_leave)
PIG_EXPORT_ENDTABLE
