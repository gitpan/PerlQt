#include <qevent.h>

struct QWheelEvent : QEvent {
    QWheelEvent(const QPoint &, int, int);
    QWheelEvent(const QPoint &, const QPoint &, int, int);
    QWheelEvent(const QWheelEvent &);
    void accept();
    int delta() const;
    const QPoint &globalPos() const;
    int globalX() const;
    int globalY() const;
    void ignore();
    bool isAccepted() const;
    const QPoint &pos() const;
    Qt::ButtonState state() const;
    int x() const;
    int y() const;
} Qt::WheelEvent;
