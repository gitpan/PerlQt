#include <pqobject.h>
#include <qmetaobj.h>

const char *reverse_proto(const char *);
SV *reverse_proto(SV *);


#define PQT_MAX_ARGUMENT_COUNT 3
#define pqt_func (*((PQT)pqt_m))

#if !defined(Q_MOC_CONNECTIONLIST_DECLARED)
#define Q_MOC_CONNECTIONLIST_DECLARED
#include <qlist.h>
#if defined(Q_DECLARE)
Q_DECLARE(QListM,QConnection);
Q_DECLARE(QListIteratorM,QConnection);
#else
declare(QListM,QConnection);
declare(QListIteratorM,QConnection);
#endif
#endif

class pqt_Slot : public QObject {
    QObject *object;
    SV *objectsv;
    const char *name, *crypt;
    QString proto;

    void slot();

protected:
    void initMetaObject();

public:
    pqt_Slot(SV *, const char *);
    ~pqt_Slot();

    const char *className() const;
    QMetaObject *metaObject() const;

    static QMember stub(const char *);

    void s();
    void s(double);
    void s(long);
    void s(short);
    void s(bool);
    void s(double, double);
    void s(double, long);
    void s(double, short);
    void s(double, bool);
    void s(long, double);
    void s(long, long);
    void s(long, short);
    void s(long, bool);
    void s(short, double);
    void s(short, long);
    void s(short, short);
    void s(short, bool);
    void s(bool, double);
    void s(bool, long);
    void s(bool, short);
    void s(bool, bool);
    void s(double, double, double);
    void s(double, double, long);
    void s(double, double, short);
    void s(double, double, bool);
    void s(double, long, double);
    void s(double, long, long);
    void s(double, long, short);
    void s(double, long, bool);
    void s(double, short, double);
    void s(double, short, long);
    void s(double, short, short);
    void s(double, short, bool);
    void s(double, bool, double);
    void s(double, bool, long);
    void s(double, bool, short);
    void s(double, bool, bool);
    void s(long, double, double);
    void s(long, double, long);
    void s(long, double, short);
    void s(long, double, bool);
    void s(long, long, double);
    void s(long, long, long);
    void s(long, long, short);
    void s(long, long, bool);
    void s(long, short, double);
    void s(long, short, long);
    void s(long, short, short);
    void s(long, short, bool);
    void s(long, bool, double);
    void s(long, bool, long);
    void s(long, bool, short);
    void s(long, bool, bool);
    void s(short, double, double);
    void s(short, double, long);
    void s(short, double, short);
    void s(short, double, bool);
    void s(short, long, double);
    void s(short, long, long);
    void s(short, long, short);
    void s(short, long, bool);
    void s(short, short, double);
    void s(short, short, long);
    void s(short, short, short);
    void s(short, short, bool);
    void s(short, bool, double);
    void s(short, bool, long);
    void s(short, bool, short);
    void s(short, bool, bool);
    void s(bool, double, double);
    void s(bool, double, long);
    void s(bool, double, short);
    void s(bool, double, bool);
    void s(bool, long, double);
    void s(bool, long, long);
    void s(bool, long, short);
    void s(bool, long, bool);
    void s(bool, short, double);
    void s(bool, short, long);
    void s(bool, short, short);
    void s(bool, short, bool);
    void s(bool, bool, double);
    void s(bool, bool, long);
    void s(bool, bool, short);
    void s(bool, bool, bool);
};

enum pqt_ArgType {
    PQT_CONST,
    PQT_OBJECT,
    PQT_LONG,
    PQT_SHORT,
    PQT_INT,
    PQT_FLOAT,
    PQT_DOUBLE,
    PQT_LONG_DOUBLE,
    PQT_BOOL,
    PQT_STRING,
    PQT_SCALAR,
    PQT_SCALAR_REF,
    PQT_HASH_REF,
    PQT_ARRAY_REF,
    PQT_DOT_DOT_DOT,
};

extern HV *Crypt, *Signals;
extern XS(pqt_signal_stub);

