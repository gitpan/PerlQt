#undef invert
#include <qwmatrix.h>

struct QWMatrix {
    QWMatrix();
    QWMatrix(const QWMatrix &);
    QWMatrix(double, double, double, double, double, double);
    bool operator == (const QWMatrix &) const;
    bool operator != (const QWMatrix &) const;
    QWMatrix &operator *= (const QWMatrix &);
    static QWMatrix operator * (const QWMatrix &, const QWMatrix &) : operator * ($0, $1);
    const char *{serial} operator << () const : pig_serialize($this);
    void operator >> (const char *{serial}) : pig_deserialize($this, $1);
    double dx() const;
    double dy() const;
    QWMatrix invert(bool * = 0);
    double m11() const;
    double m12() const;
    double m21() const;
    double m22() const;
    QPoint map(const QPoint &) const;
    QPointArray map(const QPointArray &) const;
    QRect map(const QRect &) const;
    void map(int, int, int *, int *) const;
    void map(double, double, double *, double *) const;
    void reset();
    QWMatrix &rotate(double);
    QWMatrix &scale(double, double);
    void setMatrix(double, double, double, double, double, double);
    QWMatrix &shear(double, double);
    QWMatrix &translate(double, double);
} Qt::WMatrix;
