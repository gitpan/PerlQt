#include "perlqt.h"
#include "sigslot.h"
#include "qobjcoll.h"

static QObject *pqt_last_sender = 0;
static QObject *pqt_last_receiver = 0;
static SV *pqt_last_receiversv = 0;

bool pqt_is_perl_slot(const char *pqtmember, const char *pqtclass) {
//printf("Looking for %s in %s\n", pqtmember, pqtclass);
    if(pqt_hv_exists(pqthv_class_signals, pqtclass)) {
        HV *pqthv = (HV *)SvRV(pqt_hv_fetch(pqthv_class_signals, pqtclass));
	if(pqt_hv_exists(pqthv, pqtmember))
	    return TRUE;
    }
    if(pqt_hv_exists(pqthv_class_slots, pqtclass)) {
        HV *pqthv = (HV *)SvRV(pqt_hv_fetch(pqthv_class_slots, pqtclass));
        if(pqt_hv_exists(pqthv, pqtmember))
            return TRUE;
    }

    QMetaObject *pqt_meta = objectDict->find(pqtclass);
    if(!(pqt_meta && pqt_meta->superClass())) return FALSE;

    return pqt_is_perl_slot(pqtmember, pqt_meta->superClassName());    // tail recursion
}

QObject *pqt_argument_sender() {
    pqt_last_sender = (QObject *)pqt_argument_const_class("QObject");
    return pqt_last_sender;
}

QObject *&pqt_argument_receiver() {
    pqt_last_receiversv = pqt_argument_peek();
    pqt_last_receiver = (QObject *)pqt_argument_const_class("QObject");
    return pqt_last_receiver;
}

const char *pqt_argument_signal() {
    SV *pqtsv = sv_2mortal(newSVpv("2", 0));   // BUG! Delete a new pointer instead
    sv_catsv(pqtsv, pqt_parse_proto(pqt_argument_sv()));
    return SvPVX(pqtsv);
}

const char *pqt_argument_member() {
    SV *pqtsv = sv_newmortal();
    SV *pqtmembersv = sv_2mortal(pqt_parse_proto(pqt_argument_sv()));
    const char *pqtmember = SvPVX(pqtmembersv);
    QMetaObject *pqtmeta = pqt_last_receiver->metaObject();
    if(pqtmeta->slot(pqtmember, TRUE))
        sv_setpv(pqtsv, "1");
    else if(pqtmeta->signal(pqtmember, TRUE))
        sv_setpv(pqtsv, "2");
    else {
        warn("Can't find member '%s' in %s, defaulting to SLOT()",
	     pqtmember, pqt_last_receiver->className());
	sv_setpv(pqtsv, "1");
    }
    sv_catpv(pqtsv, (char *)pqtmember);
//printf("Looking...\n");
    if(pqt_is_perl_slot(pqtmember, pqt_last_receiver->className())) {
//printf("Found it, creating new slot\n");
        pqt_last_receiver = new pqt_S(pqt_last_receiversv, pqtmembersv);
    }
    return SvPVX(pqtsv);
}

void pqt_push_signal(const char *pqt1) {
    pqt_push_cstring(pqt1 + 1);
}

pqt_extra_slot_data::pqt_extra_slot_data(SV *pqtobj, SV *pqtmember) {
    pqt_receiver = newSVsv(pqtobj);
    SvREFCNT_dec(SvRV(pqtobj));
    pqt_member = newSVsv(pqtmember);
    pqt_class = newSVpv(HvNAME(SvSTASH(SvRV((SV *)pqt_receiver))), 0);
    pqt_crypt = pqt_hv_fetch(pqt_map_crypt, SvPV(pqt_member, na));
    pqt_meta = objectDict->find(SvPVX(pqt_class));
}

pqt_extra_slot_data::~pqt_extra_slot_data() {
//    SvFLAGS(pqt_receiver) = (SvFLAGS(pqt_receiver) & ~SVTYPEMASK) | SVt_NULL;
//    SvREFCNT_dec(pqt_receiver);
//    SvREFCNT_dec(pqt_member);
//    SvREFCNT_dec(pqt_class);
}

extern HV *pqt_map_crypt;

pqt_S::pqt_S(SV *pqtobj, SV *pqtmember) {
    if(!SvROK(pqtobj)) croak("Whoops, no receiver\n");
    pqt_slot = new pqt_extra_slot_data(pqtobj, pqtmember);

//printf("pqt_S => %p\n", this);
}

pqt_S::~pqt_S() {
    delete pqt_slot;
}

void pqt_S::objectDestroyed() {
    delete this;
}

void pqt_S::initMetaObject() {
}

const char *pqt_S::className() const {
    return SvPV(pqt_slot->pqt_class, na);
}

QMetaObject *pqt_S::metaObject() const {
    return pqt_slot->pqt_meta;
}
