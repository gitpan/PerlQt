#include <qmime.h>

virtual class QMimeSource {
    virtual ~QMimeSource();
    abstract const char *format(int = 0) const;
    virtual bool provides(const char *) const;
    abstract QByteArray encodedData(const char *) const;
} Qt::MimeSource;
