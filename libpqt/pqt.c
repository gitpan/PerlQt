#include "perlqt.h"
#include "pqt_v.h"
#include "qobject.h"

class pqt_cheat_QObject : public QObject {
public:
  void doInitMetaObject() { this->initMetaObject(); }
};

#define PQT_IFARG(whentrue) ((items > pqtindex) ? (whentrue) : pqt1)
#define PQT_ST ST(pqtindex)
#define PQT_GOODST ((items > pqtindex) ? ST(pqtindex) : &sv_undef)

#include "qdstream.h"

QDataStream *pqt_dstreamptr;

static int pqtdepth = 0;
static int pqtindex = 0;

void pqt_increment_argument_index() { pqtindex++; }

////////////////////////////////////////////////////////////////////////////////

void pqt_return_nothing() {
    pqtdepth--;                   // pretty efficient, eh?
}

void pqt_return_bool(bool pqt1) {
    PQT_uXSARGS;
    ST(0) = sv_mortalcopy(pqt1 ? &sv_yes : &sv_no);
    pqtdepth--;
    XSRETURN(1);
}

void pqt_return_int(int pqt1) {
    PQT_uXSARGS;
    ST(0) = sv_2mortal(newSViv((IV)pqt1));
    pqtdepth--;
    XSRETURN(1);
}

void pqt_return_short(short pqt1) {
    PQT_uXSARGS;
    ST(0) = sv_2mortal(newSViv((IV)pqt1));
    pqtdepth--;
    XSRETURN(1);
}

void pqt_return_long(long pqt1) {
    PQT_uXSARGS;
    ST(0) = sv_2mortal(newSViv((IV)pqt1));
    pqtdepth--;
    XSRETURN(1);
}

void pqt_return_enum(unsigned int pqt1) {
    PQT_uXSARGS;
    ST(0) = sv_2mortal(newSViv((IV)pqt1));
    pqtdepth--;
    XSRETURN(1);
}

void pqt_return_uint(unsigned int pqt1) {
    PQT_uXSARGS;
    ST(0) = sv_2mortal(newSViv((IV)pqt1));
    pqtdepth--;
    XSRETURN(1);
}

void pqt_return_double(double pqt1) {
    PQT_uXSARGS;
    ST(0) = sv_2mortal(newSVnv(pqt1));
    pqtdepth--;
    XSRETURN(1);
}

void pqt_return_float(float pqt1) {
    PQT_uXSARGS;
    ST(0) = sv_2mortal(newSVnv((double)pqt1));
    pqtdepth--;
    XSRETURN(1);
}

////////////////////////////////////////////////////////////////////////////////

void pqt_return_cstring(const char *pqt1) {
    PQT_uXSARGS;
    ST(0) = sv_2mortal(pqt1 ? newSVpv((char *)pqt1, 0) : newSVsv(&sv_undef));
    pqtdepth--;
    XSRETURN(1);
}

void pqt_return_char(char pqt1) {
    char pqtr[2];
    pqtr[0] = pqt1;
    pqtr[1] = 0;
    pqt_return_cstring(pqtr);      // Cheat, its a cstring
}

void pqt_return_class(void *pqt1, const char *pqt2) {
    PQT_uXSARGS;
    pqt_object_data *pqtdata;
    ST(0) = sv_2mortal(pqt_create_object(pqt2, pqtdata));
    pqtdata->pqtptr = pqt1;
    pqtdata->pqtinfo = pqt_find_info(pqt2);
    pqtdata->pqtflags = PQTOBJ_MUTABLE;
    pqtdepth--;
    XSRETURN(1);
}

void pqt_return_const_class(const void *pqt1, const char *pqt2) {
    PQT_uXSARGS;
    pqt_object_data *pqtdata;
    ST(0) = sv_2mortal(pqt_create_object(pqt2, pqtdata));
    pqtdata->pqtptr = (void *)pqt1;
    pqtdata->pqtinfo = pqt_find_info(pqt2);
    pqtdata->pqtflags = PQTOBJ_CONST;
    pqtdepth--;
    XSRETURN(1);
}

void pqt_return_new_class(void *pqt1, const char *pqt2, const char *pqt3) {
    PQT_uXSARGS;
    pqt_object_data *pqtdata;
    ST(0) = sv_2mortal(pqt_create_object(pqt3 ? pqt3 : pqt2, pqtdata));
    pqtdata->pqtptr = pqt1;
    pqtdata->pqtinfo = pqt_find_info(pqt2);
    pqtdata->pqtflags = PQTOBJ_NEW | PQTOBJ_MUTABLE;

    pqt_virtual *pqtv = // dynamic_cast<pqt_virtual *>(pqt1);
        (pqt_virtual *)(*pqtdata->pqtinfo->pqt_tocastfunc)("virtual", pqt1);
    if(pqtv) pqtv->pqt_object(ST(0));
    QObject *pqtobj =
        (QObject *)(*pqtdata->pqtinfo->pqt_tocastfunc)("QObject", pqt1);
    if(pqtobj) ((pqt_cheat_QObject *)pqtobj)->doInitMetaObject();

    pqtdepth--;
    XSRETURN(1);
}


SV *pqt_argument_peek() {
    PQT_dXSARGS;
    SV *pqtr = PQT_GOODST;
    return pqtr;
}

SV *pqt_argument_sv() {
    PQT_dXSARGS;
    SV *pqtr = PQT_GOODST;
    pqtindex++;
    return pqtr;
}

int pqt_argument_int() {
    PQT_dXSARGS;
    int pqtr = SvIV(PQT_GOODST);
    pqtindex++;
    return pqtr;
}

int pqt_argument_int(int pqt1) {
    PQT_dXSARGS;
    int pqtr = PQT_IFARG((int)SvIV(PQT_ST));
    pqtindex++;
    return pqtr;
}

long pqt_argument_long() {
    PQT_dXSARGS;
    long pqtr = SvIV(PQT_GOODST);
    pqtindex++;
    return pqtr;
}

long pqt_argument_int(long pqt1) {
    PQT_dXSARGS;
    long pqtr = PQT_IFARG((long)SvIV(PQT_ST));
    pqtindex++;
    return pqtr;
}

int pqt_argument_enum() {
    PQT_dXSARGS;
    int pqtr = SvIV(PQT_GOODST);
    pqtindex++;
    return pqtr;
}

int pqt_argument_enum(int pqt1) {
    PQT_dXSARGS;
    int pqtr = PQT_IFARG((int)SvIV(PQT_ST));
    pqtindex++;
    return pqtr;
}

unsigned int pqt_argument_uint() {
    PQT_dXSARGS;
    unsigned int pqtr = (unsigned int)SvIV(PQT_GOODST);
    pqtindex++;
    return pqtr;
}

unsigned int pqt_argument_uint(unsigned int pqt1) {
    PQT_dXSARGS;
    int pqtr = PQT_IFARG((unsigned int)SvIV(PQT_ST));
    pqtindex++;
    return pqtr;
}

short pqt_argument_short() {
    PQT_dXSARGS;
    short pqtr = SvIV(PQT_GOODST);
    pqtindex++;
    return pqtr;
}

short pqt_argument_short(short pqt1) {
    PQT_dXSARGS;
    short pqtr = PQT_IFARG((short)SvIV(PQT_ST));
    pqtindex++;
    return pqtr;
}

double pqt_argument_double() {
    PQT_dXSARGS;
    double pqtr = SvNV(PQT_GOODST);
    pqtindex++;
    return pqtr;
}

double pqt_argument_double(double pqt1) {
    PQT_dXSARGS;
    double pqtr = PQT_IFARG(SvNV(PQT_ST));
    pqtindex++;
    return pqtr;
}

bool pqt_argument_bool() {
    PQT_dXSARGS;
    bool pqtr = SvTRUE(PQT_GOODST) ? TRUE : FALSE;
    pqtindex++;
    return pqtr;
}

bool pqt_argument_bool(bool pqt1) {
    PQT_dXSARGS;
    bool pqtr = PQT_IFARG(SvTRUE(PQT_GOODST) ? TRUE : FALSE);
    pqtindex++;
    return pqtr;
}

const char *pqt_argument_cstring() {
    PQT_dXSARGS;
    const char *pqtr = SvOK(PQT_GOODST) ? SvPV(PQT_GOODST, na) : 0;
    pqtindex++;
    return pqtr;
}

const char *pqt_argument_cstring(const char *pqt1) {
    PQT_dXSARGS;
    const char *pqtr = PQT_IFARG(SvOK(PQT_ST) ? SvPV(PQT_ST, na) : 0);
    pqtindex++;
    return pqtr;
}

char pqt_argument_char() {
    PQT_dXSARGS;
    char pqtr = SvOK(PQT_GOODST) ? *(SvPV(PQT_GOODST, na)) : 0;
    pqtindex++;
    return pqtr;
}

char pqt_argument_char(char pqt1) {
    PQT_dXSARGS;
    char pqtr = PQT_IFARG(SvOK(PQT_ST) ? *(SvPV(PQT_ST, na)) : 0);
    pqtindex++;
    return pqtr;
}

pqt_object_data *pqt_extract_object(SV *pqt1) {
    if(!SvROK(pqt1)) return 0;
    HV *pqthv_obj = (HV *)SvRV(pqt1);
    return (pqt_object_data *)(mg_find((SV *)pqthv_obj, '~')->mg_ptr);
}

void *pqt_cast_object(pqt_object_data *pqt1, const char *pqt2) {
    pqt_classinfolist *pqt_info = pqt1->pqtinfo;
    void *pqtr = (*pqt_info->pqt_tocastfunc)(pqt2, pqt1->pqtptr);
    if(!pqtr)
        die("Cannot cast %s pointer to %s\n", pqt_info->pqt_classname, pqt2);
//    else
//        printf("Converted %s to %s\n", pqt_info->pqt_classname, pqt2);
    return pqtr;
}

////////////////////////////////////////////////////////////////////////////////

void *pqt_argument_class(const char *pqt1) {
    PQT_dXSARGS;
    if(!(items > pqtindex && SvOK(ST(pqtindex))))   // generate undef warning
        return (void *)SvIV(&sv_undef);             // return NULL pointer
    pqt_object_data *pqtd = pqt_extract_object(PQT_ST);
    if(dowarn) {
        const char *pqtc = pqtd->pqtinfo->pqt_classname;
	if( (pqtd->pqtflags & PQTOBJ_CONST) &&
	   !(pqtd->pqtflags & PQTOBJ_MUTABLE))
	    warn("Modification of constant %s object is not recommended", pqtc);
	else if(!(pqtd->pqtflags & PQTOBJ_CONST) &&
		!(pqtd->pqtflags & PQTOBJ_MUTABLE))
	    warn("Possible modification of constant %s object", pqtc);
        if(pqtd->pqtflags & PQTOBJ_DELETED)
            warn("Use of deleted %s object\n", pqtc);
    }
    pqtindex++;
    return pqt_cast_object(pqtd, pqt1);
}

void *pqt_argument_class(const char *pqt1, void *pqt2) {
    PQT_dXSARGS;
    if(!(items > pqtindex)) return pqt2;
    if(!SvOK(ST(pqtindex))) return (void *)SvIV(&sv_undef);  // warn them good
    pqt_object_data *pqtd = pqt_extract_object(PQT_ST);
    if(dowarn) {
        const char *pqtc = pqtd->pqtinfo->pqt_classname;
        if( (pqtd->pqtflags & PQTOBJ_CONST) &&
           !(pqtd->pqtflags & PQTOBJ_MUTABLE))
            warn("Modification of constant %s object is not recommended", pqtc);
        else if(!(pqtd->pqtflags & PQTOBJ_CONST) &&
                !(pqtd->pqtflags & PQTOBJ_MUTABLE))
            warn("Possible modification of constant %s object", pqtc);
        if(pqtd->pqtflags & PQTOBJ_DELETED)
            warn("Use of deleted %s object\n", pqtc);
    }
    pqtindex++;
    return pqt_cast_object(pqtd, pqt1);
}

const void *pqt_argument_const_class(const char *pqt1) {
    PQT_dXSARGS;
    if(!(items > pqtindex && SvOK(ST(pqtindex))))
        return (void *)SvIV(&sv_undef);
    pqt_object_data *pqtd = pqt_extract_object(PQT_ST);
    if(dowarn) {
        const char *pqtc = pqtd->pqtinfo->pqt_classname;
        if(pqtd->pqtflags & PQTOBJ_DELETED)
            warn("Use of deleted %s object\n", pqtc);
    }
    pqtindex++;
    return pqt_cast_object(pqtd, pqt1);
}

const void *pqt_argument_const_class(const char *pqt1, const void *pqt2) {
    PQT_dXSARGS;
    if(!(items > pqtindex)) return pqt2;
    if(!SvOK(ST(pqtindex))) return (void *)SvIV(&sv_undef);
    pqt_object_data *pqtd = pqt_extract_object(PQT_ST);
    if(dowarn) {
        const char *pqtc = pqtd->pqtinfo->pqt_classname;
        if(pqtd->pqtflags & PQTOBJ_DELETED)
            warn("Use of deleted %s object\n", pqtc);
    }
    pqtindex++;
    return pqt_cast_object(pqtd, pqt1);
}

void *pqt_argument_class_destructor(const char *pqt1) {
    PQT_dXSARGS;
    if(!(items > pqtindex && SvOK(ST(pqtindex))))
        return (void *)SvIV(&sv_undef);
    pqt_object_data *pqtd = pqt_extract_object(PQT_ST);
    pqtindex++;
    return pqt_cast_object(pqtd, pqt1);
}

void *pqt_argument_classref(const char *pqt1) {
    PQT_dXSARGS;
    if(!(items > pqtindex && SvOK(ST(pqtindex)))) {
        if(dowarn) warn("About to dereference undef %s", pqt1);
        return (void *)SvIV(&sv_undef);
    }
    pqt_object_data *pqtd = pqt_extract_object(PQT_ST);
    if(dowarn) {
        const char *pqtc = pqtd->pqtinfo->pqt_classname;
	if( (pqtd->pqtflags & PQTOBJ_CONST) &&
	   !(pqtd->pqtflags & PQTOBJ_MUTABLE))
	    warn("Modification of constant %s object is not recommended", pqtc);
	else if(!(pqtd->pqtflags & PQTOBJ_CONST) &&
		!(pqtd->pqtflags & PQTOBJ_MUTABLE))
	    warn("Possible modification of constant %s object", pqtc);
        if(pqtd->pqtflags & PQTOBJ_DELETED)
            warn("Use of deleted %s object\n", pqtc);
    }
    pqtindex++;
    return pqt_cast_object(pqtd, pqt1);
}

void *pqt_argument_classref(const char *pqt1, void *pqt2) {
    PQT_dXSARGS;
    if(!(items > pqtindex)) return pqt2;
    if(!SvOK(ST(pqtindex))) {
        if(dowarn) warn("About to dereference undef %s", pqt1);
        return (void *)SvIV(&sv_undef);
    }
    pqt_object_data *pqtd = pqt_extract_object(PQT_ST);
    if(dowarn) {
        const char *pqtc = pqtd->pqtinfo->pqt_classname;
        if( (pqtd->pqtflags & PQTOBJ_CONST) &&
           !(pqtd->pqtflags & PQTOBJ_MUTABLE))
            warn("Modification of constant %s object is not recommended", pqtc);
        else if(!(pqtd->pqtflags & PQTOBJ_CONST) &&
                !(pqtd->pqtflags & PQTOBJ_MUTABLE))
            warn("Possible modification of constant %s object", pqtc);
        if(pqtd->pqtflags & PQTOBJ_DELETED)
            warn("Use of deleted %s object\n", pqtc);
    }
    pqtindex++;
    return pqt_cast_object(pqtd, pqt1);
}

const void *pqt_argument_const_classref(const char *pqt1) {
    PQT_dXSARGS;
    if(!(items > pqtindex && SvOK(ST(pqtindex)))) {
        if(dowarn) warn("About to dereference undef %s", pqt1);
        return (void *)SvIV(&sv_undef);
    }
    pqt_object_data *pqtd = pqt_extract_object(PQT_ST);
    if(dowarn) {
        const char *pqtc = pqtd->pqtinfo->pqt_classname;
        if(pqtd->pqtflags & PQTOBJ_DELETED)
            warn("Use of deleted %s object\n", pqtc);
    }
    pqtindex++;
    return pqt_cast_object(pqtd, pqt1);
}

const void *pqt_argument_const_classref(const char *pqt1, const void *pqt2) {
    PQT_dXSARGS;
    if(!(items > pqtindex)) return pqt2;
    if(!SvOK(ST(pqtindex))) {
        if(dowarn) warn("About to dereference undef %s", pqt1);
        return (void *)SvIV(&sv_undef);
    }
    pqt_object_data *pqtd = pqt_extract_object(PQT_ST);
    if(dowarn) {
        const char *pqtc = pqtd->pqtinfo->pqt_classname;
        if(pqtd->pqtflags & PQTOBJ_DELETED)
            warn("Use of deleted %s object\n", pqtc);
    }
    pqtindex++;
    return pqt_cast_object(pqtd, pqt1);
}

////////////////////////////////////////////////////////////////////////////////
void pqt_push_int(int pqt1) {
    dSP;
    XPUSHs(sv_2mortal(newSViv(pqt1)));
    PUTBACK;
}

void pqt_push_short(short pqt1) {
    dSP;
    XPUSHs(sv_2mortal(newSViv(pqt1)));
    PUTBACK;
}

void pqt_push_long(long pqt1) {
    dSP;
    XPUSHs(sv_2mortal(newSViv(pqt1)));
    PUTBACK;
}

void pqt_push_enum(int pqt1) {
    dSP;
    XPUSHs(sv_2mortal(newSViv(pqt1)));
    PUTBACK;
}

void pqt_push_double(double pqt1) {
    dSP;
    XPUSHs(sv_2mortal(newSVnv(pqt1)));
    PUTBACK;
}

void pqt_push_float(float pqt1) {
    dSP;
    XPUSHs(sv_2mortal(newSVnv((double)pqt1)));
    PUTBACK;
}

void pqt_push_bool(bool pqt1) {
    dSP;
    XPUSHs(sv_mortalcopy(boolSV(pqt1)));
    PUTBACK;
}

void pqt_push_cstring(const char *pqt1) {
    dSP;
    XPUSHs(sv_2mortal(pqt1 ? newSVpv((char *)pqt1, 0) : newSVsv(&sv_undef)));
    PUTBACK;
}

void pqt_push_char(char pqt1) {
    char pqtr[2];
    pqtr[0] = pqt1;
    pqtr[1] = 0;
    pqt_push_cstring(pqtr);
}

void pqt_push_class(void *pqt1, const char *pqt2) {
    dSP;
    if(!pqt1) {
        XPUSHs(sv_2mortal(newSVsv(&sv_undef)));
	PUTBACK;
	return;
    }
    pqt_object_data *pqtdata;
    XPUSHs(sv_2mortal(pqt_create_object(pqt2, pqtdata)));
    PUTBACK;

    pqtdata->pqtptr = pqt1;
    pqtdata->pqtinfo = pqt_find_info(pqt2);
    pqtdata->pqtflags = PQTOBJ_MUTABLE;
}

void pqt_push_const_class(const void *pqt1, const char *pqt2) {
    dSP;
    if(!pqt1) {
        XPUSHs(sv_2mortal(newSVsv(&sv_undef)));
	PUTBACK;
	return;
    }
    pqt_object_data *pqtdata;
    XPUSHs(sv_2mortal(pqt_create_object(pqt2, pqtdata)));
    PUTBACK;

    pqtdata->pqtptr = (void *)pqt1;
    pqtdata->pqtinfo = pqt_find_info(pqt2);
    pqtdata->pqtflags = PQTOBJ_CONST;
}

void pqt_push_const_classref(const void *pqt1, const char *pqt2) {
    dSP;
    pqt_object_data *pqtdata;
    XPUSHs(sv_2mortal(pqt_create_object(pqt2, pqtdata)));
    PUTBACK;

    pqtdata->pqtptr = (void *)pqt1;
    pqtdata->pqtinfo = pqt_find_info(pqt2);
    pqtdata->pqtflags = PQTOBJ_CONST;
}

void pqt_push_sv(void *pqt1) {
    dSP;
    XPUSHs(sv_mortalcopy((SV *)pqt1));
    PUTBACK;
}

void pqt_push_sv_from_av(void *pqt1) {
    dSP;
    AV *pqt_av = (AV *)pqt1;
    SV *pqt_sv;

    while(pqt_sv = av_shift(pqt_av))
        XPUSHs(sv_mortalcopy(pqt_sv));

    SvREFCNT_dec((SV *)pqt_av);
    PUTBACK;
}

extern SV *pqt_virtual_return_value;

int pqt_pop_int() {
    int pqtr = SvIV(pqt_virtual_return_value);
    SvREFCNT_dec(pqt_virtual_return_value);
    return pqtr;
}

int pqt_pop_enum() {
    int pqtr = SvIV(pqt_virtual_return_value);
    SvREFCNT_dec(pqt_virtual_return_value);
    return pqtr;
}

bool pqt_pop_bool() {
    bool pqtr = SvTRUE(pqt_virtual_return_value) ? TRUE : FALSE;
    SvREFCNT_dec(pqt_virtual_return_value);
    return pqtr;
}

const char *pqt_pop_cstring() {
    const char *pqtr = SvOK(pqt_virtual_return_value) ?
      SvPV(pqt_virtual_return_value, na) : 0;
    SvREFCNT_dec(pqt_virtual_return_value);
    return pqtr;
}

void *pqt_pop_class(const char *pqt1) {
    if(!SvOK(pqt_virtual_return_value)) return 0;
    pqt_object_data *pqtd = pqt_extract_object(pqt_virtual_return_value);
    if(dowarn) {
        const char *pqtc = pqtd->pqtinfo->pqt_classname;
	if( (pqtd->pqtflags & PQTOBJ_CONST) &&
	   !(pqtd->pqtflags & PQTOBJ_MUTABLE))
	    warn("Modification of constant %s object is not recommended", pqtc);
	else if(!(pqtd->pqtflags & PQTOBJ_CONST) &&
		!(pqtd->pqtflags & PQTOBJ_MUTABLE))
	    warn("Possible modification of constant %s object", pqtc);
        if(pqtd->pqtflags & PQTOBJ_DELETED)
            warn("Use of deleted %s object\n", pqtc);
    }
    return pqt_cast_object(pqtd, pqt1);
}

const void *pqt_pop_const_class(const char *pqt1) {
    if(!SvOK(pqt_virtual_return_value)) return 0;
    pqt_object_data *pqtd = pqt_extract_object(pqt_virtual_return_value);
    if(dowarn) {
        const char *pqtc = pqtd->pqtinfo->pqt_classname;
        if(pqtd->pqtflags & PQTOBJ_DELETED)
            warn("Use of deleted %s object\n", pqtc);
    }
    return pqt_cast_object(pqtd, pqt1);
}


const char *pqt_current_method = "";

////////////////////////////////////////////////////////////////////////////////
void pqt_begin(void *pqt_voidcv, const char *pqt_methname) {
    CV *pqt_cv = (CV *)pqt_voidcv;
    pqt_current_method = pqt_methname;
//    printf("%-3d %s::%s\n", pqtdepth, HvNAME(GvSTASH(CvGV(pqt_cv))), pqt_methname);
    pqtdepth++;

//    {
//      PQT_dXSARGS;
//	printf("%-3d ST(0) starts with %p\n", pqtdepth, &(ST(0)));
//    }
}

void pqt_lastargument() {
    dXSARGS;              // VITAL!!! Allows proper recursion
    pqtindex = 0;         // VITAL
}

void pqt_destroy_object(void *, class pqt_virtual *) {
}

bool pqt_can_delete() {
    PQT_uXSARGS;
    pqt_object_data *pqtd = pqt_extract_object(ST(0));
//    printf("Time to delete our %s\n", pqtd->pqtinfo->pqt_classname);
//    if((pqtd->pqtflags & PQTOBJ_NEW) && !(pqtd->pqtflags & PQTOBJ_DURABLE) &&
//      !(pqtd->pqtflags & PQTOBJ_DELETED)) {
//        printf("Alright, time to axe %p\n", pqtd->pqtptr);
//	if((pqtd->pqtflags & PQTOBJ_QOBJECT) && pqtd->pqtdata)
//	    SvREFCNT_dec((SV *)pqtd->pqtdata);     // The slot -> pqt_S map

    if((pqtd->pqtflags & PQTOBJ_NEW) && !(pqtd->pqtflags & PQTOBJ_DELETED) &&
       !pqtd->pqtinfo->pqt_suicidal) {
        return TRUE;
    }
    return FALSE;
}
