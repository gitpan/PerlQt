#include <qdragobject.h>

virtual class QDragObject : virtual QObject, virtual QMimeSource {
    enum DragMode { DragDefault, DragCopy, DragMove, DragCopyOrMove };

    QDragObject(QWidget * = 0, const char * = 0);
    virtual ~QDragObject();
    bool drag();
    void dragCopy();
    bool dragMove();
    QPixmap pixmap() const;
    QPoint pixmapHotSpot() const;
    virtual void setPixmap(QPixmap);
    virtual void setPixmap(QPixmap, QPoint);
    static void setTarget(QWidget *);
    QWidget *source();
    static QWidget *target();
protected:
    virtual bool drag(QDragObject::DragMode);
} Qt::DragObject;
