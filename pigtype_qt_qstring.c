#include "pigperl.h"
#include "pigtype_qt.h"
#include <qstring.h>
#if QT_VERSION > 200
#include <qcstring.h>
#endif

struct _pig_QString {
    _pig_QString(QString *pig0, SV *pig1) :
        pigptr(pig0), pigsv(pig1) {}
    ~_pig_QString() {
        if(pigptr->isNull())
	    sv_setsv(pigsv, &PIGsv_undef);
	else
	    sv_setpv(pigsv, (char *)pigptr->data());
	delete pigptr;
    }
    QString *pigptr;
    SV *pigsv;
};

PIG_DEFINE_SCOPE_ARGUMENT(pig_type_qt_QString) {
    delete (QString *)pig0;
}

PIG_DEFINE_SCOPE_VIRTUAL(pig_type_qt_QString) {
    delete (QString *)pig0;
}

PIG_DEFINE_TYPE_ARGUMENT(pig_type_qt_QString, QString &) {
    PIGARGS;
    QString *pigr = new QString;
    if(SvOK(PIG_ARG)) {
	STRLEN n_a;
	*pigr = QString(SvPV(PIG_ARG, n_a));
    }
    PIGSCOPE_ARGUMENT(pig_type_qt_QString, pigr);
    PIGARGUMENT(*pigr);
}

PIG_DEFINE_TYPE_DEFARGUMENT(pig_type_qt_QString, QString &) {
    PIGARGS;
    QString *pigr = new QString(pig0);
    if(PIG_ARGOK) {
        STRLEN n_a;
        *pigr = QString(SvPV(PIG_ARG, n_a));
    }
    PIGSCOPE_ARGUMENT(pig_type_qt_QString, pigr);
    PIGARGUMENT(*pigr);
}

PIG_DEFINE_TYPE_RETURN(pig_type_qt_QString, QString &) {
    PIGRET;
    PIGRETURN(sv_2mortal(!pig0.isNull() ?
                         newSVpv((char *)pig0.data(), 0) :
                         newSVsv(&PIGsv_undef)));
}

PIG_DEFINE_TYPE_PUSH(pig_type_qt_QString, QString &) {
    PIGPUSHSTACK;
    PIGPUSH(sv_2mortal(!pig0.isNull() ?
		       newSVpv((char *)pig0.data(), 0) :
		       newSVsv(&PIGsv_undef)));
}

PIG_DEFINE_TYPE_POP(pig_type_qt_QString, QString &) {
    PIGPOPSTACK;
    QString *pigr = new QString;
    if(SvOK(PIG_TOPSTACK)) {
        STRLEN n_a;
        *pigr = QString(SvPV(PIG_TOPSTACK, n_a));
    }
    PIGSCOPE_VIRTUAL(pig_type_qt_QString, pigr);
    PIGPOP(*pigr);
}


PIG_DEFINE_SCOPE_ARGUMENT(pig_type_qt_QString_ref) {
    delete (_pig_QString *)pig0;
}

PIG_DEFINE_SCOPE_VIRTUAL(pig_type_qt_QString_ref) {
    delete (_pig_QString *)pig0;
}

PIG_DEFINE_TYPE_ARGUMENT(pig_type_qt_QString_ref, QString &) {
    PIGARGS;
    QString *pigr = new QString;
    if(SvOK(PIG_ARG)) {
	STRLEN n_a;
	*pigr = QString(SvPV(PIG_ARG, n_a));
    }
    PIGSCOPE_ARGUMENT(pig_type_qt_QString_ref,
		      new _pig_QString(pigr, PIG_ARG));
    PIGARGUMENT(*pigr);
}

PIG_DEFINE_TYPE_DEFARGUMENT(pig_type_qt_QString_ref, QString &) {
    PIGARGS;
    QString *pigr = new QString(pig0);
    if(PIG_ARGOK) {
        STRLEN n_a;
        *pigr = QString(SvPV(PIG_ARG, n_a));
	PIGSCOPE_ARGUMENT(pig_type_qt_QString_ref,
			  new _pig_QString(pigr, PIG_ARG));
    }
    else {
        PIGSCOPE_ARGUMENT(pig_type_qt_QString, pigr);
    }
    PIGARGUMENT(*pigr);
}

PIG_DEFINE_TYPE_RETURN(pig_type_qt_QString_ref, QString &) {
    PIGRET;
    PIGRETURN(sv_2mortal(!pig0.isNull() ?
                         newSVpv((char *)pig0.data(), 0) :
                         newSVsv(&PIGsv_undef)));
}

PIG_DEFINE_TYPE_PUSH(pig_type_qt_QString_ref, QString &) {
    PIGPUSHSTACK;
    PIGPUSH(sv_2mortal(!pig0.isNull() ?
		       newSVpv((char *)pig0.data(), 0) :
		       newSVsv(&PIGsv_undef)));
}

PIG_DEFINE_TYPE_POP(pig_type_qt_QString_ref, QString &) {
    PIGPOPSTACK;
    QString *pigr = new QString;
    if(SvOK(PIG_TOPSTACK)) {
        STRLEN n_a;
        *pigr = QString(SvPV(PIG_TOPSTACK, n_a));
    }
    PIGSCOPE_VIRTUAL(pig_type_qt_QString_ref,
		     new _pig_QString(pigr, PIG_TOPSTACK));
    PIGPOP(*pigr);
}


PIG_DEFINE_SCOPE_ARGUMENT(pig_type_qt_QString_ptr) {
    delete (_pig_QString *)pig0;
}

PIG_DEFINE_SCOPE_VIRTUAL(pig_type_qt_QString_ptr) {
    delete (_pig_QString *)pig0;
}

PIG_DEFINE_TYPE_ARGUMENT(pig_type_qt_QString_ptr, QString *) {
    PIGARGS;
    if(!SvOK(PIG_ARG)) {
        PIGARGUMENT(0);
    }
    STRLEN n_a;
    QString *pigr = new QString(SvPV(PIG_ARG, n_a));
    PIGSCOPE_ARGUMENT(pig_type_qt_QString_ptr,
		      new _pig_QString(pigr, PIG_ARG));
    PIGARGUMENT(pigr);
}

PIG_DEFINE_TYPE_DEFARGUMENT(pig_type_qt_QString_ptr, QString *) {
    PIGARGS;
    QString *pigr = pig0;
    if(PIG_ARGOK) {
        STRLEN n_a;
        pigr = new QString(SvPV(PIG_ARG, n_a));
        PIGSCOPE_ARGUMENT(pig_type_qt_QString_ptr, 
			  new _pig_QString(pigr, PIG_ARG));
    }
    PIGARGUMENT(pigr);
}

PIG_DEFINE_TYPE_RETURN(pig_type_qt_QString_ptr, QString *) {
    PIGRET;
    PIGRETURN(sv_2mortal(pig0 && !pig0->isNull() ?
			 newSVpv((char *)pig0->data(), 0) :
			 newSVsv(&PIGsv_undef)));
}

PIG_DEFINE_TYPE_PUSH(pig_type_qt_QString_ptr, QString *) {
    PIGPUSHSTACK;
    PIGPUSH(sv_2mortal(pig0 && !pig0->isNull() ?
		       newSVpv((char *)pig0->data(), 0) :
		       newSVsv(&PIGsv_undef)));
}

PIG_DEFINE_TYPE_POP(pig_type_qt_QString_ptr, QString *) {
    PIGPOPSTACK;
    QString *pigr = 0;
    if(SvOK(PIG_TOPSTACK)) {
        STRLEN n_a;
        pigr = new QString(SvPV(PIG_TOPSTACK, n_a));
        PIGSCOPE_VIRTUAL(pig_type_qt_QString_ptr, 
			 new _pig_QString(pigr, PIG_TOPSTACK));
    }
    PIGPOP(pigr);
}


PIG_DEFINE_SCOPE_ARGUMENT(pig_type_qt_const_QString_ref) {
    delete (QString *)pig0;
}

PIG_DEFINE_SCOPE_VIRTUAL(pig_type_qt_const_QString_ref) {
    delete (QString *)pig0;
}

PIG_DEFINE_TYPE_ARGUMENT(pig_type_qt_const_QString_ref, const QString &) {
    PIGARGS;
    QString *pigr = new QString;
    if(SvOK(PIG_ARG)) {
	STRLEN n_a;
	*pigr = QString(SvPV(PIG_ARG, n_a));
    }
    PIGSCOPE_ARGUMENT(pig_type_qt_const_QString_ref, pigr);
    PIGARGUMENT(*pigr);
}

PIG_DEFINE_TYPE_DEFARGUMENT(pig_type_qt_const_QString_ref, const QString &) {
    PIGARGS;
    QString *pigr = new QString(pig0);
    if(PIG_ARGOK) {
        STRLEN n_a;
        *pigr = QString(SvPV(PIG_ARG, n_a));
    }
    PIGSCOPE_ARGUMENT(pig_type_qt_const_QString_ref, pigr);
    PIGARGUMENT(*pigr);
}

PIG_DEFINE_TYPE_RETURN(pig_type_qt_const_QString_ref, const QString &) {
    PIGRET;
    PIGRETURN(sv_2mortal(!pig0.isNull() ?
                         newSVpv((char *)pig0.data(), 0) :
                         newSVsv(&PIGsv_undef)));
}

PIG_DEFINE_TYPE_PUSH(pig_type_qt_const_QString_ref, const QString &) {
    PIGPUSHSTACK;
    PIGPUSH(sv_2mortal(!pig0.isNull() ?
		       newSVpv((char *)pig0.data(), 0) :
		       newSVsv(&PIGsv_undef)));
}

PIG_DEFINE_TYPE_POP(pig_type_qt_const_QString_ref, const QString &) {
    PIGPOPSTACK;
    QString *pigr = new QString;
    if(SvOK(PIG_TOPSTACK)) {
        STRLEN n_a;
        *pigr = QString(SvPV(PIG_TOPSTACK, n_a));
    }
    PIGSCOPE_VIRTUAL(pig_type_qt_const_QString_ref, pigr);
    PIGPOP(*pigr);
}


PIG_DEFINE_SCOPE_ARGUMENT(pig_type_qt_const_QString_ptr) {
    delete (QString *)pig0;
}

PIG_DEFINE_SCOPE_VIRTUAL(pig_type_qt_const_QString_ptr) {
    delete (QString *)pig0;
}

PIG_DEFINE_TYPE_ARGUMENT(pig_type_qt_const_QString_ptr, const QString *) {
    PIGARGS;
    if(!SvOK(PIG_ARG)) {
        PIGARGUMENT(0);
    }
    STRLEN n_a;
    QString *pigr = new QString(SvPV(PIG_ARG, n_a));
    PIGSCOPE_ARGUMENT(pig_type_qt_const_QString_ptr, pigr);
    PIGARGUMENT(pigr);
}

PIG_DEFINE_TYPE_DEFARGUMENT(pig_type_qt_const_QString_ptr, const QString *) {
    PIGARGS;
    QString *pigr = (QString *)pig0;
    if(PIG_ARGOK) {
        STRLEN n_a;
        pigr = new QString(SvPV(PIG_ARG, n_a));
        PIGSCOPE_ARGUMENT(pig_type_qt_const_QString_ptr, pigr);
    }
    PIGARGUMENT(pigr);
}

PIG_DEFINE_TYPE_RETURN(pig_type_qt_const_QString_ptr, const QString *) {
    PIGRET;
    PIGRETURN(sv_2mortal(pig0 && !pig0->isNull() ?
			 newSVpv((char *)pig0->data(), 0) :
			 newSVsv(&PIGsv_undef)));
}

PIG_DEFINE_TYPE_PUSH(pig_type_qt_const_QString_ptr, const QString *) {
    PIGPUSHSTACK;
    PIGPUSH(sv_2mortal(pig0 && !pig0->isNull() ?
		       newSVpv((char *)pig0->data(), 0) :
		       newSVsv(&PIGsv_undef)));
}

PIG_DEFINE_TYPE_POP(pig_type_qt_const_QString_ptr, const QString *) {
    PIGPOPSTACK;
    QString *pigr = 0;
    if(SvOK(PIG_TOPSTACK)) {
        STRLEN n_a;
        pigr = new QString(SvPV(PIG_TOPSTACK, n_a));
        PIGSCOPE_VIRTUAL(pig_type_qt_const_QString_ptr, pigr);
    }
    PIGPOP(pigr);
}


#if QT_VERSION > 200

struct _pig_QCString {
    _pig_QCString(QCString *pig0, SV *pig1) :
        pigptr(pig0), pigsv(pig1) {}
    ~_pig_QCString() {
        if(pigptr->isNull())
	    sv_setsv(pigsv, &PIGsv_undef);
	else
	    sv_setpv(pigsv, (char *)pigptr->data());
	delete pigptr;
    }
    QCString *pigptr;
    SV *pigsv;
};

PIG_DEFINE_SCOPE_ARGUMENT(pig_type_qt_QCString) {
    delete (QCString *)pig0;
}

PIG_DEFINE_SCOPE_VIRTUAL(pig_type_qt_QCString) {
    delete (QCString *)pig0;
}

PIG_DEFINE_TYPE_ARGUMENT(pig_type_qt_QCString, QCString &) {
    PIGARGS;
    QCString *pigr = new QCString;
    if(SvOK(PIG_ARG)) {
	STRLEN n_a;
	*pigr = QCString(SvPV(PIG_ARG, n_a));
    }
    PIGSCOPE_ARGUMENT(pig_type_qt_QCString, pigr);
    PIGARGUMENT(*pigr);
}

PIG_DEFINE_TYPE_DEFARGUMENT(pig_type_qt_QCString, QCString &) {
    PIGARGS;
    QCString *pigr = new QCString(pig0);
    if(PIG_ARGOK) {
        STRLEN n_a;
        *pigr = QCString(SvPV(PIG_ARG, n_a));
    }
    PIGSCOPE_ARGUMENT(pig_type_qt_QCString, pigr);
    PIGARGUMENT(*pigr);
}

PIG_DEFINE_TYPE_RETURN(pig_type_qt_QCString, QCString &) {
    PIGRET;
    PIGRETURN(sv_2mortal(!pig0.isNull() ?
                         newSVpv((char *)pig0.data(), 0) :
                         newSVsv(&PIGsv_undef)));
}

PIG_DEFINE_TYPE_PUSH(pig_type_qt_QCString, QCString &) {
    PIGPUSHSTACK;
    PIGPUSH(sv_2mortal(!pig0.isNull() ?
		       newSVpv((char *)pig0.data(), 0) :
		       newSVsv(&PIGsv_undef)));
}

PIG_DEFINE_TYPE_POP(pig_type_qt_QCString, QCString &) {
    PIGPOPSTACK;
    QCString *pigr = new QCString;
    if(SvOK(PIG_TOPSTACK)) {
        STRLEN n_a;
        *pigr = QCString(SvPV(PIG_TOPSTACK, n_a));
    }
    PIGSCOPE_VIRTUAL(pig_type_qt_QCString, pigr);
    PIGPOP(*pigr);
}


PIG_DEFINE_SCOPE_ARGUMENT(pig_type_qt_QCString_ref) {
    delete (_pig_QCString *)pig0;
}

PIG_DEFINE_SCOPE_VIRTUAL(pig_type_qt_QCString_ref) {
    delete (_pig_QCString *)pig0;
}

PIG_DEFINE_TYPE_ARGUMENT(pig_type_qt_QCString_ref, QCString &) {
    PIGARGS;
    QCString *pigr = new QCString;
    if(SvOK(PIG_ARG)) {
	STRLEN n_a;
	*pigr = QCString(SvPV(PIG_ARG, n_a));
    }
    PIGSCOPE_ARGUMENT(pig_type_qt_QCString_ref,
		      new _pig_QCString(pigr, PIG_ARG));
    PIGARGUMENT(*pigr);
}

PIG_DEFINE_TYPE_DEFARGUMENT(pig_type_qt_QCString_ref, QCString &) {
    PIGARGS;
    QCString *pigr = new QCString(pig0);
    if(PIG_ARGOK) {
        STRLEN n_a;
        *pigr = QCString(SvPV(PIG_ARG, n_a));
	PIGSCOPE_ARGUMENT(pig_type_qt_QCString_ref,
			  new _pig_QCString(pigr, PIG_ARG));
    }
    else {
        PIGSCOPE_ARGUMENT(pig_type_qt_QCString, pigr);
    }
    PIGARGUMENT(*pigr);
}

PIG_DEFINE_TYPE_RETURN(pig_type_qt_QCString_ref, QCString &) {
    PIGRET;
    PIGRETURN(sv_2mortal(!pig0.isNull() ?
                         newSVpv((char *)pig0.data(), 0) :
                         newSVsv(&PIGsv_undef)));
}

PIG_DEFINE_TYPE_PUSH(pig_type_qt_QCString_ref, QCString &) {
    PIGPUSHSTACK;
    PIGPUSH(sv_2mortal(!pig0.isNull() ?
		       newSVpv((char *)pig0.data(), 0) :
		       newSVsv(&PIGsv_undef)));
}

PIG_DEFINE_TYPE_POP(pig_type_qt_QCString_ref, QCString &) {
    PIGPOPSTACK;
    QCString *pigr = new QCString;
    if(SvOK(PIG_TOPSTACK)) {
        STRLEN n_a;
        *pigr = QCString(SvPV(PIG_TOPSTACK, n_a));
    }
    PIGSCOPE_VIRTUAL(pig_type_qt_QCString_ref,
		     new _pig_QCString(pigr, PIG_TOPSTACK));
    PIGPOP(*pigr);
}


PIG_DEFINE_SCOPE_ARGUMENT(pig_type_qt_QCString_ptr) {
    delete (_pig_QCString *)pig0;
}

PIG_DEFINE_SCOPE_VIRTUAL(pig_type_qt_QCString_ptr) {
    delete (_pig_QCString *)pig0;
}

PIG_DEFINE_TYPE_ARGUMENT(pig_type_qt_QCString_ptr, QCString *) {
    PIGARGS;
    if(!SvOK(PIG_ARG)) {
        PIGARGUMENT(0);
    }
    STRLEN n_a;
    QCString *pigr = new QCString(SvPV(PIG_ARG, n_a));
    PIGSCOPE_ARGUMENT(pig_type_qt_QCString_ptr,
		      new _pig_QCString(pigr, PIG_ARG));
    PIGARGUMENT(pigr);
}

PIG_DEFINE_TYPE_DEFARGUMENT(pig_type_qt_QCString_ptr, QCString *) {
    PIGARGS;
    QCString *pigr = pig0;
    if(PIG_ARGOK) {
        STRLEN n_a;
        pigr = new QCString(SvPV(PIG_ARG, n_a));
        PIGSCOPE_ARGUMENT(pig_type_qt_QCString_ptr, 
			  new _pig_QCString(pigr, PIG_ARG));
    }
    PIGARGUMENT(pigr);
}

PIG_DEFINE_TYPE_RETURN(pig_type_qt_QCString_ptr, QCString *) {
    PIGRET;
    PIGRETURN(sv_2mortal(pig0 && !pig0->isNull() ?
			 newSVpv((char *)pig0->data(), 0) :
			 newSVsv(&PIGsv_undef)));
}

PIG_DEFINE_TYPE_PUSH(pig_type_qt_QCString_ptr, QCString *) {
    PIGPUSHSTACK;
    PIGPUSH(sv_2mortal(pig0 && !pig0->isNull() ?
		       newSVpv((char *)pig0->data(), 0) :
		       newSVsv(&PIGsv_undef)));
}

PIG_DEFINE_TYPE_POP(pig_type_qt_QCString_ptr, QCString *) {
    PIGPOPSTACK;
    QCString *pigr = 0;
    if(SvOK(PIG_TOPSTACK)) {
        STRLEN n_a;
        pigr = new QCString(SvPV(PIG_TOPSTACK, n_a));
        PIGSCOPE_VIRTUAL(pig_type_qt_QCString_ptr, 
			 new _pig_QCString(pigr, PIG_TOPSTACK));
    }
    PIGPOP(pigr);
}


PIG_DEFINE_SCOPE_ARGUMENT(pig_type_qt_const_QCString_ref) {
    delete (QCString *)pig0;
}

PIG_DEFINE_SCOPE_VIRTUAL(pig_type_qt_const_QCString_ref) {
    delete (QCString *)pig0;
}

PIG_DEFINE_TYPE_ARGUMENT(pig_type_qt_const_QCString_ref, const QCString &) {
    PIGARGS;
    QCString *pigr = new QCString;
    if(SvOK(PIG_ARG)) {
	STRLEN n_a;
	*pigr = QCString(SvPV(PIG_ARG, n_a));
    }
    PIGSCOPE_ARGUMENT(pig_type_qt_const_QCString_ref, pigr);
    PIGARGUMENT(*pigr);
}

PIG_DEFINE_TYPE_DEFARGUMENT(pig_type_qt_const_QCString_ref, const QCString &) {
    PIGARGS;
    QCString *pigr = new QCString(pig0);
    if(PIG_ARGOK) {
        STRLEN n_a;
        *pigr = QCString(SvPV(PIG_ARG, n_a));
    }
    PIGSCOPE_ARGUMENT(pig_type_qt_const_QCString_ref, pigr);
    PIGARGUMENT(*pigr);
}

PIG_DEFINE_TYPE_RETURN(pig_type_qt_const_QCString_ref, const QCString &) {
    PIGRET;
    PIGRETURN(sv_2mortal(!pig0.isNull() ?
                         newSVpv((char *)pig0.data(), 0) :
                         newSVsv(&PIGsv_undef)));
}

PIG_DEFINE_TYPE_PUSH(pig_type_qt_const_QCString_ref, const QCString &) {
    PIGPUSHSTACK;
    PIGPUSH(sv_2mortal(!pig0.isNull() ?
		       newSVpv((char *)pig0.data(), 0) :
		       newSVsv(&PIGsv_undef)));
}

PIG_DEFINE_TYPE_POP(pig_type_qt_const_QCString_ref, const QCString &) {
    PIGPOPSTACK;
    QCString *pigr = new QCString;
    if(SvOK(PIG_TOPSTACK)) {
        STRLEN n_a;
        *pigr = QCString(SvPV(PIG_TOPSTACK, n_a));
    }
    PIGSCOPE_VIRTUAL(pig_type_qt_const_QCString_ref, pigr);
    PIGPOP(*pigr);
}


PIG_DEFINE_SCOPE_ARGUMENT(pig_type_qt_const_QCString_ptr) {
    delete (QCString *)pig0;
}

PIG_DEFINE_SCOPE_VIRTUAL(pig_type_qt_const_QCString_ptr) {
    delete (QCString *)pig0;
}

PIG_DEFINE_TYPE_ARGUMENT(pig_type_qt_const_QCString_ptr, const QCString *) {
    PIGARGS;
    if(!SvOK(PIG_ARG)) {
        PIGARGUMENT(0);
    }
    STRLEN n_a;
    QCString *pigr = new QCString(SvPV(PIG_ARG, n_a));
    PIGSCOPE_ARGUMENT(pig_type_qt_const_QCString_ptr, pigr);
    PIGARGUMENT(pigr);
}

PIG_DEFINE_TYPE_DEFARGUMENT(pig_type_qt_const_QCString_ptr, const QCString *) {
    PIGARGS;
    QCString *pigr = (QCString *)pig0;
    if(PIG_ARGOK) {
        STRLEN n_a;
        pigr = new QCString(SvPV(PIG_ARG, n_a));
        PIGSCOPE_ARGUMENT(pig_type_qt_const_QCString_ptr, pigr);
    }
    PIGARGUMENT(pigr);
}

PIG_DEFINE_TYPE_RETURN(pig_type_qt_const_QCString_ptr, const QCString *) {
    PIGRET;
    PIGRETURN(sv_2mortal(pig0 && !pig0->isNull() ?
			 newSVpv((char *)pig0->data(), 0) :
			 newSVsv(&PIGsv_undef)));
}

PIG_DEFINE_TYPE_PUSH(pig_type_qt_const_QCString_ptr, const QCString *) {
    PIGPUSHSTACK;
    PIGPUSH(sv_2mortal(pig0 && !pig0->isNull() ?
		       newSVpv((char *)pig0->data(), 0) :
		       newSVsv(&PIGsv_undef)));
}

PIG_DEFINE_TYPE_POP(pig_type_qt_const_QCString_ptr, const QCString *) {
    PIGPOPSTACK;
    QCString *pigr = 0;
    if(SvOK(PIG_TOPSTACK)) {
        STRLEN n_a;
        pigr = new QCString(SvPV(PIG_TOPSTACK, n_a));
        PIGSCOPE_VIRTUAL(pig_type_qt_const_QCString_ptr, pigr);
    }
    PIGPOP(pigr);
}

PIG_DEFINE_TYPE(pig_type_qt_QCString)
PIG_DEFINE_TYPE(pig_type_qt_QCString_ref)
PIG_DEFINE_TYPE(pig_type_qt_QCString_ptr)
PIG_DEFINE_TYPE(pig_type_qt_const_QCString_ref)
PIG_DEFINE_TYPE(pig_type_qt_const_QCString_ptr)

#endif  // QT_VERSION > 200

PIG_DEFINE_TYPE(pig_type_qt_QString)
PIG_DEFINE_TYPE(pig_type_qt_QString_ref)
PIG_DEFINE_TYPE(pig_type_qt_QString_ptr)
PIG_DEFINE_TYPE(pig_type_qt_const_QString_ref)
PIG_DEFINE_TYPE(pig_type_qt_const_QString_ptr)

PIG_EXPORT_TABLE(pigtype_qt_QString)
    PIG_EXPORT_TYPE(pig_type_qt_QString, "Qt QString")
    PIG_EXPORT_TYPE(pig_type_qt_QString_ref, "Qt QString&")
    PIG_EXPORT_TYPE(pig_type_qt_QString_ptr, "Qt QString*")
    PIG_EXPORT_TYPE(pig_type_qt_const_QString_ref, "Qt const QString&")
    PIG_EXPORT_TYPE(pig_type_qt_const_QString_ptr, "Qt const QString*")
#if QT_VERSION > 200
    PIG_EXPORT_TYPE(pig_type_qt_QCString, "Qt QCString")
    PIG_EXPORT_TYPE(pig_type_qt_QCString_ref, "Qt QCString&")
    PIG_EXPORT_TYPE(pig_type_qt_QCString_ptr, "Qt QCString*")
    PIG_EXPORT_TYPE(pig_type_qt_const_QCString_ref, "Qt const QCString&")
    PIG_EXPORT_TYPE(pig_type_qt_const_QCString_ptr, "Qt const QCString*")
#endif
PIG_EXPORT_ENDTABLE
