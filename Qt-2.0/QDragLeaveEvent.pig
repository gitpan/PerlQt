#include <qevent.h>

struct QDragLeaveEvent : QEvent {
    QDragLeaveEvent();
    QDragLeaveEvent(const QDragLeaveEvent &);
} Qt::DragLeaveEvent;
