#include <qbrush.h>

struct QBrush {
    QBrush();
    QBrush(Qt::BrushStyle);
    QBrush(const QBrush &);
    QBrush(const QColor &, Qt::BrushStyle = Qt::SolidPattern);
    QBrush(const QColor &, const QPixmap &);
    ~QBrush();
    QBrush &operator = (const QBrush &);
    bool operator == (const QBrush &) const;
    bool operator != (const QBrush &) const;
    const char *{serial} operator << () const : pig_serialize($this);
    void operator >> (const char *{serial}) : pig_deserialize($this, $1);
    const QColor &color() const;
    QPixmap *pixmap() const;
    void setColor(const QColor &);
    void setPixmap(const QPixmap &);
    void setStyle(Qt::BrushStyle);
    Qt::BrushStyle style() const;
} Qt::Brush;
