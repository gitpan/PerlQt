////////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 1998, Ashley Winters <jql@accessone.com> - All rights reserved.
//
// Since you aren't supposed to have this code, I certainly cannot
// permit your to redistribute it.
//

#ifndef PQT_H
#define PQT_H

#undef bool
#define QT_CLEAN_NAMESPACE
#define NO_DEBUG
#define NO_CHECK
#include "qglobal.h"
#undef ASSERT
#undef CHECK_PTR
#undef NO_CHECK
#undef NO_DEBUG

#define PQT_PROTONAME(name) PQT_ ## name
#define PQT_PROTO(name) void PQT_PROTONAME(name)(void *pqtCV)

#define PQT_BEGIN(method) pqt_begin(pqtCV, # method)
#define PQT_VIRTUAL(method) pqt_begin_virtual(# method)
#define PQT_END_ARGUMENTS pqt_lastargument()
#define PQT_END

#define pqt_serialize(object) pqt_munge_qdatastream(operator<<(*pqt_dstreamptr, *object))
#define pqt_deserialize(object, data) pqt_unmunge_qdatastream(data); operator>>(*pqt_dstreamptr, *object)

struct pqt_struct_methodlist {
    const char *pqt_method_name;
    void (*pqt_method_ptr)(void *);
};

struct pqt_struct_constantdata {
    const char *pqt_constant;
    long pqt_value;
};

struct pqt_classinfolist {
    const char *pqt_classname;
    pqt_struct_methodlist *pqt_methodlist;
    const char **pqt_isa;
    const char **pqt_alias;
    void *(*pqt_tocastfunc)(const char *, void *);
    void *(*pqt_fromcastfunc)(const char *, void *);
    bool pqt_suicidal;
};

struct pqt_exportinfolist {
    const char *pqt_hashname;
    pqt_struct_constantdata *pqt_constantdata;
    const char *pqt_type;
};

extern class QDataStream *pqt_dstreamptr;   // used for operator<< and operator>>

void pqt_load_module(const char *, pqt_classinfolist *, pqt_exportinfolist *);
class QApplication *pqt_QApplication_new(const char *);

void pqt_begin(void *, const char *);
void pqt_lastargument();
bool pqt_can_delete();
void pqt_destroy_object(void *, class pqt_virtual *);

int pqt_find_in_array(const char *, const char **);
void pqt_ambiguous(const char *, const char *);

const char *pqt_munge_qdatastream(class QDataStream &);
void pqt_unmunge_qdatastream(const char *);

void pqt_return_bool(bool);
void pqt_return_int(int);
void pqt_return_short(short);
void pqt_return_long(long);
void pqt_return_enum(unsigned int);
void pqt_return_uint(unsigned int);
void pqt_return_float(float);
void pqt_return_double(double);
void pqt_return_char(char);
void pqt_return_cstring(const char *);
void pqt_return_class(void *, const char *);
void pqt_return_const_class(const void *, const char *);
void pqt_return_new_class(void *, const char *, const char * = 0);

void pqt_return_qobjectlist(const void *);
void pqt_return_qwidgetlist(void *);
void pqt_return_qstring(const class QString *);
void pqt_return_qstringptr(const class QString *);
void pqt_return_qstrlist(const class QStrList *);
void pqt_return_qstrlistptr(const class QStrList *);
void pqt_return_qfileinfolist(const void *);               // Darn templates
void pqt_return_qtablist(const void *);                    // Darn them again

void pqt_return_ubits(const unsigned char *);
void pqt_return_ubitsarray(unsigned char **);        // Unusable
void pqt_return_ubitsarray(unsigned char **, int, int, int);
void pqt_return_uintarray(const unsigned int *);
void pqt_return_intarray(const int *);
void pqt_return_bits(const char *);       // unusable, I'm sure
void pqt_return_serial(const char *);
void pqt_return_nothing();
void pqt_return_nothing(void *);

int pqt_argumentcount();

int pqt_argument_int();
int pqt_argument_int(int);
long pqt_argument_long();
long pqt_argument_long(long);
unsigned int pqt_argument_uint();
unsigned int pqt_argument_uint(unsigned int);
short pqt_argument_short();
short pqt_argument_short(short);
double pqt_argument_double();
double pqt_argument_double(double);
float pqt_argument_float();
float pqt_argument_float(float);
bool pqt_argument_bool();
bool pqt_argument_bool(bool);
int pqt_argument_enum();
int pqt_argument_enum(int);
char pqt_argument_char();
char pqt_argument_char(char);
const char *pqt_argument_cstring();
const char *pqt_argument_cstring(const char *);

void *pqt_argument_class(const char *);
void *pqt_argument_class(const char *, void *);
void *pqt_argument_classref(const char *);
void *pqt_argument_classref(const char *, void *);
void *pqt_argument_class_destructor(const char *);
const void *pqt_argument_const_class(const char *);
const void *pqt_argument_const_class(const char *, const void *);
const void *pqt_argument_const_classref(const char *);
const void *pqt_argument_const_classref(const char *, const void *);

int &pqt_argument_intref();
int &pqt_argument_intref(const int &);
int *pqt_argument_intarray();
int *pqt_argument_intarray(int *);
class QString &pqt_argument_qstringref();
class QString &pqt_argument_qstringref(const class QString &);
class QString *pqt_argument_qstringptr();
class QString *pqt_argument_qstringptr(const class QString *);
class QStrList *pqt_argument_qstrlistptr();
class QStrList *pqt_argument_qstrlistptr(const class QStrList *);
class QByteArray *pqt_argument_qbytearray();
const char **pqt_argument_internal(const char ** = 0);

char *pqt_argument_bits();                  // unusable
char *pqt_argument_bits(unsigned int);
char *pqt_argument_bits(const char *);      // unusable
char *pqt_argument_bits(unsigned int, const char *);
unsigned int pqt_argument_bitslen();        // unusable
unsigned int pqt_argument_bitslen(unsigned int);
unsigned int pqt_argument_ubitslen();       // unusable
unsigned int pqt_argument_ubitslen(unsigned int);
short *pqt_argument_shortarray();           // unusable
short *pqt_argument_shortarray(int);
int pqt_argument_shortarrayitems();         // unusable
int pqt_argument_shortarrayitems(int);
const char *pqt_argument_serial();

void *pqt_argument_av_as_list();

const char **pqt_argument_xpm();
const char **pqt_argument_xpm(const char **);

int *pqt_argument_intptr();
int *pqt_argument_intptr(int *);
bool *pqt_argument_boolptr();
bool *pqt_argument_boolptr(bool *);
float *pqt_argument_floatptr();
float *pqt_argument_floatptr(float *);

class QObject *pqt_argument_sender();
class QObject *&pqt_argument_receiver();     // signal receiver
class QObject *&pqt_argument_unreceiver();
const char *pqt_argument_signal();
const char *pqt_argument_member();          // signal member
const unsigned char *pqt_argument_ubits();  // bit array

void *pqt_argument_skipptr();
int pqt_argument_skip();

void pqt_push_int(int);
void pqt_push_short(short);
void pqt_push_long(long);
void pqt_push_float(float);
void pqt_push_double(double);
void pqt_push_bool(bool);
void pqt_push_enum(int);
void pqt_push_char(char);
void pqt_push_cstring(const char *);

void pqt_push_class(void *, const char *);
void pqt_push_const_class(const void *, const char *);
void pqt_push_const_classref(const void *, const char *);

void pqt_push_sv(void *);
void pqt_push_sv_from_av(void *);

void pqt_push_signal(const char *);
void pqt_push_intref(int &);
void pqt_push_qstringref(const QString &);


int pqt_pop_int();
bool pqt_pop_bool();
const char *pqt_pop_cstring();
int pqt_pop_enum();
void *pqt_pop_class(const char *);
const void *pqt_pop_const_class(const char *);

void pqt_call_method(const char *);

unsigned int pqt_argument_info(int);
bool pqt_object_isa(int, const char *);

#define PQTTYPE_UNDEF    0x01
#define PQTTYPE_STRING   0x02
#define PQTTYPE_INT      0x04
#define PQTTYPE_FLOAT    0x08
#define PQTTYPE_BOOL     0x10
#define PQTTYPE_OBJECT   0x20
#define PQTTYPE_REF      0x40

#define pqt_is_undef(idx) (pqti##idx & PQTTYPE_UNDEF)
#define pqt_is_string(idx) (pqti##idx & PQTTYPE_STRING)
#define pqt_is_int(idx) (pqti##idx & PQTTYPE_INT)
#define pqt_is_float(idx) (pqti##idx & PQTTYPE_FLOAT)
#define pqt_is_bool(idx) (pqti##idx & PQTTYPE_BOOL)
#define pqt_is_number(idx) (pqt_is_int(idx) || pqt_is_float(idx))
#define pqt_is_object(idx) (pqti##idx & PQTTYPE_OBJECT)
#define pqt_is_class(idx, class) (pqt_is_object(idx) && pqt_object_isa(idx, class))

#endif  // PQT_H
