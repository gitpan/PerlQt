#include "perlqt.h"
#include "pqt_v.h"
#include "qobjcoll.h"
#include "qmetaobj.h"
#include "QObject_v.h"

pqt_virtual::pqt_virtual(void *pqt1) {
//    printf("Constructing pqt_virtual %p\n", this);
    pqt_this = pqt1;
    pqt_rv = 0;
}

pqt_object_data *pqt_extract_object(SV *);

pqt_virtual::~pqt_virtual() {
    if(pqt_rv) {
        SV *pqtrv = (SV *)pqt_rv;
	if(!SvOK(pqtrv)) return;
        pqt_object_data *pqt_data = pqt_extract_object(pqtrv);
	if(!pqt_data) return;                   // If perl is exiting, our object is already gone
	pqt_data->pqtflags |= PQTOBJ_DELETED;   // Will not be deleted again

//        SvFLAGS(pqtrv) = (SvFLAGS(pqtrv) & ~SVTYPEMASK) | SVt_NULL;
	SvREFCNT_dec(pqtrv);    // This will now destroy the reference, and deallocate the perl object
    }
}

void pqt_virtual::pqt_begin_virtual(const char *pqt1) const {
    dSP;
    ENTER;
    SAVETMPS;
    PUSHMARK(sp);
    XPUSHs(sv_2mortal(newSVsv((SV *)pqt_rv)));
    PUTBACK;
}

void pqt_virtual::pqt_object(void *pqt1) {
    SV *pqtsv = (SV *)pqt1;
    HV *pqthv = (HV *)SvRV(pqtsv);
    SV *pqtnewrv = newRV((SV *)pqthv);
//    SvREFCNT_dec(pqthv);    // Don't lexicalize; give it dynamic scope, per Joshua
    pqt_rv = pqtnewrv;

//    warn("Get %p from %p\n", pqthv, pqt_rv);
//    printf("Assigning to %p\n", this);
}

void pqt_virtual::pqt_call_method(const char *pqt1) const {
    dSP;
//    printf("Calling virtual %s\n", pqt1);
    perl_call_method((char *)pqt1, G_DISCARD);
    FREETMPS;
    LEAVE;
}

SV *pqt_virtual_return_value = 0;

void pqt_virtual::pqt_call_retmethod(const char *pqt1) const {
    dSP;
//    printf("Calling virtual %s\n", pqt1);
    int pqtr = perl_call_method((char *)pqt1, G_SCALAR);
    if(pqtr < 1) croak("perl_call_method croaked");
    SPAGAIN;
    pqt_virtual_return_value = newSVsv(POPs);
    PUTBACK;
    FREETMPS;
    LEAVE;
}
/*
const char *pqt_virtual_QObject::pqt_virtual_className() const {
    return HvNAME(SvSTASH(SvRV((SV *)pqt_rv)));
}

static QMetaObject *pqt_get_superclass_metaobject(const char *pqtclass, int pqtrecurse) {
    char *pqts = new char [strlen(pqtclass) + 6];
    strcpy(pqts, pqtclass);
    strcpy(pqts, "::ISA");
    AV *pqtav_isa = perl_get_av(pqts, TRUE);
    delete [] pqts;

    I32 pqt_isacnt = av_len(pqtav_isa) + 1;
    int pqti;
    for(pqti = 0; pqti <= pqt_isacnt; pqti++) {
        SV **pqt_svp = av_fetch(pqtav_isa, pqti, 0);
	if(!pqt_svp) continue;
	char *pqt_super = SvPV(*pqt_svp, na);
	QMetaObject *pqtmeta_super = pqt_get_superclass_metaobject(pqt_super, pqtrecurse + 1);
	if(pqtmeta_super) return pqtmeta_super;
    }
    return 0;
}

static QMetaObject *pqt_create_metaobject(const char *pqtclass, const char *pqtsuper) {
//warn("Creating new MetaObject where @%s::ISA = ('%s')\n", pqtclass, pqtsuper);
    return new QMetaObject(pqtclass, pqtsuper, 0, 0, 0, 0);
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

QMetaObject *pqt_virtual_QObject::pqt_virtual_metaObject() const {
    const char *pqt_classname = pqt_virtual_className();
//warn("Looking for the MetaObject of %s\n", pqt_classname);
    QMetaObject *pqtmeta = objectDict->find(pqt_classname);    // Thank you, Troll Tech
    if(pqtmeta) return pqtmeta;
    return pqt_create_metaobject(pqt_classname);
}
*/
