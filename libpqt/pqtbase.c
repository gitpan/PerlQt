/*
 * Copyright (C) 1998, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 *
 */

#include "perlqt.h"
#include "sigslot.h"
#include "Qt/QApplication.h"

HV *pqt_autoload_hv = 0;
HV *pqt_loaded_hv = 0;
extern HV *pqthv_class_signals;
extern HV *pqthv_class_slots;

char *pqt_autoload = "::AUTOLOAD";

void pqt_hv_store(HV *pqt_hv, const char *pqt_key, SV *pqt_sv) {
    hv_store(pqt_hv, (char *)pqt_key, strlen(pqt_key), pqt_sv, 0);
}

SV *pqt_hv_fetch(HV *pqt_hv, const char *pqt_key) {
    SV **pqt_retsvp = hv_fetch(pqt_hv, (char *)pqt_key, strlen(pqt_key), 0);

    return pqt_retsvp ? *pqt_retsvp : &sv_undef;
}

bool pqt_hv_exists(HV *pqt_hv, const char *pqt_key) {
    return hv_exists(pqt_hv, (char *)pqt_key, strlen(pqt_key));
}

void pqt_hv_delete(HV *pqt_hv, const char *pqt_key) {
    hv_delete(pqt_hv, (char *)pqt_key, strlen(pqt_key), G_DISCARD);
}

SV *pqt_av_fetch(AV *pqt_av, I32 pqt_key) {
    SV **pqt_retsvp = av_fetch(pqt_av, pqt_key, 0);

    return pqt_retsvp ? *pqt_retsvp : &sv_undef;
}

void pqt_load_class(const char *pqt1) {
    if(!pqt_hv_exists(pqt_autoload_hv, pqt1)) {
//	printf("%s doesn't exist, or is already loaded\n", pqt1);
	return;
    }

    SV *pqt_sv = pqt_hv_fetch(pqt_autoload_hv, pqt1);
    if(SvOK(pqt_sv)) {
        pqt_hv_store(pqt_loaded_hv, pqt1, newSVsv(pqt_sv));

	pqt_classinfolist *pqt_info = (pqt_classinfolist *)SvIV(pqt_sv);
	pqt_struct_methodlist *pqt_list = pqt_info->pqt_methodlist;
	char *pqt_fullname = new char[1024];
	char *pqt_methname;
	strcpy(pqt_fullname, pqt1);
	strcat(pqt_fullname, "::");
	pqt_methname = pqt_fullname + strlen(pqt_fullname);

	while(pqt_list->pqt_method_name) {
	    strcpy(pqt_methname, pqt_list->pqt_method_name);
//	    printf("Looks like %s with %p\n", pqt_fullname, pqt_list->pqt_method_ptr);
	    newXS(pqt_fullname, (XS((*)))pqt_list->pqt_method_ptr, "pqtbase.c");
	    pqt_list++;
	}

	strcpy(pqt_methname, "ISA");
	AV *pqt_isaav = perl_get_av(pqt_fullname, TRUE);
	av_clear(pqt_isaav);    // It should already be clear, really

	const char **pqt_isa = pqt_info->pqt_isa;
	while(*pqt_isa) {
	    av_push(pqt_isaav, newSVpv((char *)*pqt_isa, 0));
	    pqt_load_class(*pqt_isa);
	    pqt_isa++;
	}

	*(pqt_methname - 2) = 0;	// lop off ::

	HV *pqt_stashhv = gv_stashpv(pqt_fullname, FALSE);
	pqt_hv_delete(pqt_stashhv, "AUTOLOAD");		// disable AUTOLOAD

	delete [] pqt_fullname;
    }
    pqt_hv_delete(pqt_autoload_hv, pqt1);
}

pqt_classinfolist *pqt_find_info(const char *pqt1) {
    if(!pqt_hv_exists(pqt_loaded_hv, pqt1))
	pqt_load_class(pqt1);

    SV *pqt_sv = pqt_hv_fetch(pqt_loaded_hv, pqt1);
    if(SvOK(pqt_sv)) {
        pqt_classinfolist *pqt_info = (pqt_classinfolist *)SvIV(pqt_sv);
	return pqt_info;
    }

//    printf("No %s, returning NULL\n", pqt1);
    return 0;
}

static XS(PQT_AUTOLOAD) {
    char *pqt_class = HvNAME(GvSTASH(CvGV(cv)));
    char *pqt_auto;
    pqt_auto = new char[strlen(pqt_autoload) + strlen(pqt_class) + 1];
    strcpy(pqt_auto, pqt_class);
    strcat(pqt_auto, pqt_autoload);
    char *pqt_method = SvPV(perl_get_sv(pqt_auto, TRUE), na);
    delete [] pqt_auto;

//    printf("AUTOLOAD for %s->%s\n", pqt_class, pqt_method);
    pqt_load_class(pqt_class);
//    printf("Good, it's done\n");

    perl_call_method(pqt_method, GIMME_V);	// goto &
}

static XS(PQT_parseproto) {
    dXSARGS;
    ST(0) = sv_2mortal(pqt_parse_proto(ST(0)));
    XSRETURN(1);
}

static void pqt_create_QApplication() {
    AV *pqtav_ARGV = perl_get_av("ARGV", FALSE);
    I32 pqtlen_ARGV = av_len(pqtav_ARGV);
    SV *pqtsv_ARGV0 = perl_get_sv("0", FALSE);
    int pqt_argc = 0;
    char **pqt_argv = 0;

    pqt_argv = new char *[ pqtlen_ARGV + 3 ];

    if(pqtsv_ARGV0 && SvOK(pqtsv_ARGV0)) {
        char *pqt_ARGV0 = SvPV(pqtsv_ARGV0, na);
        pqt_argv[pqt_argc] = new char [ strlen(pqt_ARGV0) + 1 ];
        strcpy(pqt_argv[pqt_argc], pqt_ARGV0);
    } else {
        const char *pqt_PerlQt = "PerlQt";
        pqt_argv[pqt_argc] = new char [ strlen(pqt_PerlQt) + 1 ];
        strcpy(pqt_argv[pqt_argc], pqt_PerlQt);
    }

    pqt_argc++;

    while(av_len(pqtav_ARGV) >= 0) {
        SV *pqtsv_arg = av_shift(pqtav_ARGV);
        if(!pqtsv_arg) continue;
        char *pqt_arg = SvPV(pqtsv_arg, na);
        pqt_argv[pqt_argc] = new char [ strlen(pqt_arg) + 1 ];
        strcpy(pqt_argv[pqt_argc], pqt_arg);

        pqt_argc++;
    }

    pqt_argv[pqt_argc] = 0;
    new pqt_enhanced_QApplication(pqt_argc, pqt_argv);
    pqt_argv = qApp->argv();

    av_clear(pqtav_ARGV);

    if(pqt_argc) {
        sv_setpv(pqtsv_ARGV0, *pqt_argv);
        pqt_argv++;
    }

    while(*pqt_argv) {
        av_push(pqtav_ARGV, newSVpv(*pqt_argv, 0));
        pqt_argv++;
    }
}

SV *pqt_gv_store(const char *pqtname, SV *pqtvalue) {
    register GV *pqt_gv = gv_fetchpv((char *)pqtname, TRUE | GV_ADDMULTI, SVt_PVGV);
    SvREFCNT_inc(pqtvalue);
    if(GvSV(pqt_gv)) SvREFCNT_dec(GvSV(pqt_gv));
//printf("$%s = %s\n", pqtname, SvPV(pqtvalue, na));
    GvSV(pqt_gv) = pqtvalue;
    return pqtvalue;
}

HV *pqt_gv_store(const char *pqtname, HV *pqtvalue) {
    register GV *pqt_gv = gv_fetchpv((char *)pqtname, TRUE | GV_ADDMULTI, SVt_PVGV);
    SvREFCNT_inc(pqtvalue);
    if(GvHV(pqt_gv)) SvREFCNT_dec(GvHV(pqt_gv));
    GvHV(pqt_gv) = pqtvalue;
    return pqtvalue;
}

class pqt_cheat_QObject : public QObject {
public:
    void doInitMetaObject() { this->initMetaObject(); }
    QConnectionList *getReceivers(const char *pqt1) { return this->receivers(pqt1); }
};

SV *pqt_global_app = 0;
HV *pqthv_export_list = 0;
HV *pqthv_export_data = 0;

static void pqt_export_app(const char *pqt_caller) {
    if(!pqt_global_app) {
	pqt_object_data *pqtdata;
	pqt_global_app = pqt_create_object("QApplication", pqtdata);
	pqtdata->pqtinfo = pqt_find_info("QApplication");

        if(!qApp) {
	    pqt_create_QApplication();
	    pqtdata->pqtptr = (void *)qApp;
	    pqtdata->pqtflags = PQTOBJ_NEW | PQTOBJ_MUTABLE;
	    pqt_virtual *pqtv =
	      (pqt_virtual *)(*pqtdata->pqtinfo->pqt_tocastfunc)("virtual", qApp);
	    if(pqtv) pqtv->pqt_object(pqt_global_app);
	    if(!qApp->metaObject())
	        ((pqt_cheat_QObject *)(QObject *)qApp)->doInitMetaObject();
	} else {
	    pqtdata->pqtptr = (void *)qApp;
	    pqtdata->pqtflags = PQTOBJ_MUTABLE;
	}
    }

    char *pqt_dest = new char [ strlen(pqt_caller) + 6 ];
    strcpy(pqt_dest, pqt_caller);
    strcat(pqt_dest, "::app");
    pqt_gv_store(pqt_dest, pqt_global_app);
    delete [] pqt_dest;
}

static XS(PQT_import) {
    dXSARGS;
    HV *pqt_hvstash = curcop->cop_stash;
    const char *pqt_caller = HvNAME(pqt_hvstash);

    if(items == 1) {
        pqt_export_app(pqt_caller);
	XSRETURN_EMPTY;
    }

    int pqti;

    for(pqti = 1; pqti < items; pqti++) {
        const char *pqt_export = SvPV(ST(pqti), na);
	if(!pqt_hv_exists(pqthv_export_data, pqt_export) &&
	    pqt_hv_exists(pqthv_export_list, pqt_export)) {
	    pqt_exportinfolist *pqt_info =
	        (pqt_exportinfolist *)SvIV(pqt_hv_fetch(pqthv_export_list, pqt_export));
	    pqt_struct_constantdata *pqt_data = pqt_info->pqt_constantdata;

	    HV *pqt_newhv = newHV();
	    SV *pqt_newsv;
	    while(pqt_data->pqt_constant) {
	        pqt_newsv = newSViv(pqt_data->pqt_value);
		SvREADONLY_on(pqt_newsv);
	        pqt_hv_store(pqt_newhv, pqt_data->pqt_constant, pqt_newsv);
//		warn("$%s{'%s'} = 0x%x (%d)\n", pqt_export + 1, pqt_data->pqt_constant, pqt_data->pqt_value, pqt_data->pqt_value);
		pqt_data++;
	    }

	    SvREADONLY_on((SV *)pqt_newhv);
	    pqt_hv_delete(pqthv_export_list, pqt_export);
	    pqt_hv_store(pqthv_export_data, pqt_export, newRV((SV *)pqt_newhv));
	}
	if(pqt_hv_exists(pqthv_export_data, pqt_export)) {
	    HV *pqt_hv = (HV *)SvRV(pqt_hv_fetch(pqthv_export_data, pqt_export));
	    char *pqt_dest = new char [ strlen(pqt_caller) + strlen(pqt_export) + 2 ];
	    sprintf(pqt_dest, "%s::%s", pqt_caller, pqt_export + 1);
	    pqt_gv_store(pqt_dest, pqt_hv);
	    delete [] pqt_dest;
	} else if(!strcmp(pqt_export, "$app")) {
	    pqt_export_app(pqt_caller);
	} else {
	    warn("Cannot find %s for export\n", pqt_export);
	}
    }

    XSRETURN_EMPTY;
}

void pqt_pop_signal_arguments(const char *);

const char *pqt_find_proto(const char *pqtclass, const char *pqtname) {
    if(!pqt_hv_exists(pqthv_class_signals, pqtclass))
        die("No signals in %s\n", pqtclass);
    HV *pqthv = (HV *)SvRV(pqt_hv_fetch(pqthv_class_signals, pqtclass));
    if(!pqt_hv_exists(pqthv, pqtname))
        die("No signal named %s in %s\n", pqtname, pqtclass);
//printf("Finding %s::%s\n", pqtclass, pqtname);
    SV *pqtsv = pqt_hv_fetch(pqthv, pqtname);
//printf("Found %s::%s\n", pqtclass, SvPVX(pqtsv));
    return SvPV(pqtsv, na);
}

#ifdef emit
#undef emit
#endif

extern QObject *pqt_signal_object;
extern QMember *pqt_signal_member;
extern int pqt_exp_table[];
int pqt_typeidx(char);

static PQT_PROTO(emit) {
    PQT_BEGIN(emit);
    const char *pqt_stashname = HvNAME(GvSTASH(CvGV((CV *)pqtCV)));
    const char *pqt_funcname = GvNAME(CvGV((CV *)pqtCV));
    const char *pqt_proto = pqt_find_proto(pqt_stashname, pqt_funcname);
    const char *pqt_crypt = SvPVX(pqt_hv_fetch(pqt_map_crypt, pqt_proto));

    QObject *pqt0 = (QObject *)pqt_argument_class("QObject");
    pqt_pop_signal_arguments(pqt_crypt);
    PQT_END_ARGUMENTS;


    pqt_signal pqt_hash_table[PQT_PROTO_MAX_ARGUMENT_COUNT + 1];
    pqt_hash_table[0] = pqt_signal_matrix[0];

    {
        pqt_argument_iterator pqtargit(pqt_crypt);
	const char *pqtarg;
	int pqttot = 0;
	int pqti;
	for(pqti = 1; pqti <= *pqt_crypt; pqti++) {
            pqtarg = ++pqtargit;
	    pqttot += pqt_exp_table[ *pqt_crypt - pqti ] * pqt_typeidx(*pqtarg);
//printf("%d is %d\n", pqti, pqttot);
	    pqt_hash_table[pqti] = pqt_signal_matrix[pqttot];
	}
    }
    
    QConnectionList *pqt_clist = ((pqt_cheat_QObject *)pqt0)->getReceivers(pqt_proto);
//printf("Receivers: %p\n", pqt_clist);

    if(pqt_clist && !pqt0->signalsBlocked()) {
        QConnectionListIt pqt_it(*pqt_clist);
	QConnection *pqt_c;
	while((pqt_c = pqt_it.current())) {
	    ++pqt_it;
	    pqt_signal_object = pqt_c->object();
	    pqt_signal_member = pqt_c->member();
	    ((QSenderObject *)pqt_signal_object)->setSender(pqt0);
	    (*pqt_hash_table[pqt_c->numArgs()])();
	}
    }
    pqt_return_nothing();
    PQT_END;
}

static XS(PQT_signals_emit) {
    dXSARGS;
    XSRETURN_EMPTY;
}

static XS(PQT_signals_import) {
    dXSARGS;
    HV *pqt_hvstash = curcop->cop_stash;
    const char *pqt_caller = HvNAME(pqt_hvstash);

//printf("Importing signal to %s\n", pqt_caller);

//HV *pqthv_class_signals = 0;
//HV *pqthv_class_slots = 0;

    HV *pqt_signals;
    if(pqt_hv_exists(pqthv_class_signals, pqt_caller)) {
        SV *pqtrv_signals = pqt_hv_fetch(pqthv_class_signals, pqt_caller);
	if(SvROK(pqtrv_signals))
	    pqt_signals = (HV *)SvRV(pqtrv_signals);
	else
	    pqt_hv_delete(pqthv_class_signals, pqt_caller);
    } // FALL THROUGH
    if(!pqt_hv_exists(pqthv_class_signals, pqt_caller)) {
        pqt_signals = newHV();
	pqt_hv_store(pqthv_class_signals, pqt_caller, newRV((SV *)pqt_signals));
	SvREFCNT_dec(pqt_signals);
    }

    SV *pqt_proto, *pqt_crypt;
    int pqti;
    for(pqti = 1; pqti < items; pqti++) {
        pqt_proto = pqt_parse_proto(ST(pqti));
	pqt_hv_store(pqt_signals, SvPVX(pqt_proto), pqt_proto);

	char *pqt_name = new char [ SvCUR(pqt_proto) + strlen(pqt_caller) + 3 ];
	strcpy(pqt_name, pqt_caller);
	strcat(pqt_name, "::");
	strcat(pqt_name, SvPVX(pqt_proto));
	*(strchr(pqt_name, '(')) = 0;
//	printf("Looking at \"%s\" and \"%s\"\n", pqt_name, pqt_name + strlen(pqt_caller) + 2);

	newXS(pqt_name, (XS((*)))PQT_PROTONAME(emit), "pqtbase.c");

	SvREFCNT_inc(pqt_proto);
	pqt_hv_store(pqt_signals, pqt_name + strlen(pqt_caller) + 2, pqt_proto);

	delete [] pqt_name;

//	printf("{ package %s; use signal %s => %s }\n", pqt_caller, SvPV(ST(pqti), na), SvPVX(pqt_proto));
    }

    XSRETURN_EMPTY;
}

static XS(PQT_signals_unimport) {
    HV *pqt_hvstash = curcop->cop_stash;
    const char *pqt_caller = HvNAME(pqt_hvstash);

printf("Unimporting signal from %s\n", pqt_caller);
}

static XS(PQT_slots_import) {
    dXSARGS;
    HV *pqt_hvstash = curcop->cop_stash;
    const char *pqt_caller = HvNAME(pqt_hvstash);

//printf("Importing slot to %s\n", pqt_caller);

    HV *pqt_slots;
    if(pqt_hv_exists(pqthv_class_slots, pqt_caller)) {
        SV *pqtrv_slots = pqt_hv_fetch(pqthv_class_slots, pqt_caller);
	if(SvROK(pqtrv_slots))
	    pqt_slots = (HV *)SvRV(pqtrv_slots);
	else
	    pqt_hv_delete(pqthv_class_slots, pqt_caller);
    } // FALL THROUGH
    if(!pqt_hv_exists(pqthv_class_slots, pqt_caller)) {
        pqt_slots = newHV();
	pqt_hv_store(pqthv_class_slots, pqt_caller, newRV((SV *)pqt_slots));
	SvREFCNT_dec(pqt_slots);
    }

    SV *pqt_proto;
    int pqti;
    for(pqti = 1; pqti < items; pqti++) {
        pqt_proto = pqt_parse_proto(ST(pqti));
	pqt_hv_store(pqt_slots, SvPVX(pqt_proto), pqt_proto);

	char *pqt_name = new char [ SvCUR(pqt_proto) + 1 ];
	strcpy(pqt_name, SvPVX(pqt_proto));
	*(strchr(pqt_name, '(')) = 0;

//	printf("Storing name %s\n", pqt_name);

	SvREFCNT_inc(pqt_proto);
	pqt_hv_store(pqt_slots, pqt_name, pqt_proto);

	delete [] pqt_name;
    }
    XSRETURN_EMPTY;
}

static XS(PQT_slots_unimport) {
    HV *pqt_hvstash = curcop->cop_stash;
    const char *pqt_caller = HvNAME(pqt_hvstash);

printf("Unimporting slot from %s\n", pqt_caller);
}


pqt_object_data pqt__data;

static void pqt_init_global_data() {
    pqt__data.pqtptr = 0;
    pqt__data.pqtinfo = 0;
    pqt__data.pqtflags = 0;

    if(!pqt_autoload_hv) pqt_autoload_hv = newHV();
    if(!pqt_loaded_hv) pqt_loaded_hv = newHV();
    if(!pqthv_export_list) pqthv_export_list = newHV();
    if(!pqthv_export_data) pqthv_export_data = newHV();
    if(!pqthv_class_signals) pqthv_class_signals = newHV();
    if(!pqthv_class_slots) pqthv_class_slots = newHV();

    if(!pqt_hv_exists(gv_stashpv("signals", TRUE), "import")) {
        newXS("signals::import", PQT_signals_import, "pqtbase.c");
        newXS("signals::unimport", PQT_signals_unimport, "pqtbase.c");

	// $INC{'signals.pm'} = 'pqtbase.c'
	pqt_hv_store(perl_get_hv("main::INC", TRUE),
		     "signals.pm",
		     newSVpv("pqtbase.c", 0));
    }

    if(!pqt_hv_exists(gv_stashpv("slots", TRUE), "import")) {
        newXS("slots::import", PQT_slots_import, "pqtbase.c");
        newXS("slots::unimport", PQT_slots_unimport, "pqtbase.c");

	// $INC{'slots.pm'} = 'pqtbase.c'
	pqt_hv_store(perl_get_hv("main::INC", TRUE),
		     "slots.pm",
		     newSVpv("pqtbase.c", 0));
    }
}


void pqt_load_module(const char *pqt1, pqt_classinfolist *pqt2, pqt_exportinfolist *pqt3) {
    pqt_init_global_data();

    char *pqt_mem = new char [1024];

//    newXS("main::parseproto", PQT_parseproto, "pqtbase.c");

//    PerlIO_printf(PerlIO_stdout(), "Successful loading of %s with %p and %p\n", pqt1, pqt2, pqt3);
    while(pqt2->pqt_classname) {
        pqt_struct_methodlist *pqt_list = pqt2->pqt_methodlist;
	strcpy(pqt_mem, pqt2->pqt_classname);
	strcat(pqt_mem, pqt_autoload);
//	printf("Looks like %s (%p)\n", pqt_mem);
	newXS(pqt_mem, PQT_AUTOLOAD, "pqtbase.c");

	pqt_hv_store(pqt_autoload_hv, pqt2->pqt_classname, newSViv((IV)pqt2));

	pqt2++;
    }

    strcpy(pqt_mem, pqt1);
    strcat(pqt_mem, "::import");
    newXS(pqt_mem, PQT_import, "pqtbase.c");

    delete [] pqt_mem;

    while(pqt3->pqt_hashname) {
        pqt_hv_store(pqthv_export_list, pqt3->pqt_hashname, newSViv((IV)pqt3));
	pqt3++;
    }

    /*
    char *pqt_argv[] = { "PerlQt", 0 };
    int pqt_argc = 1;

    pqt_object_data *pqtdata;
    sv_setsv(perl_get_sv("::app", TRUE), pqt_create_object("QApplication", pqtdata));
    pqtdata->pqtptr = new QApplication(pqt_argc, pqt_argv);
    pqtdata->pqtinfo = pqt_find_info("QApplication");
    pqtdata->pqtflags = PQTOBJ_NEW | PQTOBJ_DURABLE | PQTOBJ_MUTABLE;
    */
}


/*
	pqt_struct_methodlist *pqt_list = pqt2->pqt_methodlist;
	const char **pqt_isa = pqt2->pqt_isa;
	PerlIO_printf(PerlIO_stdout(), "Loading %s... (", pqt2->pqt_classname);

	while(pqt_isa && *pqt_isa) {
	    PerlIO_printf(PerlIO_stdout(), "%s%s", (pqt_isa > pqt2->pqt_isa) ? ", " : "", *pqt_isa);
	    pqt_isa++;
	}
	PerlIO_printf(PerlIO_stdout(), ")\n");
	while(pqt_list->pqt_method_name) {
	    PerlIO_printf(PerlIO_stdout(), "Installing %s with %p.\n", pqt_list->pqt_method_name, pqt_list->pqt_method_ptr);
	    pqt_list++;
	}
	pqt2++;
*/



int pqt_find_in_array(const char *pqt1, const char **pqt2) {
    int pqt_idx = 0;
    int pqt_cur = 0;

    while(pqt2[pqt_idx]) {
        while(pqt2[pqt_idx][pqt_cur] == pqt1[pqt_cur]) {
	    if(!pqt1[pqt_cur]) {
//	        printf("Found %s at %d\n", pqt1, pqt_idx);
	        return pqt_idx;
	    }
	    pqt_cur++;
	}
	pqt_cur = 0;
        pqt_idx++;
    }

    return -1;
}
