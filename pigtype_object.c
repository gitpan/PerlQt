/*
 * Definition and export of types declared in pigtype_object.h
 *
 * Copyright (C) 1999, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README.LICENSE file which should be included with this library.
 *
 */

#include "pigperl.h"
#include "pigfunc_object.h"
#include "pigtype_object.h"
#include "pigclassinfo.h"

PIG_DEFINE_TYPE_ARGUMENT2(pig_type_object, void *, const char *) {
    PIGARGS;
    pig_object_data *pigd = pig_object_extract(PIG_ARG);
    PIGARGUMENT(pig_object_cast(pigd, pig0));
}

PIG_DEFINE_TYPE_DEFARGUMENT2(pig_type_object, void *, const char *) {
    PIGARGS;
    if(!PIG_ARGOK) {
        PIGARGUMENT(pig0);
    }
    pig_object_data *pigd = pig_object_extract(PIG_ARG);
    PIGARGUMENT(pig_object_cast(pigd, pig1));
}

PIG_DEFINE_TYPE_RETURN2(pig_type_object, void *, const char *) {
    PIGRET;
    pig_object_data *pigd;
    SV *pigr = sv_2mortal(pig_object_create(pig_map_class(pig1), &pigd));
    pigd->pigptr = pig0;
    pigd->piginfo = pig_classinfo_fetch(pig1);
    pigd->pigflags = 0x100;
    PIGRETURN(pigr);
}

PIG_DEFINE_TYPE_PUSH2(pig_type_object, void *, const char *) {
    PIGPUSHSTACK;
    pig_object_data *pigd;
    SV *pigr = sv_2mortal(pig_object_create(pig_map_class(pig1), &pigd));
    pigd->pigptr = pig0;
    pigd->piginfo = pig_classinfo_fetch(pig1);
    pigd->pigflags = 0x200;
    PIGPUSH(pigr);
}

PIG_DEFINE_TYPE_POP2(pig_type_object, void *, const char *) {
    PIGPOPSTACK;
    pig_object_data *pigd = pig_object_extract(PIG_TOPSTACK);
    PIGPOP(pig_object_cast(pigd, pig0));
}


PIG_DEFINE_TYPE_ARGUMENT2(pig_type_object_ref, void *, const char *) {
    PIGARGS;
    pig_object_data *pigd = pig_object_extract(PIG_ARG);
    PIGARGUMENT(pig_object_cast(pigd, pig0));
}

PIG_DEFINE_TYPE_DEFARGUMENT2(pig_type_object_ref, void *, const char *) {
    PIGARGS;
    if(!PIG_ARGOK) {
        PIGNEXTARG;
	return pig0;
    }
    pig_object_data *pigd = pig_object_extract(PIG_ARG);
    PIGARGUMENT(pig_object_cast(pigd, pig1));
}

PIG_DEFINE_TYPE_RETURN2(pig_type_object_ref, void *, const char *) {
    PIGRET;
    pig_object_data *pigd;
    SV *pigr = sv_2mortal(pig_object_create(pig_map_class(pig1), &pigd));
    pigd->pigptr = pig0;
    pigd->piginfo = pig_classinfo_fetch(pig1);
    pigd->pigflags = 0x300;
    PIGRETURN(pigr);
}

PIG_DEFINE_TYPE_PUSH2(pig_type_object_ref, void *, const char *) {
    PIGPUSHSTACK;
    pig_object_data *pigd;
    SV *pigr = sv_2mortal(pig_object_create(pig_map_class(pig1), &pigd));
    pigd->pigptr = pig0;
    pigd->piginfo = pig_classinfo_fetch(pig1);
    pigd->pigflags = 0x400;
    PIGPUSH(pigr);
}

PIG_DEFINE_TYPE_POP2(pig_type_object_ref, void *, const char *) {
    PIGPOPSTACK;
    pig_object_data *pigd = pig_object_extract(PIG_TOPSTACK);
    PIGPOP(pig_object_cast(pigd, pig0));
}

PIG_DEFINE_TYPE_ARGUMENT2(pig_type_const_object, const void *, const char *) {
    PIGARGS;
    pig_object_data *pigd = pig_object_extract(PIG_ARG);
    PIGARGUMENT(pig_object_cast(pigd, pig0));
}

PIG_DEFINE_TYPE_DEFARGUMENT2(pig_type_const_object, const void *, const char *) {
    PIGARGS;
    if(!PIG_ARGOK) {
        PIGNEXTARG;
	return pig0;
    }
    pig_object_data *pigd = pig_object_extract(PIG_ARG);
    PIGARGUMENT(pig_object_cast(pigd, pig1));
}

PIG_DEFINE_TYPE_RETURN2(pig_type_const_object, const void *, const char *) {
    PIGRET;
    pig_object_data *pigd;
    SV *pigr = sv_2mortal(pig_object_create(pig_map_class(pig1), &pigd));
    pigd->pigptr = pig0;
    pigd->piginfo = pig_classinfo_fetch(pig1);
    pigd->pigflags = 0x500 & PIGOBJECT_CONST;
    PIGRETURN(pigr);
}

PIG_DEFINE_TYPE_PUSH2(pig_type_const_object, const void *, const char *) {
    PIGPUSHSTACK;
    pig_object_data *pigd;
    SV *pigr = sv_2mortal(pig_object_create(pig_map_class(pig1), &pigd));
    pigd->pigptr = pig0;
    pigd->piginfo = pig_classinfo_fetch(pig1);
    pigd->pigflags = 0x600 & PIGOBJECT_CONST;
    PIGPUSH(pigr);
}

PIG_DEFINE_TYPE_POP2(pig_type_const_object, const void *, const char *) {
    PIGPOPSTACK;
    pig_object_data *pigd = pig_object_extract(PIG_TOPSTACK);
    PIGPOP(pig_object_cast(pigd, pig0));
}


PIG_DEFINE_TYPE_ARGUMENT2(pig_type_const_object_ref, const void *, const char *) {
    PIGARGS;
    pig_object_data *pigd = pig_object_extract(PIG_ARG);
    PIGARGUMENT(pig_object_cast(pigd, pig0));
}

PIG_DEFINE_TYPE_DEFARGUMENT2(pig_type_const_object_ref, const void *, const char *) {
    PIGARGS;
    if(!PIG_ARGOK) {
        PIGNEXTARG;
	return pig0;
    }
    pig_object_data *pigd = pig_object_extract(PIG_ARG);
    PIGARGUMENT(pig_object_cast(pigd, pig1));
}

PIG_DEFINE_TYPE_RETURN2(pig_type_const_object_ref, const void *, const char *) {
    PIGRET;
    pig_object_data *pigd;
    SV *pigr = sv_2mortal(pig_object_create(pig_map_class(pig1), &pigd));
    pigd->pigptr = pig0;
    pigd->piginfo = pig_classinfo_fetch(pig1);
    pigd->pigflags = 0x700 & PIGOBJECT_CONST;
    PIGRETURN(pigr);
}

PIG_DEFINE_TYPE_PUSH2(pig_type_const_object_ref, void *, const char *) {
    PIGPUSHSTACK;
    pig_object_data *pigd;
    SV *pigr = sv_2mortal(pig_object_create(pig_map_class(pig1), &pigd));
    pigd->pigptr = pig0;
    pigd->piginfo = pig_classinfo_fetch(pig1);
    pigd->pigflags = 0x800 & PIGOBJECT_CONST;
    PIGPUSH(pigr);
}

PIG_DEFINE_TYPE_POP2(pig_type_const_object_ref, const void *, const char *) {
    PIGPOPSTACK;
    pig_object_data *pigd = pig_object_extract(PIG_TOPSTACK);
    PIGPOP(pig_object_cast(pigd, pig0));
}

PIG_DEFINE_TYPE(pig_type_object)
PIG_DEFINE_TYPE(pig_type_object_ref)
PIG_DEFINE_TYPE(pig_type_const_object)
PIG_DEFINE_TYPE(pig_type_const_object_ref)

PIG_EXPORT_TABLE(pigtype_object)
    PIG_EXPORT_TYPE(pig_type_object, "object")
    PIG_EXPORT_TYPE(pig_type_object_ref, "object&")
    PIG_EXPORT_TYPE(pig_type_const_object, "const object")
    PIG_EXPORT_TYPE(pig_type_const_object_ref, "const object&")
PIG_EXPORT_ENDTABLE
