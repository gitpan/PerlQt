/*
 * XS functions for /Qt::(signals|slots)::import/
 *
 * Copyright (C) 1999, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README.LICENSE file which should be included with this library.
 *
 */

#include "pig.h"
#include "pigperl.h"
#include "pigfunc_base.h"
#include "pigfunc_object.h"
#include "pigtype_object.h"
#include <qapplication.h>
#include <qobject.h>
#include <qconnection.h>
#include "pigsigslot.h"

HV *__pig_class_info = 0;

class pig_public_QObject : public QObject {
public:
    QConnectionList *getReceivers(const char *pig0) const {
        return receivers(pig0);
    }
};

SV *pig_map_signal(const char *pigclass, const char *pigmethod) {
    static const char pigmap[] = ".signalmap";

    char *pigvar;
    pigvar = new char [strlen(pigclass) + 2 + strlen(pigmap) + 1];

    sprintf(pigvar, "%s::%s", pigclass, pigmap);

    HV *pigmaphv = perl_get_hv(pigvar, TRUE);

//printf("getting %s::%s = %p\n", pigclass, pigmap, pigmaphv);

    delete [] pigvar;

    SV **pigsvp = hv_fetch(pigmaphv, (char *)pigmethod, strlen(pigmethod), 0);
//printf("x = %p\n", pigsvp);
//printf("foo = %s\n", SvPV(*pigsvp, na));
    if(pigsvp) return *pigsvp;

    return &PIGsv_undef;
}

int pig_sigslot_typeidx(char pig1);
void pig_pop_signal_arguments(const char *pigcrypt);
typedef void (*pig_signal)();
extern pig_signal pig_signal_matrix[];
extern int pig_sigslot_exp_table[];
extern QObject *pig_signal_object;
extern QMember *pig_signal_member;

extern "C" PIG_PROTO(pig_signal_emit) {
    PIG_BEGIN(pig_emit);
    STRLEN n_a;
    const char *pigclass = HvNAME(GvSTASH(CvGV((CV *)pigCV)));
    const char *pigmethod = GvNAME(CvGV((CV *)pigCV));

    SV *pigprotosv = pig_map_signal(pigclass, pigmethod);
    const char *pigproto = SvPV(pigprotosv, n_a);
    SV *pigcryptsv = pig_map_proto(pigprotosv);
    const char *pigcrypt = SvPV(pigcryptsv, n_a);
    QObject *pigobj = (QObject *)pig_type_object_argument("QObject");
//printf("Object = %p\n", pigobj);
    pig_pop_signal_arguments(pigcrypt);
    PIG_END_ARGUMENTS;

    pig_signal pig_hash_table[PIG_SIGSLOT_MAX_ARGS + 1];
    pig_hash_table[0] = pig_signal_matrix[0];

    {
        pig_sigslot_argument_iterator pigiter(pigcrypt);
	const char *pigarg;
	int pigi;
	long pigtot = 0;

	for(pigi = 1; pigi <= *pigcrypt; pigi++) {
	    pigarg = ++pigiter;
	    pigtot += pig_sigslot_exp_table[*pigcrypt - pigi] * pig_sigslot_typeidx(*pigarg);
	    pig_hash_table[pigi] = pig_signal_matrix[pigtot];
	}
    }

    QConnectionList *pigclist = ((pig_public_QObject *)pigobj)->getReceivers(pigproto);

    if(pigclist && !pigobj->signalsBlocked()) {
        QConnectionListIt pigit(*pigclist);
	QConnection *pigc;
	while((pigc = pigit.current())) {
	    ++pigit;
	    pig_signal_object = pigc->object();
	    pig_signal_member = pigc->member();
	    ((QSenderObject *)pig_signal_object)->setSender(pigobj);
	    (*pig_hash_table[pigc->numArgs()])();
	}
    }

    pig_return_nothing();
    PIG_END;
}

static XS(PIG_Qt__signals_emit) {
    dXSARGS;
    XSRETURN_EMPTY;
}

extern "C" XS(PIG_Qt__signals_import) {
    dXSARGS;
    STRLEN n_a;
    static const char pigname[] = ".signals";
    static const char pigmap[] = ".signalmap";
    static const char pigemit[] = "emit";

    const char *pigclass = HvNAME(PIGcurcop->cop_stash);

    if(items <= 1) XSRETURN_EMPTY;

    char *pigvar;
    pigvar = new char [strlen(pigclass) + 2 + strlen(pigname) + strlen(pigmap) + strlen(pigemit) + 1];

    sprintf(pigvar, "%s::%s", pigclass, pigemit);
    newXS((char *)pigvar, PIG_Qt__signals_emit, (char *)__FILE__);

    sprintf(pigvar, "%s::%s", pigclass, pigname);

    HV *pighv = perl_get_hv(pigvar, TRUE);

    sprintf(pigvar, "%s::%s", pigclass, pigmap);
    HV *pigmaphv = perl_get_hv(pigvar, TRUE);

    delete [] pigvar;

    I32 pigx;
    for(pigx = 1; pigx < items; pigx++) {
        SV *pigsv, *pigcryptsv;
	const char *pigproto, *pigcrypt;
	char *pignewxs;

	pigsv = pig_parse_proto(ST(pigx));
	pigcryptsv = pig_map_proto(pigsv);
	pigproto = SvPV(pigsv, n_a);
	pigcrypt = SvPV(pigcryptsv, n_a);
        hv_store(pighv, (char *)pigproto, SvCUR(pigsv), newSVsv(pigcryptsv), 0);
	hv_store(pigmaphv, (char *)pigcrypt + 2, strlen(pigcrypt + 2), newSVsv(pigsv), 0);

	pignewxs = new char [ strlen(pigclass) + 2 + strlen(pigcrypt + 2) + 1 ];
	sprintf(pignewxs, "%s::%s", pigclass, pigcrypt + 2);
//	printf("newxs %s\n", pignewxs);
	newXS((char *)pignewxs, (XS((*)))pig_signal_emit, (char *)__FILE__);
	delete [] pignewxs;
    }
}

extern "C" XS(PIG_Qt__slots_import) {
    dXSARGS;
    STRLEN n_a;
    static const char pigname[] = ".slots";

    const char *pigclass = HvNAME(PIGcurcop->cop_stash);

    if(items <= 1) XSRETURN_EMPTY;

    char *pigvar;
    pigvar = new char [strlen(pigclass) + 2 + strlen(pigname) + 1];
    sprintf(pigvar, "%s::%s", pigclass, pigname);

    HV *pighv = perl_get_hv(pigvar, TRUE);

    delete [] pigvar;

    I32 pigx;
    for(pigx = 1; pigx < items; pigx++) {
        SV *pigsv;
	pigsv = pig_parse_proto(ST(pigx));
        hv_store(pighv, SvPV(pigsv, n_a), SvCUR(pigsv), newSVsv(pig_map_proto(pigsv)), 0);
    }
}

