#include <qevent.h>

struct QKeyEvent : QEvent {
    QKeyEvent(QEvent::Type, int, int, int, const QString & = QString::null, bool = FALSE, ushort = 1);
    QKeyEvent(const QKeyEvent &);
    void accept();
    int ascii() const;
    int count() const;
    void ignore();
    bool isAccepted() const;
    bool isAutoRepeat() const;
    int key() const;
    Qt::ButtonState state() const;
    Qt::ButtonState stateAfter() const;
    QString text() const;
} Qt::KeyEvent;
