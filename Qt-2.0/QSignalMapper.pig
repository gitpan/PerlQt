#include <qsignalmapper.h>

suicidal virtual class QSignalMapper : virtual QObject {
    QSignalMapper(QObject *, const char * = 0);
    virtual ~QSignalMapper();
    void map() slot;
    void removeMappings(const QObject *);
    virtual void setMapping(const QObject *, int);
    virtual void setMapping(const QObject *, const QString &);
protected:
    void mapped(int) signal;
    void mapped(const QString &) signal;
} Qt::SignalMapper;
