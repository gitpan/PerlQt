#include <qdragobject.h>

suicidal virtual class QImageDrag : virtual QDragObject {
    QImageDrag(QWidget * = 0, const char * = 0);
    QImageDrag(QImage, QWidget * = 0, const char * = 0);
    virtual ~QImageDrag();
    static bool canDecode(const QMimeSource *);
    static bool decode(const QMimeSource *, QPixmap &);
    static bool decode(const QMimeSource *, QImage &);
    virtual QByteArray encodedData(const char *) const;
    virtual const char *format(int) const;
    virtual void setImage(QImage);
} Qt::ImageDrag;
