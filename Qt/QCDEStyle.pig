#include <qcdestyle.h>

virtual class QCDEStyle : virtual QMotifStyle {
    QCDEStyle(bool = FALSE);
    virtual int defaultFrameWidth() const;
    virtual void drawArrow(QPainter *, Qt::ArrowType, bool, int, int, int, int, const QColorGroup &, bool, const QBrush * = 0);
    virtual void drawExclusiveIndicator(QPainter *, int, int, int, int, const QColorGroup &, bool, bool = FALSE, bool = TRUE);
    virtual void drawIndicator(QPainter *, int, int, int, int, const QColorGroup &, int, bool = FALSE, bool = TRUE);
} Qt::CDEStyle;
