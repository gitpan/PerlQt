#include <qdragobject.h>

suicidal virtual class QTextDrag : virtual QDragObject {
    QTextDrag(QWidget * = 0, const char * = 0);
    QTextDrag(const QString &, QWidget * = 0, const char * = 0);
    virtual ~QTextDrag();
    static bool canDecode(const QMimeSource *);
    static bool decode(const QMimeSource *, QString &);
    static bool decode(const QMimeSource *, QString &, const char *);
    virtual QByteArray encodedData(const char *) const;
    virtual const char *format(int) const;
    virtual void setSubtype(const char *);
    virtual void setText(const QString &);
} Qt::TextDrag;
