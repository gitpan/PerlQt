////////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 1998, Ashley Winters <jql@accessone.com> - All rights reserved.
//
// Since you aren't supposed to have this code, I certainly cannot
// permit your to redistribute it.
//

#ifndef PERLQT_H
#define PERLQT_H

#include "pqt.h"

#if defined(DEBUG)
/*
 * Perl has an extensive set of DEBUG* macros, it's better to cut off the
 * single Qt DEBUG definition than to fiddle with all of Perl's macros. We
 * keep a copy of it in QtDEBUG if it exists. Qt is very conservative with
 * it's use of defines, Perl is just plain reckless. Lets cross our
 * fingers and hope everything works out alright.
 */
#define QtDEBUG
#undef DEBUG
#endif  // defined(DEBUG)

extern "C" {
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include "patchlevel.h"
}

#undef bool
#undef list

#undef METHOD
#undef debug

#if PATCHLEVEL > 4
#define PQT_dXSARGS dXSARGS; PL_markstack_ptr++
#define PQT_uXSARGS PL_markstack_ptr++; dXSARGS
#else
#define PQT_dXSARGS dXSARGS; markstack_ptr++
#define PQT_uXSARGS markstack_ptr++; dXSARGS
#endif

#define PQTOBJ_NEW      0x01          /* created by new */
#define PQTOBJ_DURABLE  0x02          /* don't delete me, even if PQTOBJ_NEW */
#define PQTOBJ_CONST    0x04          /* not our object, we can't unconst it */
#define PQTOBJ_MUTABLE  0x08          /* perl object set to non-const */
#define PQTOBJ_DELETED  0x10          /* objdata->pqtptr was deleted */
#define PQTOBJ_QOBJECT  0x8000        /* Is it a QObject child? */

#define PQTOBJ_DELETE   PQT_NEW
#define PQTOBJ_IMMUNE   PQT_DURABLE
#define PQTOBJ_IMMORTAL (PQT_DURABLE | PQT_NEW)

struct pqt_object_data {
    void *pqtptr;
    pqt_classinfolist *pqtinfo;
    unsigned int pqtflags;
};

extern pqt_object_data pqt__data;  // perfect size for sv_magic's malloced mg_ptr

inline SV *pqt_create_object(const char *pqt1, pqt_object_data *&pqt2) {
    HV *pqthv_obj = newHV();
    sv_magic((SV *)pqthv_obj, 0, '~', (char *)&pqt__data, sizeof(pqt__data));
    pqt2 = (pqt_object_data *)(mg_find((SV *)pqthv_obj, '~')->mg_ptr);
    SV *pqtsv_obj = newRV((SV *)pqthv_obj); SvREFCNT_dec(pqthv_obj);
    return sv_bless(pqtsv_obj, gv_stashpv((char *)pqt1, TRUE));
}

pqt_object_data *pqt_extract_object(SV *);

pqt_classinfolist *pqt_find_info(const char *);
SV *pqt_parse_proto(SV *pqtorigproto);

SV *pqt_argument_sv();

SV *pqt_hv_fetch(HV *pqt_hv, const char *pqt_key);
void pqt_hv_store(HV *pqt_hv, const char *pqt_key, SV *pqt_sv);
bool pqt_hv_exists(HV *pqt_hv, const char *pqt_key);
SV *pqt_av_fetch(AV *pqt_av, I32 pqt_key);
void pqt_hv_delete(HV *pqt_hv, const char *pqt_key);

SV *pqt_argument_peek();

extern HV *pqt_map_crypt;
extern HV *pqthv_class_signals;
extern HV *pqthv_class_slots;


#define PQT_NUM_SHORT           0x0001
#define PQT_NUM_INT             0x0002
#define PQT_NUM_LONG            0x0004
#define PQT_NUM_LONG_LONG       0x0008
#define PQT_NUM_SIGNED          0x0010
#define PQT_NUM_UNSIGNED        0x0020
#define PQT_NUM_FLOAT           0x0100
#define PQT_NUM_DOUBLE          0x0200

#define PQT_PROTO_CONST         0
#define PQT_PROTO_OBJECT        1
#define PQT_PROTO_LONG          2
#define PQT_PROTO_INT           3
#define PQT_PROTO_SHORT         4
#define PQT_PROTO_BOOL          5
#define PQT_PROTO_STRING        6
#define PQT_PROTO_LDOUBLE       7
#define PQT_PROTO_DOUBLE        8
#define PQT_PROTO_FLOAT         9
#define PQT_PROTO_SCALAR        10
#define PQT_PROTO_SCALARREF     11
#define PQT_PROTO_SVSCALAR      12
#define PQT_PROTO_AVSCALAR      13
#define PQT_PROTO_HVSCALAR      14
#define PQT_PROTO_LIST          15

class pqt_argument_iterator {
    const char *pqtargs;
    int pqtcnt;
public:
    pqt_argument_iterator() { pqtargs = NULL; pqtcnt = 0; }
    pqt_argument_iterator(const char *pqt1) {
        pqtargs = pqt1;
        pqtcnt = *pqtargs;
        pqtargs += pqtargs[1] + 2;
    }
    const char *operator ++() {
        const char *pqtr = (--pqtcnt < 0) ? 0 : pqtargs++;
        // Yes, that NULL pointer is intentionally dereferenced here
        if(*pqtr == PQT_PROTO_CONST) pqtr = pqtargs++;
        if(*pqtr == PQT_PROTO_OBJECT) pqtargs += *pqtargs;
        return pqtr;
    }
};

class pqt_extra_slot_data {
    SV *pqt_receiver, *pqt_member, *pqt_crypt, *pqt_class;
    class QMetaObject *pqt_meta;
    friend class pqt_S;

public:
    pqt_extra_slot_data(SV *, SV *);
    ~pqt_extra_slot_data();
};

typedef void (*pqt_signal)();
extern pqt_signal pqt_signal_matrix[];

#endif  // PERLQT_H
