#include <qevent.h>

struct QShowEvent : QEvent {
    QShowEvent(bool);
    QShowEvent(const QShowEvent &);
    bool spontaneous() const;
} Qt::ShowEvent;
