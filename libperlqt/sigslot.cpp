#include "sigslot.h"

class pqt_ArgumentIterator {
    const char *args;
    int cnt;
public:
    pqt_ArgumentIterator() { args = NULL; cnt = 0; }
    pqt_ArgumentIterator(const char *p) {
	args = p;
	cnt = *args;
	args += args[1] + 2;
    }
    const char *operator ++();
};

const char *pqt_ArgumentIterator::operator ++() {
    const char *ret = (--cnt < 0) ? 0 : args++;

// Yes, that NULL pointer is intentionally dereferenced here

    if(*ret == PQT_CONST) ret = args++;
    if(*ret == PQT_OBJECT) args += *args;
    return ret;
}

static double pqt_double_stack[3];
static long pqt_long_stack[3];
static short pqt_short_stack[3];
static bool pqt_bool_stack[3];
class pqt_ArgumentStack {
    int pqtdouble, pqtlong, pqtshort, pqtbool;

public:
    pqt_ArgumentStack() {
	pqtdouble = 0;
	pqtlong = 0;
	pqtshort = 0;
	pqtbool = 0;
    }
    int inc_double() { return pqtdouble++; }
    void inc_double(double p) { pqt_double_stack[inc_double()] = p; }

    int inc_long() { return pqtlong++; }
    void inc_long(long p) { pqt_long_stack[inc_long()] = p; }

    int inc_short() { return pqtshort++; }
    void inc_short(short p) { pqt_short_stack[inc_short()] = p; }

    int inc_bool() { return pqtbool++; }
    void inc_bool(bool p) { pqt_bool_stack[inc_bool()] = p; }

};

typedef void (*pqt_signal)();

static QSenderObject *pqt_obj;
static QMember *pqt_m;
static pqt_ArgumentIterator pqt_GlobalArgumentIterator;

HV *Crypt = NULL, *Signals = NULL;

static int pqt_exp_tab[] = { 1, 4, 16, 64 };
int pqt_typeidx(char c) {
    switch(c) {
	case PQT_DOUBLE:
	    return 0 + 1;
	case PQT_LONG:
	case PQT_INT:
	case PQT_OBJECT:
	case PQT_STRING:
	case PQT_SCALAR:
	case PQT_SCALAR_REF:
	case PQT_HASH_REF:
	case PQT_ARRAY_REF:
	case PQT_DOT_DOT_DOT:
	case PQT_FLOAT:
	    return 1 + 1;
	case PQT_SHORT:
	    return 2 + 1;
	case PQT_BOOL:
	    return 3 + 1;
    }
}

int pqt_hash(const char *p) {
    int ret = 0, cnt = *p;
    pqt_ArgumentIterator argit(p);

    for(int i = 0; i < cnt; i++)
	ret += pqt_exp_tab[cnt - (i+1)] * pqt_typeidx(*++argit);
    return ret;
}

QMember pqt_slot_matrix[] = {
    (QMember)((void (pqt_Slot::*)())&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(double))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(long))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(short))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(bool))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(double, double))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(double, long))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(double, short))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(double, bool))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(long, double))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(long, long))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(long, short))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(long, bool))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(short, double))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(short, long))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(short, short))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(short, bool))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(bool, double))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(bool, long))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(bool, short))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(bool, bool))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(double, double, double))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(double, double, long))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(double, double, short))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(double, double, bool))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(double, long, double))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(double, long, long))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(double, long, short))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(double, long, bool))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(double, short, double))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(double, short, long))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(double, short, short))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(double, short, bool))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(double, bool, double))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(double, bool, long))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(double, bool, short))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(double, bool, bool))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(long, double, double))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(long, double, long))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(long, double, short))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(long, double, bool))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(long, long, double))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(long, long, long))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(long, long, short))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(long, long, bool))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(long, short, double))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(long, short, long))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(long, short, short))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(long, short, bool))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(long, bool, double))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(long, bool, long))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(long, bool, short))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(long, bool, bool))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(short, double, double))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(short, double, long))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(short, double, short))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(short, double, bool))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(short, long, double))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(short, long, long))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(short, long, short))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(short, long, bool))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(short, short, double))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(short, short, long))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(short, short, short))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(short, short, bool))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(short, bool, double))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(short, bool, long))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(short, bool, short))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(short, bool, bool))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(bool, double, double))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(bool, double, long))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(bool, double, short))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(bool, double, bool))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(bool, long, double))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(bool, long, long))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(bool, long, short))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(bool, long, bool))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(bool, short, double))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(bool, short, long))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(bool, short, short))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(bool, short, bool))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(bool, bool, double))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(bool, bool, long))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(bool, bool, short))&pqt_Slot::s),
    (QMember)((void (pqt_Slot::*)(bool, bool, bool))&pqt_Slot::s),
};

pqt_Slot::pqt_Slot(SV *o, const char *p) {
    objectsv = newRV_noinc((SV *)obj_check(o));
    object = (QObject *)extract_ptr(objectsv, "QObject");
    crypt = reverse_proto(p);
    name = crypt + 2;
    proto = p;
}

pqt_Slot::~pqt_Slot() {
    SvFLAGS(objectsv) = (SvFLAGS(objectsv) & ~SVTYPEMASK) | SVt_NULL;
    SvREFCNT_dec(objectsv);
}

void pqt_Slot::initMetaObject() {}

const char *pqt_Slot::className() const {
    return object->className();
}

QMetaObject *pqt_Slot::metaObject() const {
    return object->metaObject();
}

QMember pqt_Slot::stub(const char *p) {
    return pqt_slot_matrix[pqt_hash(reverse_proto(p))];
}

void pqt_Slot::slot() {
    dSP;
    ENTER;
    SAVETMPS;
    PUSHMARK(sp);
    XPUSHs(sv_mortalcopy(objectsv));		// is the mortal copy wasteful?

    pqt_ArgumentStack stack;
    pqt_ArgumentIterator iter(crypt);

    for(int i = 0; i < *crypt; i++) {
	const char *c = ++iter;
	switch(*c) {

	    case PQT_DOUBLE:
		XPUSHs(sv_2mortal(newSVnv((double)*(double*)&pqt_double_stack[stack.inc_double()])));
		break;
	    case PQT_LONG:
		XPUSHs(sv_2mortal(newSViv((IV)*(long*)&pqt_long_stack[stack.inc_long()])));
		break;
	    case PQT_INT:
		XPUSHs(sv_2mortal(newSViv((IV)*(int*)&pqt_long_stack[stack.inc_long()])));
		break;
	    case PQT_OBJECT:
		XPUSHs(sv_2mortal(objectify_ptr(*(void**)&pqt_long_stack[stack.inc_long()],c+1)));
		break;
	    case PQT_STRING:
		XPUSHs(sv_2mortal(newSVpv(*(char**)&pqt_long_stack[stack.inc_long()],0)));
		break;
	    case PQT_SCALAR:
		{XPUSHs(sv_mortalcopy(*(SV**)&pqt_long_stack[stack.inc_long()]));}
		break;
	    case PQT_SCALAR_REF:
		{XPUSHs(sv_mortalcopy(*(SV**)&pqt_long_stack[stack.inc_long()]));}
		break;
	    case PQT_HASH_REF:
		{XPUSHs(sv_mortalcopy(*(SV**)&pqt_long_stack[stack.inc_long()]));}
		break;
	    case PQT_ARRAY_REF:
		{XPUSHs(sv_mortalcopy(*(SV**)&pqt_long_stack[stack.inc_long()]));}
		break;
	    case PQT_DOT_DOT_DOT:
		{AV *pqt_av = *(AV **)&pqt_long_stack[stack.inc_long()]; SV *pqt_sv; while((pqt_sv = av_shift(pqt_av))) XPUSHs(sv_mortalcopy(pqt_sv));}
		break;
	    case PQT_FLOAT:
		XPUSHs(sv_2mortal(newSVnv((double)*(float*)&pqt_long_stack[stack.inc_long()])));
		break;
	    case PQT_SHORT:
		XPUSHs(sv_2mortal(newSViv((IV)*(short*)&pqt_short_stack[stack.inc_short()])));
		break;
	    case PQT_BOOL:
		XPUSHs(sv_2mortal(newSVsv(boolSV(*(bool*)&pqt_bool_stack[stack.inc_bool()]))));
		break;
	}
    }

    PUTBACK;

    perl_call_sv(
	(SV *)GvCV(
	    gv_fetchmethod(SvSTASH(SvRV(objectsv)), (char *)name)
	), G_DISCARD
    );

    FREETMPS;
    LEAVE;
}

void pqt_Slot::s() {
    slot();
}

void pqt_Slot::s(double pqt0) {
    pqt_double_stack[0] = pqt0;
    slot();
}

void pqt_Slot::s(long pqt0) {
    pqt_long_stack[0] = pqt0;
    slot();
}

void pqt_Slot::s(short pqt0) {
    pqt_short_stack[0] = pqt0;
    slot();
}

void pqt_Slot::s(bool pqt0) {
    pqt_bool_stack[0] = pqt0;
    slot();
}

void pqt_Slot::s(double pqt0, double pqt1) {
    pqt_double_stack[0] = pqt0;
    pqt_double_stack[1] = pqt1;
    slot();
}

void pqt_Slot::s(double pqt0, long pqt1) {
    pqt_double_stack[0] = pqt0;
    pqt_long_stack[0] = pqt1;
    slot();
}

void pqt_Slot::s(double pqt0, short pqt1) {
    pqt_double_stack[0] = pqt0;
    pqt_short_stack[0] = pqt1;
    slot();
}

void pqt_Slot::s(double pqt0, bool pqt1) {
    pqt_double_stack[0] = pqt0;
    pqt_bool_stack[0] = pqt1;
    slot();
}

void pqt_Slot::s(long pqt0, double pqt1) {
    pqt_long_stack[0] = pqt0;
    pqt_double_stack[0] = pqt1;
    slot();
}

void pqt_Slot::s(long pqt0, long pqt1) {
    pqt_long_stack[0] = pqt0;
    pqt_long_stack[1] = pqt1;
    slot();
}

void pqt_Slot::s(long pqt0, short pqt1) {
    pqt_long_stack[0] = pqt0;
    pqt_short_stack[0] = pqt1;
    slot();
}

void pqt_Slot::s(long pqt0, bool pqt1) {
    pqt_long_stack[0] = pqt0;
    pqt_bool_stack[0] = pqt1;
    slot();
}

void pqt_Slot::s(short pqt0, double pqt1) {
    pqt_short_stack[0] = pqt0;
    pqt_double_stack[0] = pqt1;
    slot();
}

void pqt_Slot::s(short pqt0, long pqt1) {
    pqt_short_stack[0] = pqt0;
    pqt_long_stack[0] = pqt1;
    slot();
}

void pqt_Slot::s(short pqt0, short pqt1) {
    pqt_short_stack[0] = pqt0;
    pqt_short_stack[1] = pqt1;
    slot();
}

void pqt_Slot::s(short pqt0, bool pqt1) {
    pqt_short_stack[0] = pqt0;
    pqt_bool_stack[0] = pqt1;
    slot();
}

void pqt_Slot::s(bool pqt0, double pqt1) {
    pqt_bool_stack[0] = pqt0;
    pqt_double_stack[0] = pqt1;
    slot();
}

void pqt_Slot::s(bool pqt0, long pqt1) {
    pqt_bool_stack[0] = pqt0;
    pqt_long_stack[0] = pqt1;
    slot();
}

void pqt_Slot::s(bool pqt0, short pqt1) {
    pqt_bool_stack[0] = pqt0;
    pqt_short_stack[0] = pqt1;
    slot();
}

void pqt_Slot::s(bool pqt0, bool pqt1) {
    pqt_bool_stack[0] = pqt0;
    pqt_bool_stack[1] = pqt1;
    slot();
}

void pqt_Slot::s(double pqt0, double pqt1, double pqt2) {
    pqt_double_stack[0] = pqt0;
    pqt_double_stack[1] = pqt1;
    pqt_double_stack[2] = pqt2;
    slot();
}

void pqt_Slot::s(double pqt0, double pqt1, long pqt2) {
    pqt_double_stack[0] = pqt0;
    pqt_double_stack[1] = pqt1;
    pqt_long_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(double pqt0, double pqt1, short pqt2) {
    pqt_double_stack[0] = pqt0;
    pqt_double_stack[1] = pqt1;
    pqt_short_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(double pqt0, double pqt1, bool pqt2) {
    pqt_double_stack[0] = pqt0;
    pqt_double_stack[1] = pqt1;
    pqt_bool_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(double pqt0, long pqt1, double pqt2) {
    pqt_double_stack[0] = pqt0;
    pqt_long_stack[0] = pqt1;
    pqt_double_stack[1] = pqt2;
    slot();
}

void pqt_Slot::s(double pqt0, long pqt1, long pqt2) {
    pqt_double_stack[0] = pqt0;
    pqt_long_stack[0] = pqt1;
    pqt_long_stack[1] = pqt2;
    slot();
}

void pqt_Slot::s(double pqt0, long pqt1, short pqt2) {
    pqt_double_stack[0] = pqt0;
    pqt_long_stack[0] = pqt1;
    pqt_short_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(double pqt0, long pqt1, bool pqt2) {
    pqt_double_stack[0] = pqt0;
    pqt_long_stack[0] = pqt1;
    pqt_bool_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(double pqt0, short pqt1, double pqt2) {
    pqt_double_stack[0] = pqt0;
    pqt_short_stack[0] = pqt1;
    pqt_double_stack[1] = pqt2;
    slot();
}

void pqt_Slot::s(double pqt0, short pqt1, long pqt2) {
    pqt_double_stack[0] = pqt0;
    pqt_short_stack[0] = pqt1;
    pqt_long_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(double pqt0, short pqt1, short pqt2) {
    pqt_double_stack[0] = pqt0;
    pqt_short_stack[0] = pqt1;
    pqt_short_stack[1] = pqt2;
    slot();
}

void pqt_Slot::s(double pqt0, short pqt1, bool pqt2) {
    pqt_double_stack[0] = pqt0;
    pqt_short_stack[0] = pqt1;
    pqt_bool_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(double pqt0, bool pqt1, double pqt2) {
    pqt_double_stack[0] = pqt0;
    pqt_bool_stack[0] = pqt1;
    pqt_double_stack[1] = pqt2;
    slot();
}

void pqt_Slot::s(double pqt0, bool pqt1, long pqt2) {
    pqt_double_stack[0] = pqt0;
    pqt_bool_stack[0] = pqt1;
    pqt_long_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(double pqt0, bool pqt1, short pqt2) {
    pqt_double_stack[0] = pqt0;
    pqt_bool_stack[0] = pqt1;
    pqt_short_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(double pqt0, bool pqt1, bool pqt2) {
    pqt_double_stack[0] = pqt0;
    pqt_bool_stack[0] = pqt1;
    pqt_bool_stack[1] = pqt2;
    slot();
}

void pqt_Slot::s(long pqt0, double pqt1, double pqt2) {
    pqt_long_stack[0] = pqt0;
    pqt_double_stack[0] = pqt1;
    pqt_double_stack[1] = pqt2;
    slot();
}

void pqt_Slot::s(long pqt0, double pqt1, long pqt2) {
    pqt_long_stack[0] = pqt0;
    pqt_double_stack[0] = pqt1;
    pqt_long_stack[1] = pqt2;
    slot();
}

void pqt_Slot::s(long pqt0, double pqt1, short pqt2) {
    pqt_long_stack[0] = pqt0;
    pqt_double_stack[0] = pqt1;
    pqt_short_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(long pqt0, double pqt1, bool pqt2) {
    pqt_long_stack[0] = pqt0;
    pqt_double_stack[0] = pqt1;
    pqt_bool_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(long pqt0, long pqt1, double pqt2) {
    pqt_long_stack[0] = pqt0;
    pqt_long_stack[1] = pqt1;
    pqt_double_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(long pqt0, long pqt1, long pqt2) {
    pqt_long_stack[0] = pqt0;
    pqt_long_stack[1] = pqt1;
    pqt_long_stack[2] = pqt2;
    slot();
}

void pqt_Slot::s(long pqt0, long pqt1, short pqt2) {
    pqt_long_stack[0] = pqt0;
    pqt_long_stack[1] = pqt1;
    pqt_short_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(long pqt0, long pqt1, bool pqt2) {
    pqt_long_stack[0] = pqt0;
    pqt_long_stack[1] = pqt1;
    pqt_bool_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(long pqt0, short pqt1, double pqt2) {
    pqt_long_stack[0] = pqt0;
    pqt_short_stack[0] = pqt1;
    pqt_double_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(long pqt0, short pqt1, long pqt2) {
    pqt_long_stack[0] = pqt0;
    pqt_short_stack[0] = pqt1;
    pqt_long_stack[1] = pqt2;
    slot();
}

void pqt_Slot::s(long pqt0, short pqt1, short pqt2) {
    pqt_long_stack[0] = pqt0;
    pqt_short_stack[0] = pqt1;
    pqt_short_stack[1] = pqt2;
    slot();
}

void pqt_Slot::s(long pqt0, short pqt1, bool pqt2) {
    pqt_long_stack[0] = pqt0;
    pqt_short_stack[0] = pqt1;
    pqt_bool_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(long pqt0, bool pqt1, double pqt2) {
    pqt_long_stack[0] = pqt0;
    pqt_bool_stack[0] = pqt1;
    pqt_double_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(long pqt0, bool pqt1, long pqt2) {
    pqt_long_stack[0] = pqt0;
    pqt_bool_stack[0] = pqt1;
    pqt_long_stack[1] = pqt2;
    slot();
}

void pqt_Slot::s(long pqt0, bool pqt1, short pqt2) {
    pqt_long_stack[0] = pqt0;
    pqt_bool_stack[0] = pqt1;
    pqt_short_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(long pqt0, bool pqt1, bool pqt2) {
    pqt_long_stack[0] = pqt0;
    pqt_bool_stack[0] = pqt1;
    pqt_bool_stack[1] = pqt2;
    slot();
}

void pqt_Slot::s(short pqt0, double pqt1, double pqt2) {
    pqt_short_stack[0] = pqt0;
    pqt_double_stack[0] = pqt1;
    pqt_double_stack[1] = pqt2;
    slot();
}

void pqt_Slot::s(short pqt0, double pqt1, long pqt2) {
    pqt_short_stack[0] = pqt0;
    pqt_double_stack[0] = pqt1;
    pqt_long_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(short pqt0, double pqt1, short pqt2) {
    pqt_short_stack[0] = pqt0;
    pqt_double_stack[0] = pqt1;
    pqt_short_stack[1] = pqt2;
    slot();
}

void pqt_Slot::s(short pqt0, double pqt1, bool pqt2) {
    pqt_short_stack[0] = pqt0;
    pqt_double_stack[0] = pqt1;
    pqt_bool_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(short pqt0, long pqt1, double pqt2) {
    pqt_short_stack[0] = pqt0;
    pqt_long_stack[0] = pqt1;
    pqt_double_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(short pqt0, long pqt1, long pqt2) {
    pqt_short_stack[0] = pqt0;
    pqt_long_stack[0] = pqt1;
    pqt_long_stack[1] = pqt2;
    slot();
}

void pqt_Slot::s(short pqt0, long pqt1, short pqt2) {
    pqt_short_stack[0] = pqt0;
    pqt_long_stack[0] = pqt1;
    pqt_short_stack[1] = pqt2;
    slot();
}

void pqt_Slot::s(short pqt0, long pqt1, bool pqt2) {
    pqt_short_stack[0] = pqt0;
    pqt_long_stack[0] = pqt1;
    pqt_bool_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(short pqt0, short pqt1, double pqt2) {
    pqt_short_stack[0] = pqt0;
    pqt_short_stack[1] = pqt1;
    pqt_double_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(short pqt0, short pqt1, long pqt2) {
    pqt_short_stack[0] = pqt0;
    pqt_short_stack[1] = pqt1;
    pqt_long_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(short pqt0, short pqt1, short pqt2) {
    pqt_short_stack[0] = pqt0;
    pqt_short_stack[1] = pqt1;
    pqt_short_stack[2] = pqt2;
    slot();
}

void pqt_Slot::s(short pqt0, short pqt1, bool pqt2) {
    pqt_short_stack[0] = pqt0;
    pqt_short_stack[1] = pqt1;
    pqt_bool_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(short pqt0, bool pqt1, double pqt2) {
    pqt_short_stack[0] = pqt0;
    pqt_bool_stack[0] = pqt1;
    pqt_double_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(short pqt0, bool pqt1, long pqt2) {
    pqt_short_stack[0] = pqt0;
    pqt_bool_stack[0] = pqt1;
    pqt_long_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(short pqt0, bool pqt1, short pqt2) {
    pqt_short_stack[0] = pqt0;
    pqt_bool_stack[0] = pqt1;
    pqt_short_stack[1] = pqt2;
    slot();
}

void pqt_Slot::s(short pqt0, bool pqt1, bool pqt2) {
    pqt_short_stack[0] = pqt0;
    pqt_bool_stack[0] = pqt1;
    pqt_bool_stack[1] = pqt2;
    slot();
}

void pqt_Slot::s(bool pqt0, double pqt1, double pqt2) {
    pqt_bool_stack[0] = pqt0;
    pqt_double_stack[0] = pqt1;
    pqt_double_stack[1] = pqt2;
    slot();
}

void pqt_Slot::s(bool pqt0, double pqt1, long pqt2) {
    pqt_bool_stack[0] = pqt0;
    pqt_double_stack[0] = pqt1;
    pqt_long_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(bool pqt0, double pqt1, short pqt2) {
    pqt_bool_stack[0] = pqt0;
    pqt_double_stack[0] = pqt1;
    pqt_short_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(bool pqt0, double pqt1, bool pqt2) {
    pqt_bool_stack[0] = pqt0;
    pqt_double_stack[0] = pqt1;
    pqt_bool_stack[1] = pqt2;
    slot();
}

void pqt_Slot::s(bool pqt0, long pqt1, double pqt2) {
    pqt_bool_stack[0] = pqt0;
    pqt_long_stack[0] = pqt1;
    pqt_double_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(bool pqt0, long pqt1, long pqt2) {
    pqt_bool_stack[0] = pqt0;
    pqt_long_stack[0] = pqt1;
    pqt_long_stack[1] = pqt2;
    slot();
}

void pqt_Slot::s(bool pqt0, long pqt1, short pqt2) {
    pqt_bool_stack[0] = pqt0;
    pqt_long_stack[0] = pqt1;
    pqt_short_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(bool pqt0, long pqt1, bool pqt2) {
    pqt_bool_stack[0] = pqt0;
    pqt_long_stack[0] = pqt1;
    pqt_bool_stack[1] = pqt2;
    slot();
}

void pqt_Slot::s(bool pqt0, short pqt1, double pqt2) {
    pqt_bool_stack[0] = pqt0;
    pqt_short_stack[0] = pqt1;
    pqt_double_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(bool pqt0, short pqt1, long pqt2) {
    pqt_bool_stack[0] = pqt0;
    pqt_short_stack[0] = pqt1;
    pqt_long_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(bool pqt0, short pqt1, short pqt2) {
    pqt_bool_stack[0] = pqt0;
    pqt_short_stack[0] = pqt1;
    pqt_short_stack[1] = pqt2;
    slot();
}

void pqt_Slot::s(bool pqt0, short pqt1, bool pqt2) {
    pqt_bool_stack[0] = pqt0;
    pqt_short_stack[0] = pqt1;
    pqt_bool_stack[1] = pqt2;
    slot();
}

void pqt_Slot::s(bool pqt0, bool pqt1, double pqt2) {
    pqt_bool_stack[0] = pqt0;
    pqt_bool_stack[1] = pqt1;
    pqt_double_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(bool pqt0, bool pqt1, long pqt2) {
    pqt_bool_stack[0] = pqt0;
    pqt_bool_stack[1] = pqt1;
    pqt_long_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(bool pqt0, bool pqt1, short pqt2) {
    pqt_bool_stack[0] = pqt0;
    pqt_bool_stack[1] = pqt1;
    pqt_short_stack[0] = pqt2;
    slot();
}

void pqt_Slot::s(bool pqt0, bool pqt1, bool pqt2) {
    pqt_bool_stack[0] = pqt0;
    pqt_bool_stack[1] = pqt1;
    pqt_bool_stack[2] = pqt2;
    slot();
}

void pqt_call() {
    typedef void (QObject::**PQT)();
    (pqt_obj->*pqt_func)();
}

void pqt_call_double() {
    typedef void (QObject::**PQT)(double);
    (pqt_obj->*pqt_func)(pqt_double_stack[0]);
}

void pqt_call_long() {
    typedef void (QObject::**PQT)(long);
    (pqt_obj->*pqt_func)(pqt_long_stack[0]);
}

void pqt_call_short() {
    typedef void (QObject::**PQT)(short);
    (pqt_obj->*pqt_func)(pqt_short_stack[0]);
}

void pqt_call_bool() {
    typedef void (QObject::**PQT)(bool);
    (pqt_obj->*pqt_func)(pqt_bool_stack[0]);
}

void pqt_call_double_double() {
    typedef void (QObject::**PQT)(double, double);
    (pqt_obj->*pqt_func)(pqt_double_stack[0], pqt_double_stack[1]);
}

void pqt_call_double_long() {
    typedef void (QObject::**PQT)(double, long);
    (pqt_obj->*pqt_func)(pqt_double_stack[0], pqt_long_stack[0]);
}

void pqt_call_double_short() {
    typedef void (QObject::**PQT)(double, short);
    (pqt_obj->*pqt_func)(pqt_double_stack[0], pqt_short_stack[0]);
}

void pqt_call_double_bool() {
    typedef void (QObject::**PQT)(double, bool);
    (pqt_obj->*pqt_func)(pqt_double_stack[0], pqt_bool_stack[0]);
}

void pqt_call_long_double() {
    typedef void (QObject::**PQT)(long, double);
    (pqt_obj->*pqt_func)(pqt_long_stack[0], pqt_double_stack[0]);
}

void pqt_call_long_long() {
    typedef void (QObject::**PQT)(long, long);
    (pqt_obj->*pqt_func)(pqt_long_stack[0], pqt_long_stack[1]);
}

void pqt_call_long_short() {
    typedef void (QObject::**PQT)(long, short);
    (pqt_obj->*pqt_func)(pqt_long_stack[0], pqt_short_stack[0]);
}

void pqt_call_long_bool() {
    typedef void (QObject::**PQT)(long, bool);
    (pqt_obj->*pqt_func)(pqt_long_stack[0], pqt_bool_stack[0]);
}

void pqt_call_short_double() {
    typedef void (QObject::**PQT)(short, double);
    (pqt_obj->*pqt_func)(pqt_short_stack[0], pqt_double_stack[0]);
}

void pqt_call_short_long() {
    typedef void (QObject::**PQT)(short, long);
    (pqt_obj->*pqt_func)(pqt_short_stack[0], pqt_long_stack[0]);
}

void pqt_call_short_short() {
    typedef void (QObject::**PQT)(short, short);
    (pqt_obj->*pqt_func)(pqt_short_stack[0], pqt_short_stack[1]);
}

void pqt_call_short_bool() {
    typedef void (QObject::**PQT)(short, bool);
    (pqt_obj->*pqt_func)(pqt_short_stack[0], pqt_bool_stack[0]);
}

void pqt_call_bool_double() {
    typedef void (QObject::**PQT)(bool, double);
    (pqt_obj->*pqt_func)(pqt_bool_stack[0], pqt_double_stack[0]);
}

void pqt_call_bool_long() {
    typedef void (QObject::**PQT)(bool, long);
    (pqt_obj->*pqt_func)(pqt_bool_stack[0], pqt_long_stack[0]);
}

void pqt_call_bool_short() {
    typedef void (QObject::**PQT)(bool, short);
    (pqt_obj->*pqt_func)(pqt_bool_stack[0], pqt_short_stack[0]);
}

void pqt_call_bool_bool() {
    typedef void (QObject::**PQT)(bool, bool);
    (pqt_obj->*pqt_func)(pqt_bool_stack[0], pqt_bool_stack[1]);
}

void pqt_call_double_double_double() {
    typedef void (QObject::**PQT)(double, double, double);
    (pqt_obj->*pqt_func)(pqt_double_stack[0], pqt_double_stack[1], pqt_double_stack[2]);
}

void pqt_call_double_double_long() {
    typedef void (QObject::**PQT)(double, double, long);
    (pqt_obj->*pqt_func)(pqt_double_stack[0], pqt_double_stack[1], pqt_long_stack[0]);
}

void pqt_call_double_double_short() {
    typedef void (QObject::**PQT)(double, double, short);
    (pqt_obj->*pqt_func)(pqt_double_stack[0], pqt_double_stack[1], pqt_short_stack[0]);
}

void pqt_call_double_double_bool() {
    typedef void (QObject::**PQT)(double, double, bool);
    (pqt_obj->*pqt_func)(pqt_double_stack[0], pqt_double_stack[1], pqt_bool_stack[0]);
}

void pqt_call_double_long_double() {
    typedef void (QObject::**PQT)(double, long, double);
    (pqt_obj->*pqt_func)(pqt_double_stack[0], pqt_long_stack[0], pqt_double_stack[1]);
}

void pqt_call_double_long_long() {
    typedef void (QObject::**PQT)(double, long, long);
    (pqt_obj->*pqt_func)(pqt_double_stack[0], pqt_long_stack[0], pqt_long_stack[1]);
}

void pqt_call_double_long_short() {
    typedef void (QObject::**PQT)(double, long, short);
    (pqt_obj->*pqt_func)(pqt_double_stack[0], pqt_long_stack[0], pqt_short_stack[0]);
}

void pqt_call_double_long_bool() {
    typedef void (QObject::**PQT)(double, long, bool);
    (pqt_obj->*pqt_func)(pqt_double_stack[0], pqt_long_stack[0], pqt_bool_stack[0]);
}

void pqt_call_double_short_double() {
    typedef void (QObject::**PQT)(double, short, double);
    (pqt_obj->*pqt_func)(pqt_double_stack[0], pqt_short_stack[0], pqt_double_stack[1]);
}

void pqt_call_double_short_long() {
    typedef void (QObject::**PQT)(double, short, long);
    (pqt_obj->*pqt_func)(pqt_double_stack[0], pqt_short_stack[0], pqt_long_stack[0]);
}

void pqt_call_double_short_short() {
    typedef void (QObject::**PQT)(double, short, short);
    (pqt_obj->*pqt_func)(pqt_double_stack[0], pqt_short_stack[0], pqt_short_stack[1]);
}

void pqt_call_double_short_bool() {
    typedef void (QObject::**PQT)(double, short, bool);
    (pqt_obj->*pqt_func)(pqt_double_stack[0], pqt_short_stack[0], pqt_bool_stack[0]);
}

void pqt_call_double_bool_double() {
    typedef void (QObject::**PQT)(double, bool, double);
    (pqt_obj->*pqt_func)(pqt_double_stack[0], pqt_bool_stack[0], pqt_double_stack[1]);
}

void pqt_call_double_bool_long() {
    typedef void (QObject::**PQT)(double, bool, long);
    (pqt_obj->*pqt_func)(pqt_double_stack[0], pqt_bool_stack[0], pqt_long_stack[0]);
}

void pqt_call_double_bool_short() {
    typedef void (QObject::**PQT)(double, bool, short);
    (pqt_obj->*pqt_func)(pqt_double_stack[0], pqt_bool_stack[0], pqt_short_stack[0]);
}

void pqt_call_double_bool_bool() {
    typedef void (QObject::**PQT)(double, bool, bool);
    (pqt_obj->*pqt_func)(pqt_double_stack[0], pqt_bool_stack[0], pqt_bool_stack[1]);
}

void pqt_call_long_double_double() {
    typedef void (QObject::**PQT)(long, double, double);
    (pqt_obj->*pqt_func)(pqt_long_stack[0], pqt_double_stack[0], pqt_double_stack[1]);
}

void pqt_call_long_double_long() {
    typedef void (QObject::**PQT)(long, double, long);
    (pqt_obj->*pqt_func)(pqt_long_stack[0], pqt_double_stack[0], pqt_long_stack[1]);
}

void pqt_call_long_double_short() {
    typedef void (QObject::**PQT)(long, double, short);
    (pqt_obj->*pqt_func)(pqt_long_stack[0], pqt_double_stack[0], pqt_short_stack[0]);
}

void pqt_call_long_double_bool() {
    typedef void (QObject::**PQT)(long, double, bool);
    (pqt_obj->*pqt_func)(pqt_long_stack[0], pqt_double_stack[0], pqt_bool_stack[0]);
}

void pqt_call_long_long_double() {
    typedef void (QObject::**PQT)(long, long, double);
    (pqt_obj->*pqt_func)(pqt_long_stack[0], pqt_long_stack[1], pqt_double_stack[0]);
}

void pqt_call_long_long_long() {
    typedef void (QObject::**PQT)(long, long, long);
    (pqt_obj->*pqt_func)(pqt_long_stack[0], pqt_long_stack[1], pqt_long_stack[2]);
}

void pqt_call_long_long_short() {
    typedef void (QObject::**PQT)(long, long, short);
    (pqt_obj->*pqt_func)(pqt_long_stack[0], pqt_long_stack[1], pqt_short_stack[0]);
}

void pqt_call_long_long_bool() {
    typedef void (QObject::**PQT)(long, long, bool);
    (pqt_obj->*pqt_func)(pqt_long_stack[0], pqt_long_stack[1], pqt_bool_stack[0]);
}

void pqt_call_long_short_double() {
    typedef void (QObject::**PQT)(long, short, double);
    (pqt_obj->*pqt_func)(pqt_long_stack[0], pqt_short_stack[0], pqt_double_stack[0]);
}

void pqt_call_long_short_long() {
    typedef void (QObject::**PQT)(long, short, long);
    (pqt_obj->*pqt_func)(pqt_long_stack[0], pqt_short_stack[0], pqt_long_stack[1]);
}

void pqt_call_long_short_short() {
    typedef void (QObject::**PQT)(long, short, short);
    (pqt_obj->*pqt_func)(pqt_long_stack[0], pqt_short_stack[0], pqt_short_stack[1]);
}

void pqt_call_long_short_bool() {
    typedef void (QObject::**PQT)(long, short, bool);
    (pqt_obj->*pqt_func)(pqt_long_stack[0], pqt_short_stack[0], pqt_bool_stack[0]);
}

void pqt_call_long_bool_double() {
    typedef void (QObject::**PQT)(long, bool, double);
    (pqt_obj->*pqt_func)(pqt_long_stack[0], pqt_bool_stack[0], pqt_double_stack[0]);
}

void pqt_call_long_bool_long() {
    typedef void (QObject::**PQT)(long, bool, long);
    (pqt_obj->*pqt_func)(pqt_long_stack[0], pqt_bool_stack[0], pqt_long_stack[1]);
}

void pqt_call_long_bool_short() {
    typedef void (QObject::**PQT)(long, bool, short);
    (pqt_obj->*pqt_func)(pqt_long_stack[0], pqt_bool_stack[0], pqt_short_stack[0]);
}

void pqt_call_long_bool_bool() {
    typedef void (QObject::**PQT)(long, bool, bool);
    (pqt_obj->*pqt_func)(pqt_long_stack[0], pqt_bool_stack[0], pqt_bool_stack[1]);
}

void pqt_call_short_double_double() {
    typedef void (QObject::**PQT)(short, double, double);
    (pqt_obj->*pqt_func)(pqt_short_stack[0], pqt_double_stack[0], pqt_double_stack[1]);
}

void pqt_call_short_double_long() {
    typedef void (QObject::**PQT)(short, double, long);
    (pqt_obj->*pqt_func)(pqt_short_stack[0], pqt_double_stack[0], pqt_long_stack[0]);
}

void pqt_call_short_double_short() {
    typedef void (QObject::**PQT)(short, double, short);
    (pqt_obj->*pqt_func)(pqt_short_stack[0], pqt_double_stack[0], pqt_short_stack[1]);
}

void pqt_call_short_double_bool() {
    typedef void (QObject::**PQT)(short, double, bool);
    (pqt_obj->*pqt_func)(pqt_short_stack[0], pqt_double_stack[0], pqt_bool_stack[0]);
}

void pqt_call_short_long_double() {
    typedef void (QObject::**PQT)(short, long, double);
    (pqt_obj->*pqt_func)(pqt_short_stack[0], pqt_long_stack[0], pqt_double_stack[0]);
}

void pqt_call_short_long_long() {
    typedef void (QObject::**PQT)(short, long, long);
    (pqt_obj->*pqt_func)(pqt_short_stack[0], pqt_long_stack[0], pqt_long_stack[1]);
}

void pqt_call_short_long_short() {
    typedef void (QObject::**PQT)(short, long, short);
    (pqt_obj->*pqt_func)(pqt_short_stack[0], pqt_long_stack[0], pqt_short_stack[1]);
}

void pqt_call_short_long_bool() {
    typedef void (QObject::**PQT)(short, long, bool);
    (pqt_obj->*pqt_func)(pqt_short_stack[0], pqt_long_stack[0], pqt_bool_stack[0]);
}

void pqt_call_short_short_double() {
    typedef void (QObject::**PQT)(short, short, double);
    (pqt_obj->*pqt_func)(pqt_short_stack[0], pqt_short_stack[1], pqt_double_stack[0]);
}

void pqt_call_short_short_long() {
    typedef void (QObject::**PQT)(short, short, long);
    (pqt_obj->*pqt_func)(pqt_short_stack[0], pqt_short_stack[1], pqt_long_stack[0]);
}

void pqt_call_short_short_short() {
    typedef void (QObject::**PQT)(short, short, short);
    (pqt_obj->*pqt_func)(pqt_short_stack[0], pqt_short_stack[1], pqt_short_stack[2]);
}

void pqt_call_short_short_bool() {
    typedef void (QObject::**PQT)(short, short, bool);
    (pqt_obj->*pqt_func)(pqt_short_stack[0], pqt_short_stack[1], pqt_bool_stack[0]);
}

void pqt_call_short_bool_double() {
    typedef void (QObject::**PQT)(short, bool, double);
    (pqt_obj->*pqt_func)(pqt_short_stack[0], pqt_bool_stack[0], pqt_double_stack[0]);
}

void pqt_call_short_bool_long() {
    typedef void (QObject::**PQT)(short, bool, long);
    (pqt_obj->*pqt_func)(pqt_short_stack[0], pqt_bool_stack[0], pqt_long_stack[0]);
}

void pqt_call_short_bool_short() {
    typedef void (QObject::**PQT)(short, bool, short);
    (pqt_obj->*pqt_func)(pqt_short_stack[0], pqt_bool_stack[0], pqt_short_stack[1]);
}

void pqt_call_short_bool_bool() {
    typedef void (QObject::**PQT)(short, bool, bool);
    (pqt_obj->*pqt_func)(pqt_short_stack[0], pqt_bool_stack[0], pqt_bool_stack[1]);
}

void pqt_call_bool_double_double() {
    typedef void (QObject::**PQT)(bool, double, double);
    (pqt_obj->*pqt_func)(pqt_bool_stack[0], pqt_double_stack[0], pqt_double_stack[1]);
}

void pqt_call_bool_double_long() {
    typedef void (QObject::**PQT)(bool, double, long);
    (pqt_obj->*pqt_func)(pqt_bool_stack[0], pqt_double_stack[0], pqt_long_stack[0]);
}

void pqt_call_bool_double_short() {
    typedef void (QObject::**PQT)(bool, double, short);
    (pqt_obj->*pqt_func)(pqt_bool_stack[0], pqt_double_stack[0], pqt_short_stack[0]);
}

void pqt_call_bool_double_bool() {
    typedef void (QObject::**PQT)(bool, double, bool);
    (pqt_obj->*pqt_func)(pqt_bool_stack[0], pqt_double_stack[0], pqt_bool_stack[1]);
}

void pqt_call_bool_long_double() {
    typedef void (QObject::**PQT)(bool, long, double);
    (pqt_obj->*pqt_func)(pqt_bool_stack[0], pqt_long_stack[0], pqt_double_stack[0]);
}

void pqt_call_bool_long_long() {
    typedef void (QObject::**PQT)(bool, long, long);
    (pqt_obj->*pqt_func)(pqt_bool_stack[0], pqt_long_stack[0], pqt_long_stack[1]);
}

void pqt_call_bool_long_short() {
    typedef void (QObject::**PQT)(bool, long, short);
    (pqt_obj->*pqt_func)(pqt_bool_stack[0], pqt_long_stack[0], pqt_short_stack[0]);
}

void pqt_call_bool_long_bool() {
    typedef void (QObject::**PQT)(bool, long, bool);
    (pqt_obj->*pqt_func)(pqt_bool_stack[0], pqt_long_stack[0], pqt_bool_stack[1]);
}

void pqt_call_bool_short_double() {
    typedef void (QObject::**PQT)(bool, short, double);
    (pqt_obj->*pqt_func)(pqt_bool_stack[0], pqt_short_stack[0], pqt_double_stack[0]);
}

void pqt_call_bool_short_long() {
    typedef void (QObject::**PQT)(bool, short, long);
    (pqt_obj->*pqt_func)(pqt_bool_stack[0], pqt_short_stack[0], pqt_long_stack[0]);
}

void pqt_call_bool_short_short() {
    typedef void (QObject::**PQT)(bool, short, short);
    (pqt_obj->*pqt_func)(pqt_bool_stack[0], pqt_short_stack[0], pqt_short_stack[1]);
}

void pqt_call_bool_short_bool() {
    typedef void (QObject::**PQT)(bool, short, bool);
    (pqt_obj->*pqt_func)(pqt_bool_stack[0], pqt_short_stack[0], pqt_bool_stack[1]);
}

void pqt_call_bool_bool_double() {
    typedef void (QObject::**PQT)(bool, bool, double);
    (pqt_obj->*pqt_func)(pqt_bool_stack[0], pqt_bool_stack[1], pqt_double_stack[0]);
}

void pqt_call_bool_bool_long() {
    typedef void (QObject::**PQT)(bool, bool, long);
    (pqt_obj->*pqt_func)(pqt_bool_stack[0], pqt_bool_stack[1], pqt_long_stack[0]);
}

void pqt_call_bool_bool_short() {
    typedef void (QObject::**PQT)(bool, bool, short);
    (pqt_obj->*pqt_func)(pqt_bool_stack[0], pqt_bool_stack[1], pqt_short_stack[0]);
}

void pqt_call_bool_bool_bool() {
    typedef void (QObject::**PQT)(bool, bool, bool);
    (pqt_obj->*pqt_func)(pqt_bool_stack[0], pqt_bool_stack[1], pqt_bool_stack[2]);
}

pqt_signal pqt_signal_matrix[] = {
    pqt_call,
    pqt_call_double,
    pqt_call_long,
    pqt_call_short,
    pqt_call_bool,
    pqt_call_double_double,
    pqt_call_double_long,
    pqt_call_double_short,
    pqt_call_double_bool,
    pqt_call_long_double,
    pqt_call_long_long,
    pqt_call_long_short,
    pqt_call_long_bool,
    pqt_call_short_double,
    pqt_call_short_long,
    pqt_call_short_short,
    pqt_call_short_bool,
    pqt_call_bool_double,
    pqt_call_bool_long,
    pqt_call_bool_short,
    pqt_call_bool_bool,
    pqt_call_double_double_double,
    pqt_call_double_double_long,
    pqt_call_double_double_short,
    pqt_call_double_double_bool,
    pqt_call_double_long_double,
    pqt_call_double_long_long,
    pqt_call_double_long_short,
    pqt_call_double_long_bool,
    pqt_call_double_short_double,
    pqt_call_double_short_long,
    pqt_call_double_short_short,
    pqt_call_double_short_bool,
    pqt_call_double_bool_double,
    pqt_call_double_bool_long,
    pqt_call_double_bool_short,
    pqt_call_double_bool_bool,
    pqt_call_long_double_double,
    pqt_call_long_double_long,
    pqt_call_long_double_short,
    pqt_call_long_double_bool,
    pqt_call_long_long_double,
    pqt_call_long_long_long,
    pqt_call_long_long_short,
    pqt_call_long_long_bool,
    pqt_call_long_short_double,
    pqt_call_long_short_long,
    pqt_call_long_short_short,
    pqt_call_long_short_bool,
    pqt_call_long_bool_double,
    pqt_call_long_bool_long,
    pqt_call_long_bool_short,
    pqt_call_long_bool_bool,
    pqt_call_short_double_double,
    pqt_call_short_double_long,
    pqt_call_short_double_short,
    pqt_call_short_double_bool,
    pqt_call_short_long_double,
    pqt_call_short_long_long,
    pqt_call_short_long_short,
    pqt_call_short_long_bool,
    pqt_call_short_short_double,
    pqt_call_short_short_long,
    pqt_call_short_short_short,
    pqt_call_short_short_bool,
    pqt_call_short_bool_double,
    pqt_call_short_bool_long,
    pqt_call_short_bool_short,
    pqt_call_short_bool_bool,
    pqt_call_bool_double_double,
    pqt_call_bool_double_long,
    pqt_call_bool_double_short,
    pqt_call_bool_double_bool,
    pqt_call_bool_long_double,
    pqt_call_bool_long_long,
    pqt_call_bool_long_short,
    pqt_call_bool_long_bool,
    pqt_call_bool_short_double,
    pqt_call_bool_short_long,
    pqt_call_bool_short_short,
    pqt_call_bool_short_bool,
    pqt_call_bool_bool_double,
    pqt_call_bool_bool_long,
    pqt_call_bool_bool_short,
    pqt_call_bool_bool_bool,
};

double pqt_gimmie_double(char) {
    dSP;
    double ret;

    double pqt_cache_tmp;
    pqt_cache_tmp = (double)SvNV(POPs); ret = *(double *)&pqt_cache_tmp;
    PUTBACK;
    return ret;
}

long pqt_gimmie_long(char c) {
    dSP;
    long ret;

    SV *arg = POPs;
    PUTBACK;

    switch(c) {

	case PQT_SCALAR:
	case PQT_SCALAR_REF:
	case PQT_HASH_REF:
	case PQT_ARRAY_REF:
	case PQT_DOT_DOT_DOT:
	    ret = (long)arg;
	    break;
	case PQT_FLOAT:
	{
	    float pqt_cache_tmp;
	    pqt_cache_tmp = (float)SvNV(arg); ret = *(long *)&pqt_cache_tmp;
	    break;
	}
	case PQT_OBJECT:
	    ret = (long)extract_ptr(arg);
	    break;
	case PQT_STRING:
	    ret = (long)SvPV(arg, na);
	    break;
	case PQT_LONG:
	case PQT_INT:
	    ret = (long)SvIV(arg);
	    break;
    }
    return ret;
}

short pqt_gimmie_short(char) {
    dSP;
    short ret;

    ret = (short)SvIV(POPs);
    PUTBACK;
    return ret;
}

bool pqt_gimmie_bool(char) {
    dSP;
    bool ret;

    ret = (bool)SvTRUE(POPs);
    PUTBACK;
    return ret;
}

XS(pqt_signal_stub) {
    dXSARGS;
    char *stashname = HvNAME(GvSTASH(CvGV(cv)));
    char *funcname = GvNAME(CvGV(cv));
    char *proto =
	SvPV(
	    safe_hv_fetch(
		(HV *)rv_check(
		    safe_hv_fetch(Signals, stashname, "Signals tampered")
		),
		funcname, "Signals tampered badly"
	    ), na
	);
    const char *crypt = reverse_proto(proto);

    if(items - 1 != *crypt)
	croak("Recieved %d arguments instead of %d for signal '%s'",
	      items - 1, *crypt, proto);

    pqt_ArgumentIterator local(crypt);
    pqt_ArgumentStack stack;
    pqt_signal pqt_hash_table[4];
    pqt_hash_table[0] = pqt_signal_matrix[0];

    const char *arg;
    int tot = 0;
    for(int i = 1; i <= *crypt; i++) {
	arg = ++local;
	tot += pqt_exp_tab[*crypt - i] * pqt_typeidx(*arg);
	pqt_hash_table[i] = pqt_signal_matrix[tot];

	switch(*arg) {

	    case PQT_DOUBLE:
		stack.inc_double(pqt_gimmie_double(*arg));
		break;
	    case PQT_LONG:
	    case PQT_INT:
	    case PQT_OBJECT:
	    case PQT_STRING:
	    case PQT_SCALAR:
	    case PQT_SCALAR_REF:
	    case PQT_HASH_REF:
	    case PQT_ARRAY_REF:
	    case PQT_DOT_DOT_DOT:
	    case PQT_FLOAT:
		stack.inc_long(pqt_gimmie_long(*arg));
		break;
	    case PQT_SHORT:
		stack.inc_short(pqt_gimmie_short(*arg));
		break;
	    case PQT_BOOL:
		stack.inc_bool(pqt_gimmie_bool(*arg));
		break;
	}
    }

    QObject *self = pQ(0, QObject);
    QConnectionList *clist = ((PQObject *)self)->receivers(proto);
    if(!clist || self->signalsBlocked()) XSRETURN_EMPTY;
    QConnectionListIt it(*clist);
    QConnection *c;
    while((c = it.current())) {
	++it;
	pqt_obj = (QSenderObject *)c->object();
	pqt_obj->setSender(self);
	pqt_m = c->member();
	(*pqt_hash_table[c->numArgs()])();
    }
    XSRETURN_EMPTY;
}

