#include <qpen.h>

struct QPen {
    QPen();
    QPen(Qt::PenStyle);
    QPen(const QPen &);
    QPen(const QColor &, uint = 0, Qt::PenStyle = Qt::SolidLine);
    ~QPen();
    QPen &operator = (const QPen &);
    bool operator == (const QPen &) const;
    bool operator != (const QPen &) const;
    const QColor &color() const;
    void setColor(const QColor &);
    void setStyle(Qt::PenStyle);
    void setWidth(uint);
    Qt::PenStyle style() const;
    uint width() const;
} Qt::Pen;
