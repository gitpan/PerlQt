#include <qstring.h>
#include <qregexp.h>
#include <qapplication.h>
#include <qmetaobject.h>
#include <qvaluelist.h>
#include <private/qucomextra_p.h>
#include "smoke.h"

#undef DEBUG
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#ifndef __USE_POSIX
#define __USE_POSIX
#endif
#ifndef __USE_XOPEN
#define __USE_XOPEN
#endif
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#if PERL_VERSION == 6 && PERL_SUBVERSION == 0
  #include <qtextcodec.h>
#endif

#include "marshall.h"
#include "perlqt.h"
#include "smokeperl.h"

int smokeperl_free(pTHX_ SV *sv, MAGIC *mg) {
    smokeperl_object *o = (smokeperl_object*)mg->mg_ptr;

    const char *className = o->smoke->classes[o->classId].className;
    if(o->allocated && o->ptr) {
        if(do_debug & qtdb_gc) printf("Deleting (%s*)%p\n", className, o->ptr);
        SmokeClass sc(o->smoke, o->classId);
        if(sc.hasVirtual())
            unmapPointer(o, o->classId, 0);
        object_count --;
        char *methodName = new char[strlen(className) + 2];
        methodName[0] = '~';
        strcpy(methodName + 1, className);
        Smoke::Index nameId = o->smoke->idMethodName(methodName);
        Smoke::Index meth = o->smoke->findMethod(o->classId, nameId);
        if(meth > 0) {
            Smoke::Method &m = o->smoke->methods[o->smoke->methodMaps[meth].method];
            Smoke::ClassFn fn = o->smoke->classes[m.classId].classFn;
            Smoke::StackItem i[1];
            (*fn)(m.method, o->ptr, i);
        }
        delete[] methodName;
    }
    return 0;
}

struct mgvtbl vtbl_smoke = { 0, 0, 0, 0, smokeperl_free };

bool matches_arg(Smoke *smoke, Smoke::Index meth, Smoke::Index argidx, const char *argtype) {
    Smoke::Index *arg = smoke->argumentList + smoke->methods[meth].args + argidx;
    SmokeType type = SmokeType(smoke, *arg);
    if(type.name() && !strcmp(type.name(), argtype))
	return true;
    return false;
}

void *construct_copy(smokeperl_object *o) {
    const char *className = o->smoke->className(o->classId);
    int classNameLen = strlen(className);
    char *ccSig = new char[classNameLen + 2];       // copy constructor signature
    strcpy(ccSig, className);
    strcat(ccSig, "#");
    Smoke::Index ccId = o->smoke->idMethodName(ccSig);
    delete[] ccSig;

    char *ccArg = new char[classNameLen + 8];
    sprintf(ccArg, "const %s&", className);

    Smoke::Index ccMeth = o->smoke->findMethod(o->classId, ccId);
    if(!ccMeth)
	return 0;
    if(ccMeth > 0) {
	Smoke::Index method = o->smoke->methodMaps[ccMeth].method;
	// Make sure it's a copy constructor
	if(!matches_arg(o->smoke, method, 0, ccArg)) {
            delete[] ccArg;
	    return 0;
        }
        ccMeth = method;
    } else {
        // ambiguous method, pick the copy constructor
	Smoke::Index i = -ccMeth;
	while(o->smoke->ambiguousMethodList[i]) {
	    if(matches_arg(o->smoke, o->smoke->ambiguousMethodList[i], 0, ccArg))
		break;
	}
        delete[] ccArg;
	ccMeth = o->smoke->ambiguousMethodList[i];
	if(!ccMeth)
	    return 0;
    }

    // Okay, ccMeth is the copy constructor. Time to call it.
    Smoke::StackItem args[2];
    args[0].s_voidp = 0;
    args[1].s_voidp = o->ptr;
    Smoke::ClassFn fn = o->smoke->classes[o->classId].classFn;
    (*fn)(o->smoke->methods[ccMeth].method, 0, args);
    return args[0].s_voidp;
}

static void marshall_basetype(Marshall *m) {
    switch(m->type().elem()) {
      case Smoke::t_bool:
	switch(m->action()) {
	  case Marshall::FromSV:
	    m->item().s_bool = SvTRUE(m->var()) ? true : false;
	    break;
	  case Marshall::ToSV:
	    sv_setsv_mg(m->var(), boolSV(m->item().s_bool));
	    break;
	  default:
	    m->unsupported();
	    break;
	}
	break;
      case Smoke::t_char:
	switch(m->action()) {
	  case Marshall::FromSV:
	    m->item().s_char = (char)SvIV(m->var());
	    break;
	  case Marshall::ToSV:
	    sv_setiv_mg(m->var(), (IV)m->item().s_char);
	    break;
	  default:
	    m->unsupported();
	    break;
	}
	break;
      case Smoke::t_uchar:
	switch(m->action()) {
	  case Marshall::FromSV:
	    m->item().s_uchar = (unsigned char)SvIV(m->var());
	    break;
	  case Marshall::ToSV:
	    sv_setiv_mg(m->var(), (IV)m->item().s_uchar);
	    break;
	  default:
	    m->unsupported();
	    break;
	}
	break;
      case Smoke::t_short:
	switch(m->action()) {
	  case Marshall::FromSV:
	    m->item().s_short = (short)SvIV(m->var());
	    break;
	  case Marshall::ToSV:
	    sv_setiv_mg(m->var(), (IV)m->item().s_short);
	    break;
	  default:
	    m->unsupported();
	    break;
	}
	break;
      case Smoke::t_ushort:
	switch(m->action()) {
	  case Marshall::FromSV:
	    m->item().s_ushort = (unsigned short)SvIV(m->var());
	    break;
	  case Marshall::ToSV:
	    sv_setiv_mg(m->var(), (IV)m->item().s_ushort);
	    break;
	  default:
	    m->unsupported();
	    break;
	}
	break;
      case Smoke::t_int:
	switch(m->action()) {
	  case Marshall::FromSV:
	    m->item().s_int = (int)SvIV(m->var());
	    break;
	  case Marshall::ToSV:
	    sv_setiv_mg(m->var(), (IV)m->item().s_int);
	    break;
	  default:
	    m->unsupported();
	    break;
	}
	break;
      case Smoke::t_uint:
	switch(m->action()) {
	  case Marshall::FromSV:
	    m->item().s_uint = (unsigned int)SvIV(m->var());
	    break;
	  case Marshall::ToSV:
	    sv_setiv_mg(m->var(), (IV)m->item().s_uint);
	    break;
	  default:
	    m->unsupported();
	    break;
	}
	break;
      case Smoke::t_long:
	switch(m->action()) {
	  case Marshall::FromSV:
	    m->item().s_long = (long)SvIV(m->var());
	    break;
	  case Marshall::ToSV:
	    sv_setiv_mg(m->var(), (IV)m->item().s_long);
	    break;
	  default:
	    m->unsupported();
	    break;
	}
	break;
      case Smoke::t_ulong:
	switch(m->action()) {
	  case Marshall::FromSV:
	    m->item().s_ulong = (unsigned long)SvIV(m->var());
	    break;
	  case Marshall::ToSV:
	    sv_setiv_mg(m->var(), (IV)m->item().s_ulong);
	    break;
	  default:
	    m->unsupported();
	    break;
	}
	break;
      case Smoke::t_float:
	switch(m->action()) {
	  case Marshall::FromSV:
	    m->item().s_float = (float)SvNV(m->var());
	    break;
	  case Marshall::ToSV:
	    sv_setnv_mg(m->var(), (NV)m->item().s_float);
	    break;
	  default:
	    m->unsupported();
	    break;
	}
	break;
      case Smoke::t_double:
	switch(m->action()) {
	  case Marshall::FromSV:
	    m->item().s_double = (double)SvNV(m->var());
	    break;
	  case Marshall::ToSV:
	    sv_setnv_mg(m->var(), (NV)m->item().s_double);
	    break;
	  default:
	    m->unsupported();
	    break;
	}
	break;
      case Smoke::t_enum:
	switch(m->action()) {
	  case Marshall::FromSV:
	    m->item().s_enum = (long)SvIV(m->var());
	    break;
	  case Marshall::ToSV:
	    sv_setiv_mg(m->var(), (IV)m->item().s_enum);
	    break;
	  default:
	    m->unsupported();
	    break;
	}
	break;
      case Smoke::t_class:
	switch(m->action()) {
	  case Marshall::FromSV:
	    {
		smokeperl_object *o = sv_obj_info(m->var());
		if(!o || !o->ptr) {
                    if(m->type().isRef()) {
                        warn("References can't be null or undef\n");
                        m->unsupported();
                    }
		    m->item().s_class = 0;
		    break;
		}
		void *ptr = o->ptr;
		if(!m->cleanup() && m->type().isStack()) {
		    ptr = construct_copy(o);
		}
		const Smoke::Class &c = m->smoke()->classes[m->type().classId()];
		ptr = o->smoke->cast(
		    ptr,				// pointer
		    o->classId,				// from
		    o->smoke->idClass(c.className)	// to
		);
		m->item().s_class = ptr;
		break;
	    }
	    break;
	  case Marshall::ToSV:
	    {
		if(!m->item().s_voidp) {
		    sv_setsv_mg(m->var(), &PL_sv_undef);
		    break;
		}
		void *p = m->item().s_voidp;
		SV *obj = getPointerObject(p);
		if(obj) {
		    sv_setsv_mg(m->var(), obj);
		    break;
		}
		HV *hv = newHV();
		obj = newRV_noinc((SV*)hv);
		// TODO: Generic mapping from C++ classname to Qt classname

		smokeperl_object o;
		o.smoke = m->smoke();
		o.classId = m->type().classId();
		o.ptr = p;
		o.allocated = false;

		if(m->type().isStack())
		    o.allocated = true;

		sv_magic((SV*)hv, sv_qapp, '~', (char*)&o, sizeof(o));
		MAGIC *mg = mg_find((SV*)hv, '~');
		mg->mg_virtual = &vtbl_smoke;

		char *buf = m->smoke()->binding->className(m->type().classId());
		sv_bless(obj, gv_stashpv(buf, TRUE));
		delete[] buf;

		sv_setsv_mg(m->var(), obj);
		SvREFCNT_dec(obj);
	    }
	    break;
	  default:
	    m->unsupported();
	    break;
	}
	break;
      default:
	m->unsupported();
	break;
    }
}

static void marshall_void(Marshall *m) {}
static void marshall_unknown(Marshall *m) {
    m->unsupported();
}

static void marshall_charP(Marshall *m) {
    switch(m->action()) {
      case Marshall::FromSV:
	{
	    SV *sv = m->var();
	    if(!SvOK(sv)) {
		m->item().s_voidp = 0;
		break;
	    }
	    if(m->cleanup())
		m->item().s_voidp = SvPV_nolen(sv);
	    else {
		STRLEN len;
		char *svstr = SvPV(sv, len);
		char *str = new char [len + 1];
		strncpy(str, svstr, len);
		str[len] = 0;
		m->item().s_voidp = str;
	    }
	}
	break;
      case Marshall::ToSV:
	{
	    char *p = (char*)m->item().s_voidp;
	    if(p)
		sv_setpv_mg(m->var(), p);
	    else
		sv_setsv_mg(m->var(), &PL_sv_undef);
	    if(m->cleanup())
		delete[] p;
	}
	break;
      default:
	m->unsupported();
	break;
    }
}

void marshall_ucharP(Marshall *m) {
    switch(m->action()) {
      case Marshall::FromSV:
	{
	    SV *sv = m->var();
	    if(!SvOK(sv)) {
		m->item().s_voidp = 0;
		break;
	    }
	    if(m->cleanup())
		m->item().s_voidp = SvPV_nolen(sv);
	    else {
		STRLEN len;
		char *svstr = SvPV(sv, len);
		char *str = new char [len + 1];
		strncpy(str, svstr, len);
		str[len] = 0;
		m->item().s_voidp = str;
	    }
	}
	break;
      case Marshall::ToSV:
	// This will need to be implemented with some sort of tied array
      default:
	m->unsupported();
	break;
    }
}

static void marshall_QString(Marshall *m) {
    switch(m->action()) {
      case Marshall::FromSV:
	{
	    QString *s = 0;
	    if(SvOK(m->var()) || m->type().isStack()) {
                if(SvUTF8(m->var()))
		    s = new QString(QString::fromUtf8(SvPV_nolen(m->var())));
                else if(PL_hints & HINT_LOCALE)
                    s = new QString(QString::fromLocal8Bit(SvPV_nolen(m->var()))); 
                else
                    s = new QString(QString::fromLatin1(SvPV_nolen(m->var())));
            }
            else if(m->type().isRef())
                s = new QString;
	    m->item().s_voidp = s;
	    m->next();
	    if(s && m->cleanup())
		delete s;
	}
	break;
      case Marshall::ToSV:
	{
	    QString *s = (QString*)m->item().s_voidp;
	    if(s) {
		sv_setpv_mg(m->var(), (const char *)s->utf8());
                SvUTF8_on(m->var());                                
            }
	    else
		sv_setsv_mg(m->var(), &PL_sv_undef);
	    if(m->cleanup())
		delete s;
	}
	break;
      default:
	m->unsupported();
	break;
    }
}

static void marshall_QCString(Marshall *m) {
    switch(m->action()) {
      case Marshall::FromSV:
	{
	    QCString *s = 0;
	    if(SvOK(m->var()) || m->type().isStack())
		s = new QCString(SvPV_nolen(m->var()));
	    m->item().s_voidp = s;
	    m->next();
	    if(s && m->cleanup())
		delete s;
	}
	break;
      case Marshall::ToSV:
	{
	    QCString *s = (QCString*)m->item().s_voidp;
	    if(s) {
		sv_setpv_mg(m->var(), (const char *)*s);
                #if PERL_VERSION == 6 && PERL_SUBVERSION == 0
                QTextCodec* c = QTextCodec::codecForName("utf8");
                if(c->heuristicContentMatch((const char *)*s, s->length()) >= 0)
                #else
                if(is_utf8_string((U8 *)(const char *)*s, s->length()))
                #endif
                    SvUTF8_on(m->var());
            }
            else
		sv_setsv_mg(m->var(), &PL_sv_undef);

	    if(m->cleanup())
		delete s;
	}
	break;
      default:
	m->unsupported();
	break;
    }
}

static void marshall_QCOORD_array(Marshall *m) {
    switch(m->action()) {
      case Marshall::FromSV:
	{
	    SV *sv = m->var();
	    if(!SvROK(sv) || SvTYPE(SvRV(sv)) != SVt_PVAV ||
		av_len((AV*)SvRV(sv)) < 0) {
		m->item().s_voidp = 0;
		break;
	    }
	    AV *av = (AV*)SvRV(sv);
	    int count = av_len(av);
	    QCOORD *coord = new QCOORD[count + 2];
	    for(int i = 0; i <= count; i++) {
		SV **svp = av_fetch(av, i, 0);
		coord[i] = svp ? SvIV(*svp) : 0;
	    }
	    m->item().s_voidp = coord;
	    m->next();
	}
	break;
      default:
	m->unsupported();
    }
}

static void marshall_intR(Marshall *m) {
    switch(m->action()) {
      case Marshall::FromSV:
	{
	    SV *sv = m->var();
	    if(m->type().isPtr() &&		// is pointer
	       !SvOK(sv) && SvREADONLY(sv)) {   // and real undef
		m->item().s_voidp = 0;		// pass null pointer
		break;
	    }
	    if(m->cleanup()) {
		int i = SvIV(sv);
		m->item().s_voidp = &i;
		m->next();
		sv_setiv_mg(sv, (IV)i);
	    } else {
		m->item().s_voidp = new int((int)SvIV(sv));
		if(PL_dowarn)
		    warn("Leaking memory from int& handler");
	    }
	}
	break;
      case Marshall::ToSV:
	{
	    int *ip = (int*)m->item().s_voidp;
	    SV *sv = m->var();
	    if(!ip) {
		sv_setsv_mg(sv, &PL_sv_undef);
		break;
	    }
	    sv_setiv_mg(sv, *ip);
	    m->next();
	    if(!m->type().isConst())
		*ip = (int)SvIV(sv);
	}
	break;
      default:
	m->unsupported();
	break;
    }
}

static void marshall_boolR(Marshall *m) {
    switch(m->action()) {
      case Marshall::FromSV:
	{
	    SV *sv = m->var();
	    if(m->type().isPtr() &&		// is pointer
	       !SvOK(sv) && SvREADONLY(sv)) {   // and real undef
		m->item().s_voidp = 0;		// pass null pointer
		break;
	    }
	    if(m->cleanup()) {
		bool i = SvTRUE(sv)? true : false;
		m->item().s_voidp = &i;
		m->next();
		sv_setsv_mg(sv, boolSV(i));
	    } else {
		m->item().s_voidp = new bool(SvTRUE(sv)?true:false);
		if(PL_dowarn)
		    warn("Leaking memory from bool& handler");
	    }
	}
	break;
      case Marshall::ToSV:
	{
	    bool *ip = (bool*)m->item().s_voidp;
	    SV *sv = m->var();
	    if(!ip) {
		sv_setsv_mg(sv, &PL_sv_undef);
		break;
	    }
	    sv_setsv_mg(sv, boolSV(*ip));
	    m->next();
	    if(!m->type().isConst())
		*ip = SvTRUE(sv)? true : false;
	}
	break;
      default:
	m->unsupported();
	break;
    }
}

static void marshall_charP_array(Marshall *m) {
    switch(m->action()) {
      case Marshall::FromSV:
	{
	    SV *sv = m->var();
	    if(!SvROK(sv) || SvTYPE(SvRV(sv)) != SVt_PVAV ||
		av_len((AV*)SvRV(sv)) < 0) {
		m->item().s_voidp = 0;
		break;
	    }

	    AV *arglist = (AV*)SvRV(sv);
	    int count = av_len(arglist);
	    char **argv = new char *[count + 2];
	    int i;
	    for(i = 0; i <= count; i++) {
		SV **item = av_fetch(arglist, i, 0);
		if(!item || !SvOK(*item)) {
		    argv[i] = new char[1];
		    argv[i][0] = 0;	// should undef warn?
		    continue;
		}

		STRLEN len;
		char *s = SvPV(*item, len);
		argv[i] = new char[len + 1];
		strncpy(argv[i], s, len);
		argv[i][len] = 0;	// null terminazi? yes
	    }
	    argv[i] = 0;
	    m->item().s_voidp = argv;
	    m->next();
	    if(m->cleanup()) {
		av_clear(arglist);
		for(i = 0; argv[i]; i++)
		    av_push(arglist, newSVpv(argv[i], 0));

		// perhaps we should check current_method?   
	    }
	}
	break;
      default:
	m->unsupported();
	break;
    }
}

void marshall_QStringList(Marshall *m) {
    switch(m->action()) {
      case Marshall::FromSV:
	{
	    SV *sv = m->var();
	    if(!SvROK(sv) || SvTYPE(SvRV(sv)) != SVt_PVAV ||
		av_len((AV*)SvRV(sv)) < 0) {
		m->item().s_voidp = 0;
		break;
	    }
	    AV *list = (AV*)SvRV(sv);
	    int count = av_len(list);
	    QStringList *stringlist = new QStringList;
	    int i;
            bool lc = PL_hints & HINT_LOCALE;
	    for(i = 0; i <= count; i++) {
		SV **item = av_fetch(list, i, 0);
		if(!item || !SvOK(*item)) {
		    stringlist->append(QString());
		    continue;
		}

                if(SvUTF8(*item))
		    stringlist->append(QString::fromUtf8(SvPV_nolen(*item)));
                else if(lc)
                    stringlist->append(QString::fromLocal8Bit(SvPV_nolen(*item))); 
                else
                    stringlist->append(QString::fromLatin1(SvPV_nolen(*item)));
	    }

	    m->item().s_voidp = stringlist;
	    m->next();

	    if(m->cleanup()) {
		av_clear(list);
		for(QStringList::Iterator it = stringlist->begin();
		    it != stringlist->end();
		    ++it)
		    av_push(list, newSVpv((const char *)*it, 0));
		delete stringlist;
	    }
	}
	break;
      case Marshall::ToSV:
	{
	    QStringList *stringlist = (QStringList*)m->item().s_voidp;
	    if(!stringlist) {
		sv_setsv_mg(m->var(), &PL_sv_undef);
		break;
	    }

	    AV *av = newAV();
	    {
		SV *rv = newRV_noinc((SV*)av);
		sv_setsv_mg(m->var(), rv);
		SvREFCNT_dec(rv);
	    }

	    for(QStringList::Iterator it = stringlist->begin();
		it != stringlist->end();
		++it) {
                    SV *sv = newSVpv((const char *)(*it).utf8(), 0);
                    SvUTF8_on(sv);
		    av_push(av, sv);
                }
	    if(m->cleanup())
		delete stringlist;
	}
	break;
      default:
	m->unsupported();
	break;
    }
}

void marshall_QValueListInt(Marshall *m) {
    switch(m->action()) {
      case Marshall::FromSV:
	{
	    SV *sv = m->var();
	    if(!SvROK(sv) || SvTYPE(SvRV(sv)) != SVt_PVAV ||
		av_len((AV*)SvRV(sv)) < 0) {
		m->item().s_voidp = 0;
		break;
	    }
	    AV *list = (AV*)SvRV(sv);
	    int count = av_len(list);
	    QValueList<int> *valuelist = new QValueList<int>;
	    int i;
	    for(i = 0; i <= count; i++) {
		SV **item = av_fetch(list, i, 0);
		if(!item || !SvOK(*item)) {
		    valuelist->append(0);
		    continue;
		}

		valuelist->append(SvIV(*item));
	    }

	    m->item().s_voidp = valuelist;
	    m->next();

	    if(m->cleanup()) {
		av_clear(list);
		for(QValueListIterator<int> it = valuelist->begin();
		    it != valuelist->end();
		    ++it)
		    av_push(list, newSViv((int)*it));
		delete valuelist;
	    }
	}
	break;
      case Marshall::ToSV:
	{
	    QValueList<int> *valuelist = (QValueList<int>*)m->item().s_voidp;
	    if(!valuelist) {
		sv_setsv_mg(m->var(), &PL_sv_undef);
		break;
	    }

	    AV *av = newAV();
	    {
		SV *rv = newRV_noinc((SV*)av);
		sv_setsv_mg(m->var(), rv);
		SvREFCNT_dec(rv);
	    }

	    for(QValueListIterator<int> it = valuelist->begin();
		it != valuelist->end();
		++it)
		av_push(av, newSViv((int)*it));
	    if(m->cleanup())
		delete valuelist;
	}
	break;
      default:
	m->unsupported();
	break;
    }
}

void marshall_voidP(Marshall *m) {
    switch(m->action()) {
      case Marshall::FromSV:
	{
	    SV *sv = m->var();
	    if(SvROK(sv) && SvRV(sv) && SvOK(SvRV(sv)))
		m->item().s_voidp = (void*)SvIV(SvRV(m->var()));
	    else
		m->item().s_voidp = 0;
	}
	break;
      case Marshall::ToSV:
	{
	    SV *sv = newSViv((IV)m->item().s_voidp);
	    SV *rv = newRV_noinc(sv);
	    sv_setsv_mg(m->var(), rv);
	    SvREFCNT_dec(rv);
	}
	break;
      default:
	m->unsupported();
	break;
    }
}

void marshall_QRgb_array(Marshall *m) {
    switch(m->action()) {
      case Marshall::FromSV:
	{
	    SV *sv = m->var();
	    if(!SvROK(sv) || SvTYPE(SvRV(sv)) != SVt_PVAV ||
		av_len((AV*)SvRV(sv)) < 0) {
		m->item().s_voidp = 0;
		break;
	    }
	    AV *list = (AV*)SvRV(sv);
	    int count = av_len(list);
	    QRgb *rgb = new QRgb[count + 2];
	    int i;
	    for(i = 0; i <= count; i++) {
		SV **item = av_fetch(list, i, 0);
		if(!item || !SvOK(*item)) {
		    rgb[i] = 0;
		    continue;
		}

		rgb[i] = SvIV(*item);
	    }
	    m->item().s_voidp = rgb;
	    m->next();
	    if(m->cleanup())
		delete[] rgb;
	}
	break;
      case Marshall::ToSV:
	// Implement this with a tied array or something
      default:
	m->unsupported();
	break;
    }
}

TypeHandler Qt_handlers[] = {
    { "QString", marshall_QString },
    { "QString&", marshall_QString },
    { "QString*", marshall_QString },
    { "QCString", marshall_QCString },
    { "QCString&", marshall_QCString },
    { "QCString*", marshall_QCString },
    { "QStringList", marshall_QStringList },
    { "QStringList&", marshall_QStringList },
    { "QStringList*", marshall_QStringList },
    { "int&", marshall_intR },
    { "int*", marshall_intR },
    { "bool&", marshall_boolR },
    { "bool*", marshall_boolR },
    { "char*", marshall_charP },
    { "char**", marshall_charP_array },
    { "uchar*", marshall_ucharP },
    { "QRgb*", marshall_QRgb_array },
    { "QUObject*", marshall_voidP },
    { "const QCOORD*", marshall_QCOORD_array },
    { "void", marshall_void },
    { "QValueList<int>", marshall_QValueListInt },
    { "QValueList<int>*", marshall_QValueListInt },
    { "QValueList<int>&", marshall_QValueListInt },
    { 0, 0 }
};

static HV *type_handlers = 0;

void install_handlers(TypeHandler *h) {
    if(!type_handlers) type_handlers = newHV();
    while(h->name) {
	hv_store(type_handlers, h->name, strlen(h->name), newSViv((IV)h), 0);
	h++;
    }
}

Marshall::HandlerFn getMarshallFn(const SmokeType &type) {
    if(type.elem())
	return marshall_basetype;
    if(!type.name())
	return marshall_void;
    if(!type_handlers) {
	return marshall_unknown;
    }
    U32 len = strlen(type.name());
    SV **svp = hv_fetch(type_handlers, type.name(), len, 0);
    if(!svp && type.isConst() && len > 6)
	svp = hv_fetch(type_handlers, type.name() + 6, len - 6, 0);
    if(svp) {
	TypeHandler *h = (TypeHandler*)SvIV(*svp);
	return h->fn;
    }
    return marshall_unknown;
}
