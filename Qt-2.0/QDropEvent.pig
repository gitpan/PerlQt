#include <qevent.h>

struct QDropEvent : QEvent, QMimeSource {
    enum Action { Copy, Link, Move, Private, UserAction };

    QDropEvent(const QPoint &, QEvent::Type = QEvent::Drop);
    QDropEvent(const QDropEvent &);
    void accept(bool = TRUE);
    QDropEvent::Action action() const;
    QByteArray data(const char *) const;
    QByteArray encodedData(const char *) const;
    const char *format(int = 0) const;
    void ignore();
    bool isAccepted() const;
    bool isActionAccepted() const;
    const QPoint &pos() const;
    bool provides(const char *) const;
    void setAction(QDropEvent::Action);
    void setPoint(const QPoint &);
    QWidget *source() const;
} Qt::DropEvent;
