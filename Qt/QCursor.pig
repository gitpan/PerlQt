#include <qcursor.h>

struct QCursor {
    QCursor();
    QCursor(int);
    QCursor(const QCursor &);
    QCursor(const QPixmap &, int = -1, int = -1);
    QCursor(const QBitmap &, const QBitmap &, int = -1, int = -1);
    ~QCursor();
    QCursor &operator = (const QCursor &);
    const char *{serial} operator << () const : pig_serialize($this);
    void operator >> (const char *{serial}) : pig_deserialize($this, $1);
    const QBitmap *bitmap() const;
    HANDLE handle() const;
    QPoint hotSpot() const;
    const QBitmap *mask() const;
    static QPoint pos();
    static void setPos(const QPoint &);
    static void setPos(int, int);
    void setShape(int);
    int shape() const;
} Qt::Cursor;
