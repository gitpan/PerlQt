#include <qevent.h>

struct QDragMoveEvent : QDropEvent {
    QDragMoveEvent(const QPoint &, QEvent::Type = QEvent::DragMove);
    QDragMoveEvent(const QDragMoveEvent &);
    void accept(bool = TRUE);
    void accept(const QRect &);
    QRect answerRect() const;
    void ignore();
    void ignore(const QRect &);
} Qt::DragMoveEvent;
