#include <qsizegrip.h>

suicidal virtual class QSizeGrip : virtual QWidget {
    QSizeGrip(QWidget *, const char * = 0);
    virtual ~QSizeGrip();
    virtual QSize sizeHint() const;
    virtual QSizePolicy sizePolicy() const;
protected:
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void paintEvent(QPaintEvent *);
} Qt::SizeGrip;
