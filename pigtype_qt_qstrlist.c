#include "pig.h"
#include <qstrlist.h>
#include "pigperl.h"
#include "pigtype_qt.h"

static SV *_pig_extract_QStrList(const QStrList &piglist) {
    AV *pigav = newAV();
    SV *pigr = newRV((SV *)pigav);
    SvREFCNT_dec(pigav);
    QStrListIterator piglistit(piglist);
    for(; piglistit.current(); ++piglistit)
	av_push(pigav, newSVpv(piglistit.current(), 0));
    return pigr;
}

static QStrList *_pig_create_QStrList(AV *pigav) {
    I32 pigcnt = av_len(pigav) + 1;
    I32 pigi;
    STRLEN n_a;
    QStrList *pigr = new QStrList;

    for(pigi = 0; pigi < pigcnt; pigi++) {
        SV **pigsvp = av_fetch(pigav, pigi, 0);
        if(pigsvp) {
	    const char *pigdata = SvPV(*pigsvp, n_a);
	    if(pigdata)
		pigr->append(pigdata);
	}
    }

    return pigr;
}

PIG_DEFINE_SCOPE_ARGUMENT(pig_type_qt_QStrList_ptr) {
    delete (QStrList *)pig0;
}

PIG_DEFINE_SCOPE_VIRTUAL(pig_type_qt_QStrList_ptr) {
    delete (QStrList *)pig0;
}

PIG_DEFINE_TYPE_ARGUMENT(pig_type_qt_QStrList_ptr, class QStrList *) {
    PIGARGS;
    if(!SvOK(PIG_ARG) || !SvROK(PIG_ARG) || SvTYPE(SvRV(PIG_ARG)) != SVt_PVAV)
        PIGARGUMENT(0);

    QStrList *pigr = _pig_create_QStrList((AV *)SvRV(PIG_ARG));

    PIGSCOPE_ARGUMENT(pig_type_qt_QStrList_ptr, pigr);
    PIGARGUMENT(pigr);
}

PIG_DEFINE_TYPE_DEFARGUMENT(pig_type_qt_QStrList_ptr, class QStrList *) {
    PIGARGS;
    if(!PIG_ARGOK)
	PIGARGUMENT(pig0);
    if(!SvOK(PIG_ARG) || !SvROK(PIG_ARG) || SvTYPE(SvRV(PIG_ARG)) != SVt_PVAV)
	PIGARGUMENT(0);

    QStrList *pigr = _pig_create_QStrList((AV *)SvRV(PIG_ARG));

    PIGSCOPE_ARGUMENT(pig_type_qt_QStrList_ptr, pigr);
    PIGARGUMENT(pigr);
}

PIG_DEFINE_TYPE_RETURN(pig_type_qt_QStrList_ptr, class QStrList *) {
    PIGRET;
    PIGRETURN(pig0 ?
	      sv_2mortal(_pig_extract_QStrList(*pig0)) :
	      sv_mortalcopy(&PIGsv_undef));
}

PIG_DEFINE_TYPE_PUSH(pig_type_qt_QStrList_ptr, class QStrList *) {
    PIGPUSHSTACK;
    PIGPUSH(pig0 ?
	    sv_2mortal(_pig_extract_QStrList(*pig0)) :
	    sv_mortalcopy(&PIGsv_undef));
}

PIG_DEFINE_TYPE_POP(pig_type_qt_QStrList_ptr, class QStrList *) {
    PIGPOPSTACK;
    SV *pigsv = PIG_TOPSTACK;
    if(!SvOK(pigsv) || !SvROK(pigsv) || SvTYPE(SvRV(pigsv)) != SVt_PVAV)
        PIGPOP(0);

    QStrList *pigr = _pig_create_QStrList((AV *)SvRV(pigsv));

    PIGSCOPE_VIRTUAL(pig_type_qt_QStrList_ptr, pigr);
    PIGPOP(pigr);
}


PIG_DEFINE_TYPE_ARGUMENT(pig_type_qt_leak_QStrList_ptr, class QStrList *) {
    PIGARGS;
    if(!SvOK(PIG_ARG) || !SvROK(PIG_ARG) || SvTYPE(SvRV(PIG_ARG)) != SVt_PVAV)
        PIGARGUMENT(0);
    AV *pigav = (AV *)SvRV(PIG_ARG);
    QStrList *pigr = _pig_create_QStrList(pigav);

    //    PIGSCOPE_ARGUMENT(pig_type_qt_QStrList_ptr, pigr);
    PIGARGUMENT(pigr);
}

PIG_DEFINE_TYPE_DEFARGUMENT(pig_type_qt_leak_QStrList_ptr, class QStrList *) {
    PIGARGS;
    if(!PIG_ARGOK)
	PIGARGUMENT(pig0);
    if(!SvOK(PIG_ARG) || !SvROK(PIG_ARG) || SvTYPE(SvRV(PIG_ARG)) != SVt_PVAV)
	PIGARGUMENT(0);

    AV *pigav = (AV *)SvRV(PIG_ARG);
    QStrList *pigr = _pig_create_QStrList(pigav);

    //    PIGSCOPE_ARGUMENT(pig_type_qt_QStrList_ptr, pigr);
    PIGARGUMENT(pigr);
}

PIG_DEFINE_STUB_RETURN(pig_type_qt_leak_QStrList_ptr, class QStrList *)
PIG_DEFINE_STUB_PUSH(pig_type_qt_leak_QStrList_ptr, class QStrList *)

PIG_DEFINE_TYPE_POP(pig_type_qt_leak_QStrList_ptr, class QStrList *) {
    PIGPOPSTACK;
    SV *pigsv = PIG_TOPSTACK;
    if(!SvOK(pigsv) || !SvROK(pigsv) || SvTYPE(SvRV(pigsv)) != SVt_PVAV)
        PIGPOP(0);

    QStrList *pigr = _pig_create_QStrList((AV *)SvRV(pigsv));

    //    PIGSCOPE_VIRTUAL(pig_type_qt_QStrList_ptr, pigr);
    PIGPOP(pigr);
}


PIG_DEFINE_TYPE(pig_type_qt_QStrList_ptr)
PIG_DEFINE_TYPE(pig_type_qt_leak_QStrList_ptr)

PIG_EXPORT_TABLE(pigtype_qt_QStrList)
    PIG_EXPORT_TYPE(pig_type_qt_QStrList_ptr, "Qt QStrList*")
    PIG_EXPORT_TYPE(pig_type_qt_leak_QStrList_ptr, "Qt new QStrList*")
PIG_EXPORT_ENDTABLE
