#include <qevent.h>

struct QCustomEvent : QEvent {
    QCustomEvent(const QCustomEvent &);
} Qt::CustomEvent;
