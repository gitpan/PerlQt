#include <qevent.h>

struct QHideEvent : QEvent {
    QHideEvent(bool);
    QHideEvent(const QHideEvent &);
    bool spontaneous() const;
} Qt::HideEvent;
