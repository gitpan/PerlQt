#include "perlqt.h"
#include "sigslot.h"
#include "qobjcoll.h"
#include "Qt/QObject_v.h"

extern HV *pqt_map_crypt;

HV *pqthv_class_signals = 0;
HV *pqthv_class_slots = 0;

static QMetaData *pqt_init_metadata(HV *pqts, int &pqtcnt) {
    pqtcnt = 0;
    if(!pqts || HvKEYS(pqts) < 1) return 0;
    int pqt_keys = HvKEYS(pqts);

//printf("Okay, the beginning\n");
    SV *pqt_crypt, *pqt_value;
    char *pqt_key;
    I32 pqt_len;
    int pqti;

    hv_iterinit(pqts);
    for(pqti = 0; pqti < pqt_keys; pqti++) {
        hv_iternextsv(pqts, &pqt_key, &pqt_len);
	if(strchr(pqt_key, '(')) pqtcnt++;
    }

    QMetaData *pqt_tbl = new QMetaData[pqtcnt];


    pqtcnt = 0;
    hv_iterinit(pqts);
    for(pqti = 0; pqti < pqt_keys; pqti++) {
        pqt_value = hv_iternextsv(pqts, &pqt_key, &pqt_len);
//printf("FOO: Found %s\n", pqt_key);
        if(!strchr(pqt_key, '(')) continue;
	pqt_crypt = pqt_hv_fetch(pqt_map_crypt, pqt_key);

	pqt_tbl[pqtcnt].name = SvPVX(pqt_value);

	pqt_tbl[pqtcnt].ptr = pqt_S::stub(pqt_crypt);

	pqtcnt++;
    }
//printf("Count = %d\n", pqtcnt);

    return pqt_tbl;
}

static QMetaObject *pqt_create_metaobject(const char *pqtclass, const char *pqtsuper) {
//warn("Creating new MetaObject where @%s::ISA = ('%s')\n", pqtclass, pqtsuper);
    HV *pqthv_signals, *pqthv_slots;

    pqthv_signals = pqt_hv_exists(pqthv_class_signals, pqtclass) ?
        (HV *)SvRV(pqt_hv_fetch(pqthv_class_signals, pqtclass)) : 0;
    pqthv_slots = pqt_hv_exists(pqthv_class_slots, pqtclass) ?
        (HV *)SvRV(pqt_hv_fetch(pqthv_class_slots, pqtclass)) : 0;

    int pqt_signalcnt;
    int pqt_slotcnt;

    QMetaData *pqtmeta_signal = pqt_init_metadata(pqthv_signals, pqt_signalcnt);
    QMetaData *pqtmeta_slot = pqt_init_metadata(pqthv_slots, pqt_slotcnt);
//printf("Here it comes %d %d\n", pqt_signalcnt, pqt_slotcnt);
    return new QMetaObject(pqtclass, pqtsuper, pqtmeta_slot, pqt_slotcnt, pqtmeta_signal, pqt_signalcnt);
}


static QMetaObject *pqt_create_metaobject(const char *pqtclass) {
    char *pqts = new char [strlen(pqtclass) + 6];
    strcpy(pqts, pqtclass);
    strcat(pqts, "::ISA");

    AV *pqtav_isa = perl_get_av(pqts, TRUE);
    I32 pqt_isacnt = av_len(pqtav_isa) + 1;
    int pqti;

    delete [] pqts;

    for(pqti = 0; pqti < pqt_isacnt; pqti++) {
        SV *pqt_sv = pqt_av_fetch(pqtav_isa, pqti);
        char *pqt_super = SvPV(pqt_sv, na);
        if(objectDict->find(pqt_super))
            return pqt_create_metaobject(pqtclass, pqt_super);
    }

    for(pqti = 0; pqti < pqt_isacnt; pqti++) {
        SV *pqt_sv = pqt_av_fetch(pqtav_isa, pqti);
        char *pqt_super = SvPV(pqt_sv, na);
        QMetaObject *pqtmeta = pqt_create_metaobject(pqt_super);
        if(pqtmeta)
            return pqt_create_metaobject(pqtclass, pqt_super);
    }

    return 0;
}

const char *pqt_virtual_QObject::pqt_virtual_className() const {
    return HvNAME(SvSTASH(SvRV((SV *)pqt_rv)));
}

QMetaObject *pqt_virtual_QObject::pqt_virtual_metaObject() const {
    const char *pqt_classname = pqt_virtual_className();
//warn("Looking for the MetaObject of %s\n", pqt_classname);

    QMetaObject *pqtmeta = objectDict->find(pqt_classname);    // Thank you, Troll Tech
    if(pqtmeta) return pqtmeta;
    return pqt_create_metaobject(pqt_classname);
}

extern int pqt_typeidx(char);
extern int pqt_exp_table[];
extern QMember pqt_slot_matrix[];

int pqt_S::hash(const char *pqt1) {
    int pqtr = 0, pqtcnt = *pqt1;
    pqt_argument_iterator pqt_argit(pqt1);

    int pqti;
    for(pqti = 0; pqti < pqtcnt; pqti++)
	pqtr += pqt_exp_table[pqtcnt - (pqti+1)] * pqt_typeidx(*++pqt_argit);
//printf("Returning hash %d for %s\n", pqtr, pqt1 + 2);
    return pqtr;
}

QMember pqt_S::stub(SV *pqtsv) {
    int pqtx = pqt_S::hash(SvPV(pqtsv, na));
//    printf("Snagging pqt_slot_matrix[%d]\n", pqtx);
    return pqt_slot_matrix[ pqtx ];
}

extern void pqt_push_slot_arguments(const char *);

void pqt_S::slot() {
    dSP;
//printf("Getting crypt from %p\n", this);
    char *pqt_cryptstr = SvPV(pqt_slot->pqt_crypt, na);
//printf("Did that\n");
    ENTER;
    SAVETMPS;
    PUSHMARK(sp);
//printf("Pushing it\n");
    XPUSHs(sv_mortalcopy(pqt_slot->pqt_receiver));
//printf("Pushing arguments for %s\n", SvPV(pqt_slot->pqt_class, na));
    PUTBACK;
    pqt_push_slot_arguments(pqt_cryptstr);
    SPAGAIN;
//printf("Calling %d \"%s\"\n", strlen(pqt_cryptstr + 2), pqt_cryptstr + 2);

//    GV *meth = gv_fetchmethod(SvSTASH(SvRV(pqt_slot->pqt_receiver)), "foo");

//    perl_call_sv((SV *)GvCV(meth), G_DISCARD);

//    perl_call_method(pqt_cryptstr + 1, G_DISCARD);
    perl_call_method(pqt_cryptstr + 2, G_DISCARD);
//printf("Called it\n");
    FREETMPS;
    LEAVE;
}
