#include <qevent.h>

struct QDragEnterEvent : QDragMoveEvent {
    QDragEnterEvent(const QPoint &);
    QDragEnterEvent(const QDragEnterEvent &);
} Qt::DragEnterEvent;
