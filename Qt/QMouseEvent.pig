#include <qevent.h>

struct QMouseEvent : QEvent {
    QMouseEvent(QEvent::Type, const QPoint &, int, int);
    QMouseEvent(QEvent::Type, const QPoint &, const QPoint &, int, int);
    Qt::ButtonState button() const;
    const QPoint &globalPos() const;
    int globalX() const;
    int globalY() const;
    const QPoint &pos() const;
    Qt::ButtonState state() const;
    Qt::ButtonState stateAfter() const;
    int x() const;
    int y() const;
} Qt::MouseEvent;
