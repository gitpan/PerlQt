/*
 * I have no idea where this file came from
 *
 * Copyright (C) 1999, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README.LICENSE file which should be included with this library.
 *
 */

#include "pigperl.h"
#include "pigvirtual.h"
#include "pigtype_object.h"
#include "pigfunc_object.h"
#include "pigclassinfo.h"
#include <qobject.h>
#include <qobjcoll.h>
#include <qmetaobj.h>
#include "pigsigslot.h"

class pig_public_QObject : public QObject {
public:
    void doInitMetaObject() { this->initMetaObject(); }
    class QMetaObject *doMetaObject() { return this->metaObject(); }
};

void break_it_here() {

}

static bool pig_is_perl_receiver(QMetaObject *pigm, const char *pigproto) {
    if(pig_classinfo_fetch(pigm->className()))		// if(QClass) return false
        return FALSE;

    if(pigm->signal(pigproto, FALSE) || pigm->slot(pigproto, FALSE))
        return TRUE;
    else if(pigm->superClass())
	return pig_is_perl_receiver(pigm->superClass(), pigproto);

    return FALSE;
}

// pig0 = object, pig1 = member
PIG_DEFINE_FUNC_2(bool, pig_receiver_defined, SV *, SV *) {
    PIGARGS;
    STRLEN n_a;
    SV *pigprotosv = pig_parse_proto(pig1);
    const char *pigproto = SvPV(pigprotosv, n_a);

//warn("Is there a receiver defined for %s?\n", pigproto);

    pig_object_data *pigd = pig_object_extract(pig0);
    QObject *pigobj = (QObject *)pig_object_cast(pigd, "QObject");

    QMetaObject *pigm = pigobj->metaObject();

    bool pigr = pig_is_perl_receiver(pigm, pigproto);

    SvREFCNT_dec(pigprotosv);

    return pigr;
}

// pig0 = object, pig1 = member
PIG_DEFINE_FUNC_2(class QObject *, pig_create_slot, SV *, SV *) {
    PIGARGS;
    STRLEN n_a;
//printf("WHOOPS!\n");
    SV *pigprotosv = pig_parse_proto(pig1);
    const char *pigproto = SvPV(pigprotosv, n_a);
    pig_slot_data *pigsd;

    pig_object_data *pigd = pig_object_extract(pig0);
    QObject *pigobj = (QObject *)pig_object_cast(pigd, "QObject");
    QMetaObject *pigm = pigobj->metaObject();

    pigsd = new pig_slot_data;
    pigsd->pigreceiver = newSVsv(pig0);
//printf("%p = %p\n", pigsd->pigreceiver, SvRV(pig0));
    //SvREFCNT_dec(SvRV(pig0));
    pigsd->pigproto = new char[strlen(pigproto) + 1];
    strcpy((char *)pigsd->pigproto, pigproto);
    pigsd->pigcrypt = SvPV(pig_map_proto(pigprotosv), n_a);
    pigsd->pigmethod = pigsd->pigcrypt + 2;
    pigsd->pigmeta = pigm;

    pig_S *pigslot = new pig_S;
    pigslot->pigsd = pigsd;

//warn("Created slot %p\n", pigslot);

//    pigslot->connect(pigobj, SIGNAL(destroyed()), SLOT(pig_S_destroyed()));

//    QObject::connect(pigobj, SIGNAL(destroyed()), pigslot,
//SLOT(pig_S_destroyed()));
//warn("Connecting %p to %p\n", pigobj, pigslot);

    return pigslot;
}

PIG_DEFINE_FUNC_2(const char *, pig_member_string, SV *, SV *) {
    PIGARGS;
    STRLEN n_a;
//printf("Well... %s %s\n", SvPV(pig0, na), SvPV(pig1, na));
    SV *pigprotosv = pig_parse_proto(pig1);
//printf("It wasn't there\n");
    const char *pigproto = SvPV(pigprotosv, n_a);

    pig_object_data *pigd = pig_object_extract(pig0);
    QObject *pigobj = (QObject *)pig_object_cast(pigd, "QObject");
//printf("Looks like we got a %s\n", pigobj->className());
    QMetaObject *pigm = pigobj->metaObject();

    SV *pigr = sv_newmortal();
    if(pigm->signal(pigproto, TRUE))
        sv_setiv(pigr, SIGNAL_CODE);
    else
        sv_setiv(pigr, SLOT_CODE);

    sv_catpv(pigr, (char *)pigproto);

//printf("Got the member for %s\n", pigproto);
    return SvPVX(pigr);
}

void pig_assign_pigd(pig_object_data *pigd, void *pigptr, pig_classinfo *piginfo, long pigflags) {
    pigd->pigptr = pigptr;
    pigd->piginfo = piginfo;
    pigd->pigflags = pigflags;

//printf("okay, %p -> %p:%p:%x\n", pigd, pigd->pigptr, pigd->piginfo, pigd->pigflags);
}

PIG_DEFINE_FUNC_3(SV *, pig_new_castobject, void *, const char *, const char *) {
    pig_object_data *pigd;
    SV *pigr = sv_2mortal(pig_object_create(pig2, &pigd));

    pig_assign_pigd(pigd, pig0, pig_classinfo_fetch(pig1), PIGOBJECT_ALLOCATED);

    pig_virtual *pigv =
      (pig_virtual *)(*pigd->piginfo->pigtocastfunc)("virtual", pig0);
    if(pigv) pig_virtual_setobject(pigv, pigr);

    QObject *pigobj =
      (QObject *)(*pigd->piginfo->pigtocastfunc)("QObject", pig0);
    if(pigobj) ((pig_public_QObject *)pigobj)->doInitMetaObject();

    return pigr;
}

PIG_DEFINE_VOID_FUNC_3(pig_type_new_castobject_return, void *, const char *, const char *) {
    PIGRET;
    pig_object_data *pigd;
    SV *pigr = sv_2mortal(pig_object_create(pig2, &pigd));

    pig_assign_pigd(pigd, pig0, pig_classinfo_fetch(pig1), PIGOBJECT_ALLOCATED);

    pig_virtual *pigv =
      (pig_virtual *)(*pigd->piginfo->pigtocastfunc)("virtual", pig0);
    if(pigv) pig_virtual_setobject(pigv, pigr);

    QObject *pigobj = 
      (QObject *)(*pigd->piginfo->pigtocastfunc)("QObject", pig0);
    if(pigobj) ((pig_public_QObject *)pigobj)->doInitMetaObject();

//    sv_bless(PIG_RETARG, gv_stashpv((char *)pig2, TRUE));
    PIGRETURN(pigr);
}

PIG_DEFINE_VOID_FUNC_2(pig_type_new_object_return, void *, const char *) {
    PIGRET;
    pig_object_data *pigd;
    if(!pig0) { PIGRETURN(sv_mortalcopy(&PIGsv_undef)); }
    SV *pigr = sv_2mortal(pig_object_create(pig_map_class(pig1), &pigd));
//printf("Creating %s(%p)\n", pig_map_class(pig1), pig0);
    pig_assign_pigd(pigd, pig0, pig_classinfo_fetch(pig1), PIGOBJECT_ALLOCATED);

//    pig_virtual *pigv =
//      (pig_virtual *)(*pigd->piginfo->pigtocastfunc)("virtual", pig0);
//    if(pigv) pig_virtual_setobject(pigv, PIG_RETARG);

//    sv_bless(pigr, gv_stashpv((char *)pig_map_class(pig1), TRUE));
//printf("Returning %p => %p\n", pigr, SvRV(pigr));
    PIGRETURN(pigr);
}

PIG_DEFINE_FUNC_1(void *, pig_type_object_destructor_argument, const char *) {
    PIGARGS;
//PIGstack_sp - (PIGstack_base + TOPMARK)
    pig_object_data *pigd = pig_object_extract(PIG_ARG);
//printf("Argument %d = %p => %p == %p\n", pig_argument_idx, PIG_ARG, pigd, pigd->pigptr);
    if(!pigd) return 0;
    PIGARGUMENT(pig_object_cast(pigd, pig0));
}

PIG_DEFINE_FUNC_0(bool, pig_object_can_delete) {
    PIGARGS;
    if(!SvOK(ST(0))) return FALSE;
    pig_object_data *pigd = pig_object_extract(ST(0));
//printf("flags: %x\n", pigd->pigflags);
//printf("testing for delete of %s:%p:%p:%x %s\n", pigd->piginfo->pigclassname, pigd, pigd->pigptr, pigd->pigflags, (pigd->pigflags & PIGOBJECT_ALLOCATED) ? "TRUE" : "FALSE");

    if(pigd->piginfo->pigclassinfo != PIG_CLASS_SUICIDAL) {
        PIGARGUMENT((pigd->pigflags & PIGOBJECT_ALLOCATED) ? TRUE : FALSE);
    } else {
	PIGARGUMENT(FALSE);
    }
}

PIG_DEFINE_VOID_FUNC_2(pig_object_destroy, void *, class pig_virtual *) {
    die("Please, no\n");
}



/* borrowed from Perl source under GPL */

static bool isa_lookup(HV *stash, char *name, int len, int level) {
    AV* av;
    GV* gv;
    GV** gvp;
    HV* hv = Nullhv;

    if (!stash)
        return FALSE;

    if(strEQ(HvNAME(stash), name))
        return TRUE;

    if (level > 100)
        croak("Recursive inheritance detected in package '%s'", HvNAME(stash));

    gvp = (GV**)hv_fetch(stash, "::ISA::CACHE::", 14, FALSE);

    if (gvp && (gv = *gvp) != (GV*)&PIGsv_undef && (hv = GvHV(gv))) {
        SV* sv;
        SV** svp = (SV**)hv_fetch(hv, name, len, FALSE);
        if (svp && (sv = *svp) != (SV*)&PIGsv_undef)
            return SvTRUE(sv);
    }

    gvp = (GV**)hv_fetch(stash,"ISA",3,FALSE);

    if (gvp && (gv = *gvp) != (GV*)&PIGsv_undef && (av = GvAV(gv))) {
        if(!hv) {
            gvp = (GV**)hv_fetch(stash, "::ISA::CACHE::", 14, TRUE);

            gv = *gvp;

            if (SvTYPE(gv) != SVt_PVGV)
                gv_init(gv, stash, "::ISA::CACHE::", 14, TRUE);

            hv = GvHVn(gv);
        }
        if(hv) {
            SV** svp = AvARRAY(av);
            /* NOTE: No support for tied ISA */
            I32 items = AvFILL(av) + 1;
            while (items--) {
                SV* sv = *svp++;
                HV* basestash = gv_stashsv(sv, FALSE);
                if (!basestash) {
                    if (PIGdowarn)
                        warn("Can't locate package %s for @%s::ISA",
                            SvPVX(sv), HvNAME(stash));
                    continue;
                }
                if(isa_lookup(basestash, name, len, level + 1)) {
                    (void)hv_store(hv,name,len,&PIGsv_yes,0);
                    return TRUE;
                }
            }
            (void)hv_store(hv,name,len,&PIGsv_no,0);
        }
    }

    return strEQ(name, "UNIVERSAL");
}

/* end borrowed Perl source */

bool pig_class_isa(HV *pigstash, const char *pigclass) {
    bool pigr = isa_lookup(pigstash, (char *)pigclass, strlen(pigclass), 0);
    return pigr;
}

extern QMember pig_slot_matrix[];
extern int pig_sigslot_exp_table[];
extern int pig_sigslot_typeidx(char);
extern void pig_push_slot_arguments(const char *);

void pigslot(pig_S *pigthis) {
    dSP;
    pig_slot_data *pigsd = pigthis->pigsd;
    ENTER;
    SAVETMPS;
    PUSHMARK(sp);
    XPUSHs(sv_mortalcopy(pigsd->pigreceiver));

    PUTBACK;
    pig_push_slot_arguments(pigsd->pigcrypt);
    SPAGAIN;
    perl_call_method((char *)pigsd->pigmethod, G_DISCARD);
    SPAGAIN;
    FREETMPS;
    LEAVE;
}

PIG_DEFINE_FUNC_1(int, pig_sigslot_hash, const char *) {
    int pigr = 0, pigcnt = *pig0;
    pig_sigslot_argument_iterator pig_argit(pig0);

    int pigi;
    for(pigi = 0; pigi < pigcnt; pigi++)
        pigr += pig_sigslot_exp_table[pigcnt - (pigi+1)] * pig_sigslot_typeidx(*++pig_argit);
    return pigr;
}

PIG_DEFINE_FUNC_1(QMember, pig_sigslot_stub, SV *) {
    STRLEN n_a;
    int pigidx = pig_sigslot_hash(SvPV(pig0, n_a));
    return pig_slot_matrix[pigidx];
}

static QMetaData *pig_createMetaData(HV *pighv, bool pigslot, int *pigcount = 0) {
    int pigcnt = 0;
    int pigkeys = 0;

    if(!pighv) {
	if(pigcount) *pigcount = 0;
	return 0;
    }

    pigkeys = HvKEYS(pighv);
    QMetaData *pigtbl = new QMetaData[pigslot ? pigkeys + 1 : pigkeys];

    char *pigkey;
    I32 piglen;
    SV *pigvalue;
    hv_iterinit(pighv);
    for(pigcnt = 0; pigcnt < pigkeys; pigcnt++) {
	pigvalue = hv_iternextsv(pighv, &pigkey, &piglen);
	pigtbl[pigcnt].name = pigkey;
	pigtbl[pigcnt].ptr = pig_sigslot_stub(pigvalue);
    }

    if(pigslot) {
        pigtbl[pigcnt].name = "pig_S_destroyed()";
	pigtbl[pigcnt].ptr = (QMember)&pig_S::pig_S_destroyed;
	pigcnt++;
    }

    if(pigcount) *pigcount = pigcnt;

    return pigtbl;
}

PIG_DEFINE_FUNC_2(class QMetaObject *, pig_createMetaObject, const char *, class QMetaObject *) {
    int pigsigcnt, pigslotcnt;
    QMetaData *pigsigmeta, *pigslotmeta;
    HV *pigsighv = 0, *pigslothv = 0;
    GV *piggv = 0;
    HV *pigstash;
    SV **pigsvp;

//    printf("Creating QMetaObject for %s which isa %s\n", 0, pig1->className());
    objectDict->remove(pig0);

    pigstash = gv_stashpv((char *)pig0, TRUE);
    pigsvp = hv_fetch(pigstash, ".signals", 8, FALSE);
    if(pigsvp) pigsighv = GvHV(*pigsvp);
    pigsvp = hv_fetch(pigstash, ".slots", 6, FALSE);
    if(pigsvp) pigslothv = GvHV(*pigsvp);
    
    pigsigmeta = pig_createMetaData(pigsighv, FALSE, &pigsigcnt);
    pigslotmeta = pig_createMetaData(pigslothv, TRUE, &pigslotcnt);

    return new QMetaObject(pig0, pig1->className(), pigslotmeta, pigslotcnt, pigsigmeta, pigsigcnt);
}

PIG_DEFINE_FUNC_1(class QMetaObject *, pig_initMetaObject, const char *) {
    AV *pigav_isa;
    SV **pigsvp_isa;
    I32 pigcnt_isa, pigidx;
    const char *pigsuper = 0;

    {
	HV *pigstash = gv_stashpv((char *)pig0, TRUE);
	pigsvp_isa = hv_fetch(pigstash, "ISA", 3, FALSE);
	pigav_isa = GvAV((GV *)*pigsvp_isa);
	if(!pigav_isa) return 0;
    }

    pigcnt_isa = AvFILL(pigav_isa);
    pigsvp_isa = AvARRAY(pigav_isa);

    for(pigidx = 0; pigidx <= pigcnt_isa; pigidx++) {
	if(pig_class_isa(gv_stashsv(*pigsvp_isa, FALSE), pig_map_class("QObject"))) {
	    STRLEN n_a;
	    pigsuper = SvPV(*pigsvp_isa, n_a);
	    break;
	}
        pigsvp_isa++;
    }

    if(!pigsuper)
	return 0;

    class QMetaObject *pigsupermeta = objectDict->find(pig_unmap_class(pigsuper));
    if(!pigsupermeta) pigsupermeta = pig_initMetaObject(pigsuper);

    return pig_createMetaObject(pig0, pigsupermeta);
}

const char * pig_virtual_QObject__className(const pig_virtual *pig0) {
    return HvNAME(SvSTASH(SvRV((SV *)pig0->pig_rv)));
}

class QMetaObject * pig_virtual_QObject__metaObject(const pig_virtual *pig0) {
//    pig_object_data *pigd = pig_object_extract((SV *)pig0->pig_rv);
//warn("metaobject\n");
//warn("metaobject of %s\n", pigd->piginfo->pig_classname);
//warn("Going to return %p\n", objectDict->find(pigd->piginfo->pig_classname));

    class QMetaObject *pigm;

    const char *pigclass;
    pigclass = pig_unmap_class(HvNAME(SvSTASH(SvRV((SV *)pig0->pig_rv))));

//printf("Okay, %p, %p, %p, %s\n", pig0->pig_rv, SvRV((SV *)pig0->pig_rv), SvSTASH(SvRV((SV *)pig0->pig_rv)), HvNAME(SvSTASH(SvRV((SV *)pig0->pig_rv))));

    pigm = objectDict->find(pigclass);
    if(!pigm)
        pigm = pig_initMetaObject(pigclass);

    return pigm;
}

PIG_EXPORT_TABLE(pigobject)
    PIG_EXPORT_FUNC(pig_receiver_defined)
    PIG_EXPORT_FUNC(pig_create_slot)
    PIG_EXPORT_FUNC(pig_member_string)

    PIG_EXPORT_FUNC(pig_new_castobject)
    PIG_EXPORT_FUNC(pig_type_new_castobject_return)
    PIG_EXPORT_FUNC(pig_type_new_object_return)
    PIG_EXPORT_FUNC(pig_type_object_destructor_argument)
    PIG_EXPORT_FUNC(pig_object_can_delete)
    PIG_EXPORT_FUNC(pig_object_destroy)

    PIG_EXPORT_FUNC(pig_createMetaObject)
    PIG_EXPORT_FUNC(pig_initMetaObject)
    PIG_EXPORT_FUNC(pig_sigslot_hash)
    PIG_EXPORT_FUNC(pig_sigslot_stub)
PIG_EXPORT_ENDTABLE
