#include <qpointarray.h>

struct QPointArray {
    QPointArray();
    QPointArray(int);
    QPointArray(const QPointArray &);
    QPointArray(const QRect &, bool = FALSE);
    QPointArray(int {@qt_pointarrayitems(1)}, const QCOORD *{shortarray});
    ~QPointArray();
    QPointArray &operator = (const QPointArray &);
    bool operator == (const QPointArray &) const;
    bool operator != (const QPointArray &) const;
    const char *{serial} operator << () const : pig_serialize($this);
    void operator >> (const char *{serial}) : pig_deserialize($this, $1);
    QRect boundingRect() const;
    void makeArc(int, int, int, int, int, int);
    void makeArc(int, int, int, int, int, int, const QWMatrix &);
    void makeEllipse(int, int, int, int);
    QPoint point(uint) const;
    void point(uint, int *, int *) const;
    void putPoints(int, int {@qt_pointarrayitems(3)}, const QCOORD *{shortarray});
    QPointArray quadBezier() const;
    void setPoint(uint, const QPoint &);
    void setPoint(uint, int, int);
    void setPoints(int {@qt_pointarrayitems(2)}, const QCOORD *{shortarray});
;    void *shortPoints(int = 0, int = -1) const;
    void translate(int, int);
} Qt::PointArray;
