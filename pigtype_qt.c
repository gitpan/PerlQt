/*
 * Definition and export of types declared in pigtype_qt.h
 *
 * Copyright (C) 1999, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README.LICENSE file which should be included with this library.
 *
 */

#include "pigperl.h"
#include "pigtype_object.h"
#include "pigtype_qt.h"
#include "pigclassinfo.h"
#include <qobjectlist.h>
#include <qwidgetlist.h>

PIG_DEFINE_STUB_TYPE(pig_type_qt_serial, const char *)
PIG_DEFINE_STUB_TYPE(pig_type_qt_xpm, void *)
PIG_DEFINE_STUB_TYPE(pig_type_qt_bits, char *)
PIG_DEFINE_STUB_TYPE(pig_type_qt_bitslen, char *)
PIG_DEFINE_STUB_TYPE(pig_type_qt_ubits, uchar *)
PIG_DEFINE_STUB_TYPE(pig_type_qt_ubitsarray, uchar **)
PIG_DEFINE_STUB_TYPE(pig_type_qt_uintarray, uint **)
PIG_DEFINE_STUB_TYPE(pig_type_qt_VHorientation, int)
PIG_DEFINE_STUB_TYPE(pig_type_qt_QString_ref, class QString &)
PIG_DEFINE_STUB_TYPE(pig_type_qt_QByteArray_ptr, class QByteArray *)
PIG_DEFINE_STUB_TYPE(pig_type_qt_QArray_QRect_ptr, void *)
PIG_DEFINE_STUB_TYPE(pig_type_qt_QFileInfo_ptr, class QFileInfo *)
PIG_DEFINE_STUB_TYPE(pig_type_qt_QFileInfoList_ptr, class QFileInfoList *)
PIG_DEFINE_STUB_TYPE(pig_type_qt_QStrList_ptr, class QStrList *)
PIG_DEFINE_STUB_TYPE(pig_type_qt_QTabList_ptr, class QTabList *)

PIG_DEFINE_TYPE_ARGUMENT2(pig_type_qt_sender, class QObject *, int) {
    return (class QObject *)pig_type_object_argument("QObject");
}

PIG_DEFINE_TYPE_DEFARGUMENT2(pig_type_qt_sender, class QObject *, int) {
    return (class QObject *)pig_type_object_defargument((void *)pig0, "QObject");
}

PIG_DEFINE_STUB_RETURN(pig_type_qt_sender, class QObject *)
PIG_DEFINE_STUB_PUSH(pig_type_qt_sender, class QObject *)
PIG_DEFINE_STUB_POP(pig_type_qt_sender, class QObject *)


PIG_DEFINE_TYPE_ARGUMENT2(pig_type_qt_receiver, class QObject *, int) {
    PIGARGS;
    if(pig_receiver_defined(PIG_ARG, ST(pig0))) {
        QObject *pigr = pig_create_slot(PIG_ARG, ST(pig0));
        PIGARGUMENT(pigr);
    }
    return (class QObject *)pig_type_object_argument("QObject");
}

PIG_DEFINE_TYPE_DEFARGUMENT2(pig_type_qt_receiver, class QObject *, int) {
    PIGARGS;
    if(PIG_ARGOK && pig_receiver_defined(PIG_ARG, ST(pig1))) {
        QObject *pigr = pig_create_slot(PIG_ARG, ST(pig1));
        PIGARGUMENT(pigr);
    }
    return (class QObject *)pig_type_object_defargument(pig0, "QObject");
}

PIG_DEFINE_STUB_RETURN(pig_type_qt_receiver, class QObject *)
PIG_DEFINE_STUB_PUSH(pig_type_qt_receiver, class QObject *)
PIG_DEFINE_STUB_POP(pig_type_qt_receiver, class QObject *)


PIG_DEFINE_TYPE_ARGUMENT2(pig_type_qt_unreceiver, class QObject *, int) {
    return (class QObject *)pig_type_object_argument("QObject");
}

PIG_DEFINE_TYPE_DEFARGUMENT2(pig_type_qt_unreceiver, class QObject *, int) {
    return (class QObject *)pig_type_object_defargument((void *)pig0, "QObject");
}

PIG_DEFINE_STUB_RETURN(pig_type_qt_unreceiver, class QObject *)
PIG_DEFINE_STUB_PUSH(pig_type_qt_unreceiver, class QObject *)
PIG_DEFINE_STUB_POP(pig_type_qt_unreceiver, class QObject *)


PIG_DEFINE_TYPE_ARGUMENT2(pig_type_qt_signal, const char *, int) {
    PIGARGS;
    const char *pigr;
    if(!PIG_ARGOK) {
	PIGARGUMENT(0);
    } else if(pig0 < 0) {
        SV *pigsv = sv_2mortal(newSViv(SIGNAL_CODE));
	STRLEN n_a;
	sv_catsv(pigsv, PIG_ARG);
	pigr = SvPVX(pigsv);
    } else {
        pigr = pig_member_string(ST(pig0), PIG_ARG);
    }
    PIGARGUMENT(pigr);
}

PIG_DEFINE_TYPE_DEFARGUMENT2(pig_type_qt_signal, const char *, int) {
    PIGARGS;
    const char *pigr;
    if(!PIG_ARGOK) {
        pigr = pig0;
    } else if(pig0 < 0) {
        SV *pigsv = sv_2mortal(newSViv(SIGNAL_CODE));
	STRLEN n_a;
	sv_catsv(pigsv, PIG_ARG);
	pigr = SvPVX(pigsv);
    } else {
        pigr = pig_member_string(ST(pig1), PIG_ARG);
    }
    PIGARGUMENT(pigr);
}

PIG_DEFINE_STUB_RETURN(pig_type_qt_signal, const char *)

PIG_DEFINE_TYPE_PUSH(pig_type_qt_signal, const char *) {
    PIGPUSHSTACK;
    PIGPUSH(pig0 ? sv_2mortal(newSVpv((char *)pig0 + 1, 0)) : sv_mortalcopy(&PIGsv_undef));
}

PIG_DEFINE_STUB_POP(pig_type_qt_signal, const char *)


PIG_DEFINE_TYPE_ARGUMENT2(pig_type_qt_member, const char *, int) {
    PIGARGS;
    const char *pigr = pig_member_string(ST(pig0), PIG_ARG);
    PIGARGUMENT(pigr);
}

PIG_DEFINE_TYPE_DEFARGUMENT2(pig_type_qt_member, const char *, int) {
    PIGARGS;
    const char *pigr = PIG_ARGOK ? pig_member_string(ST(pig1), PIG_ARG) : pig0;
    PIGARGUMENT(pigr);
}

PIG_DEFINE_STUB_RETURN(pig_type_qt_member, const char *)
PIG_DEFINE_STUB_PUSH(pig_type_qt_member, const char *)
PIG_DEFINE_STUB_POP(pig_type_qt_member, const char *)


PIG_DEFINE_TYPE_ARGUMENT(pig_type_qt_HVorientation, int) {
    PIGARGS;
    int pigr = SvIV(PIG_ARG);
    PIGARGUMENT(pigr);
}

PIG_DEFINE_TYPE_DEFARGUMENT(pig_type_qt_HVorientation, int) {
    PIGARGS;
    int pigr = PIG_ARGOK ? SvIV(PIG_ARG) : pig0;
    PIGARGUMENT(pigr);
}

PIG_DEFINE_TYPE_RETURN(pig_type_qt_HVorientation, int) {
    PIGRET;
    PIGRETURN(sv_2mortal(newSViv(pig0)));
}

PIG_DEFINE_TYPE_PUSH(pig_type_qt_HVorientation, int) {
    PIGPUSHSTACK;
    PIGPUSH(sv_2mortal(newSViv(pig0)));
}

PIG_DEFINE_TYPE_POP(pig_type_qt_HVorientation, int) {
    PIGPOPSTACK;
    int pigr = SvIV(PIG_TOPSTACK);
    PIGPOP(pigr);
}


PIG_DEFINE_TYPE_ARGUMENT2(pig_type_qt_pointarrayitems, int, int) {
    PIGARGS;
    SV *pigarg = ST(pig0);
    if(!SvOK(pigarg) || !SvROK(pigarg) || SvTYPE(SvRV(pigarg)) != SVt_PVAV)
        return 0;

    // This does not move us to the next ST() argument
    return((av_len((AV *)SvRV(pigarg)) + 1) / 2);
}

PIG_DEFINE_STUB_DEFARGUMENT(pig_type_qt_pointarrayitems, int)
PIG_DEFINE_STUB_RETURN(pig_type_qt_pointarrayitems, int)
PIG_DEFINE_STUB_PUSH(pig_type_qt_pointarrayitems, int)
PIG_DEFINE_STUB_POP(pig_type_qt_pointarrayitems, int)


PIG_DEFINE_SCOPE_ARGUMENT(pig_type_qt_QString_ptr) {
    delete (QString *)pig0;
}

PIG_DEFINE_SCOPE_VIRTUAL(pig_type_qt_QString_ptr) {
    delete (QString *)pig0;
}

PIG_DEFINE_TYPE_ARGUMENT(pig_type_qt_QString_ptr, QString *) {
    PIGARGS;
    if(!SvOK(PIG_ARG)) {
        PIGARGUMENT(0);
    }
    STRLEN n_a;
    QString *pigr = new QString(SvPV(PIG_ARG, n_a));
    PIGSCOPE_ARGUMENT(pig_type_qt_QString_ptr, pigr);
    PIGARGUMENT(pigr);
}

PIG_DEFINE_TYPE_DEFARGUMENT(pig_type_qt_QString_ptr, QString *) {
    PIGARGS;
    QString *pigr;
    if(PIG_ARGOK) {
        STRLEN n_a;
        pigr = new QString(SvPV(PIG_ARG, n_a));
        PIGSCOPE_ARGUMENT(pig_type_qt_QString_ptr, pigr);
    }
    else pigr = pig0;
    PIGARGUMENT(pigr);
}

PIG_DEFINE_TYPE_RETURN(pig_type_qt_QString_ptr, QString *) {
    PIGRET;
    PIGRETURN(sv_2mortal(pig0 ?
			 newSVpv(pig0->data(), 0) :
			 newSVsv(&PIGsv_undef)));
}

PIG_DEFINE_STUB_PUSH(pig_type_qt_QString_ptr, QString *)

PIG_DEFINE_TYPE_POP(pig_type_qt_QString_ptr, QString *) {
    PIGPOPSTACK;
    QString *pigr;
    if(SvOK(PIG_TOPSTACK)) {
        STRLEN n_a;
        pigr = new QString(SvPV(PIG_TOPSTACK, n_a));
        PIGSCOPE_VIRTUAL(pig_type_qt_QString_ptr, pigr);
    }
    else pigr = 0;
    PIGPOP(pigr);
}


PIG_DEFINE_STUB_ARGUMENT(pig_type_qt_QObjectList_ptr, QObjectList *)
PIG_DEFINE_STUB_DEFARGUMENT(pig_type_qt_QObjectList_ptr, QObjectList *)
PIG_DEFINE_STUB_PUSH(pig_type_qt_QObjectList_ptr, QObjectList *)
PIG_DEFINE_STUB_POP(pig_type_qt_QObjectList_ptr, QObjectList *)

PIG_DEFINE_TYPE_RETURN(pig_type_qt_QObjectList_ptr, QObjectList *) {
    PIGRET;
    AV *pigav;
    if(!pig0) {
        PIGRETURN(sv_mortalcopy(&PIGsv_undef));
    }

    pigav = newAV();

    // FIXME
    // There should only be one instance of a Qt object in Perl at any
    // one time. This is creating duplicates...

    QObjectListIt pigobjit(*pig0);
    QObject *pigobj;
    SV *pigsv;
    pig_object_data *pigd;

    while(pigobjit.current()) {
        pigobj = pigobjit.current();
	pigsv = pig_object_create(pig_map_class(pigobj->className()), &pigd);
	pigd->pigptr = pigobj;
	pigd->piginfo = pig_classinfo_fetch("QObject");
	pigd->pigflags = 0;

	av_push(pigav, pigsv);

	++pigobjit;
    }

    pigsv = sv_2mortal(newRV((SV *)pigav));
    SvREFCNT_dec(pigav);
    PIGRETURN(pigsv);
}


PIG_DEFINE_STUB_ARGUMENT(pig_type_qt_QWidgetList_ptr, QWidgetList *)
PIG_DEFINE_STUB_DEFARGUMENT(pig_type_qt_QWidgetList_ptr, QWidgetList *)
PIG_DEFINE_STUB_PUSH(pig_type_qt_QWidgetList_ptr, QWidgetList *)
PIG_DEFINE_STUB_POP(pig_type_qt_QWidgetList_ptr, QWidgetList *)

PIG_DEFINE_TYPE_RETURN(pig_type_qt_QWidgetList_ptr, QWidgetList *) {
    PIGRET;
    AV *pigav;
    if(!pig0) {
        PIGRETURN(sv_mortalcopy(&PIGsv_undef));
    }

    pigav = newAV();

    // FIXME
    // There should only be one instance of a Qt object in Perl at any
    // one time. This is creating duplicates...

    QWidgetListIt pigobjit(*pig0);
    QWidget *pigobj;
    SV *pigsv;
    pig_object_data *pigd;

    while(pigobjit.current()) {
        pigobj = pigobjit.current();
	pigsv = pig_object_create(pig_map_class(pigobj->className()), &pigd);
	pigd->pigptr = pigobj;
	pigd->piginfo = pig_classinfo_fetch("QWidget");
	pigd->pigflags = 0;

	av_push(pigav, pigsv);

	++pigobjit;
    }

    pigsv = sv_2mortal(newRV((SV *)pigav));
    SvREFCNT_dec(pigav);
    PIGRETURN(pigsv);
}

PIG_DEFINE_TYPE(pig_type_qt_serial)
PIG_DEFINE_TYPE(pig_type_qt_sender)
PIG_DEFINE_TYPE(pig_type_qt_signal)
PIG_DEFINE_TYPE(pig_type_qt_receiver)
PIG_DEFINE_TYPE(pig_type_qt_unreceiver)
PIG_DEFINE_TYPE(pig_type_qt_member)
PIG_DEFINE_TYPE(pig_type_qt_xpm)
PIG_DEFINE_TYPE(pig_type_qt_bits)
PIG_DEFINE_TYPE(pig_type_qt_bitslen)
PIG_DEFINE_TYPE(pig_type_qt_ubits)
PIG_DEFINE_TYPE(pig_type_qt_ubitsarray)
PIG_DEFINE_TYPE(pig_type_qt_uintarray)
PIG_DEFINE_TYPE(pig_type_qt_pointarrayitems)
PIG_DEFINE_TYPE(pig_type_qt_HVorientation)
PIG_DEFINE_TYPE(pig_type_qt_VHorientation)
PIG_DEFINE_TYPE(pig_type_qt_QString_ptr)
PIG_DEFINE_TYPE(pig_type_qt_QString_ref)
PIG_DEFINE_TYPE(pig_type_qt_QByteArray_ptr)
PIG_DEFINE_TYPE(pig_type_qt_QArray_QRect_ptr)
PIG_DEFINE_TYPE(pig_type_qt_QFileInfo_ptr)
PIG_DEFINE_TYPE(pig_type_qt_QFileInfoList_ptr)
PIG_DEFINE_TYPE(pig_type_qt_QStrList_ptr)
PIG_DEFINE_TYPE(pig_type_qt_QTabList_ptr)
PIG_DEFINE_TYPE(pig_type_qt_QObjectList_ptr)
PIG_DEFINE_TYPE(pig_type_qt_QWidgetList_ptr)

PIG_EXPORT_TABLE(pigtype_qt)
    PIG_EXPORT_TYPE(pig_type_qt_serial, "Qt serial")
    PIG_EXPORT_TYPE(pig_type_qt_sender, "Qt sender")
    PIG_EXPORT_TYPE(pig_type_qt_signal, "Qt signal")
    PIG_EXPORT_TYPE(pig_type_qt_receiver, "Qt receiver")
    PIG_EXPORT_TYPE(pig_type_qt_unreceiver, "Qt unreceiver")
    PIG_EXPORT_TYPE(pig_type_qt_member, "Qt member")
    PIG_EXPORT_TYPE(pig_type_qt_xpm, "Qt xpm")
    PIG_EXPORT_TYPE(pig_type_qt_bits, "Qt bits")
    PIG_EXPORT_TYPE(pig_type_qt_bitslen, "Qt sizeof(bits)")
    PIG_EXPORT_TYPE(pig_type_qt_ubits, "Qt ubits")
    PIG_EXPORT_TYPE(pig_type_qt_ubitsarray, "Qt ubits[]")
    PIG_EXPORT_TYPE(pig_type_qt_uintarray, "Qt uint[]")
    PIG_EXPORT_TYPE(pig_type_qt_pointarrayitems, "Qt sizeof(point[])")
    PIG_EXPORT_TYPE(pig_type_qt_HVorientation, "Qt HVorientation")
    PIG_EXPORT_TYPE(pig_type_qt_VHorientation, "Qt VHorientation")
    PIG_EXPORT_TYPE(pig_type_qt_QString_ptr, "Qt QString*")
    PIG_EXPORT_TYPE(pig_type_qt_QString_ref, "Qt QString&")
    PIG_EXPORT_TYPE(pig_type_qt_QByteArray_ptr, "Qt QByteArray*")
    PIG_EXPORT_TYPE(pig_type_qt_QArray_QRect_ptr, "Qt QArray<QRect>*")
    PIG_EXPORT_TYPE(pig_type_qt_QFileInfo_ptr, "Qt QFileInfo*")
    PIG_EXPORT_TYPE(pig_type_qt_QFileInfoList_ptr, "Qt QFileInfoList*")
    PIG_EXPORT_TYPE(pig_type_qt_QStrList_ptr, "Qt QStrList*")
    PIG_EXPORT_TYPE(pig_type_qt_QTabList_ptr, "Qt QTabList*")
    PIG_EXPORT_TYPE(pig_type_qt_QObjectList_ptr, "Qt QObjectList*")
    PIG_EXPORT_TYPE(pig_type_qt_QWidgetList_ptr, "Qt QWidgetList*")
PIG_EXPORT_ENDTABLE
