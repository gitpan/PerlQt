/*
 * Definition and export of functions in pigfunc_object.h
 *
 * Copyright (C) 1999, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README.LICENSE file which should be included with this library.
 *
 */

#include "pigperl.h"
#include "pigclassinfo.h"
#include "pigtype_object.h"
#include "pigfunc_object.h"

PIG_DEFINE_VOID_FUNC_0(pig_object_continue) {
    PIGARGS;
    struct pig_object_data *pigd = pig_object_extract(ST(0));
    if(!pigd) return;
    pigd->pigflags &= ~PIGOBJECT_BREAK;
    pigd->pigflags |= PIGOBJECT_CONTINUED;
}

PIG_DEFINE_VOID_FUNC_0(pig_object_break) {
    PIGARGS;
    struct pig_object_data *pigd = pig_object_extract(ST(0));
    if(!pigd) return;
    pigd->pigflags &= ~PIGOBJECT_CONTINUED;
    pigd->pigflags |= PIGOBJECT_BREAK;
}

PIG_DEFINE_FUNC_0(bool, pig_object_can_delete) {
    PIGARGS;
    if(!SvOK(ST(0))) return FALSE;

    pig_object_data *pigd = pig_object_extract(ST(0));
    if(pigd->pigflags & PIGOBJECT_ALLOCATED) {
	if(pigd->pigflags & PIGOBJECT_CONTINUED) {
	    PIGARGUMENT(FALSE);
	} else if(pigd->pigflags & PIGOBJECT_BREAK) {
	    PIGARGUMENT(TRUE);
	}
    }
    if(pigd->piginfo->pigclassinfo != PIG_CLASS_SUICIDAL) {
        PIGARGUMENT((pigd->pigflags & PIGOBJECT_ALLOCATED) ? TRUE : FALSE);
    } else {
        PIGARGUMENT(FALSE);
    }
}

PIG_DEFINE_FUNC_2(SV *, pig_object_create, const char *, struct pig_object_data **) {
    static pig_object_data pigpod = { 0, 0, 0 };

    MAGIC *pigmg;
    HV *pighv_obj = newHV();
    SV *pigsv_obj = newRV((SV *)pighv_obj);
    SvREFCNT_dec(pighv_obj);

    sv_magic((SV *)pighv_obj, 0, '~', (char *)&pigpod, sizeof(pigpod));

    pigmg = mg_find((SV *)pighv_obj, '~');
    *pig1 = (pig_object_data *)pigmg->mg_ptr;

    return sv_bless(pigsv_obj, pig_map_class_stash(pig0));
}


PIG_DEFINE_FUNC_1(pig_object_data *, pig_object_extract, SV *) {
    if(!pig0 || !SvROK(pig0)) return 0;
    HV *pighv_obj;
    MAGIC *pigmg;
    pig_object_data *pigd;

    pighv_obj = (HV *)SvRV(pig0);
    pigmg = mg_find((SV *)pighv_obj, '~');
    if(!pigmg) return 0;
    pigd = (pig_object_data *)pigmg->mg_ptr;

    return pigd;
}

PIG_DEFINE_FUNC_2(void *, pig_object_cast, struct pig_object_data *, const char *) {
    if(!pig0 || !pig0->pigptr) return 0;
    pig_classinfo *piginfo = pig0->piginfo;
    void *pigr = (*piginfo->pigtocastfunc)(pig1, (void *)pig0->pigptr);
    if(!pigr)
        die("Cannot cast %s pointer to %s", piginfo->pigclassname, pig1);
    return pigr;
}

extern bool pig_class_isa(HV *pigstash, const char *pigclass);

PIG_DEFINE_FUNC_2(int, pig_object_isa, int, const char *) {
    PIGARGS;
    int pigr = pig_class_isa(SvSTASH(SvRV(ST(pig0))), pig_map_class(pig1));
    //warn("Is %s a subclass of %s? %d\n", pig_map_class(pig1), HvNAME(SvSTASH(SvRV(ST(pig0)))), pigr);
    return pigr ? 1 : 0;
}

PIG_EXPORT_TABLE(pigfunc_object)
    PIG_EXPORT_FUNC(pig_object_break)
    PIG_EXPORT_FUNC(pig_object_continue)
    PIG_EXPORT_FUNC(pig_object_can_delete)
    PIG_EXPORT_FUNC(pig_object_create)
    PIG_EXPORT_FUNC(pig_object_extract)
    PIG_EXPORT_FUNC(pig_object_cast)
    PIG_EXPORT_FUNC(pig_object_isa)
PIG_EXPORT_ENDTABLE
