#include <qevent.h>

struct QFocusEvent : QEvent {
    QFocusEvent(QEvent::Type);
    QFocusEvent(const QFocusEvent &);
    bool gotFocus() const;
    bool lostFocus() const;
} Qt::FocusEvent;

