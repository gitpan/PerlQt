#include <qevent.h>

struct QPaintEvent : QEvent {
    QPaintEvent(const QRegion &, bool = TRUE);
    QPaintEvent(const QRect &, bool = TRUE);
    QPaintEvent(const QPaintEvent &);
    bool erased() const;
    const QRect &rect() const;
    const QRegion &region() const;
} Qt::PaintEvent;
