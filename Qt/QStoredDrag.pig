#include <qdragobject.h>

suicidal virtual class QStoredDrag : virtual QDragObject {
    QStoredDrag(const char *, QWidget * = 0, const char * = 0);
    virtual ~QStoredDrag();
    virtual QByteArray encodedData(const char *) const;
    virtual const char *format(int) const;
    virtual void setEncodedData(const QByteArray &);
} Qt::StoredDrag;
