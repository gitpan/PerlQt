#include <qevent.h>

struct QChildEvent : QEvent {
    QChildEvent(const QChildEvent &);
    QChildEvent(QEvent::Type, QObject *);
    QObject *child() const;
    bool inserted() const;
    bool removed() const;
} Qt::ChildEvent;
