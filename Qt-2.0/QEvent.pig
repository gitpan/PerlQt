#include <qevent.h>

struct QEvent {
    enum Type {
        None,
        Timer,
        MouseButtonPress,
        MouseButtonRelease,
        MouseButtonDblClick,
        MouseMove,
        KeyPress,
        KeyRelease,
        FocusIn,
        FocusOut,
        Enter,
        Leave,
        Paint,
        Move,
        Resize,
        Create,
        Destroy,
        Show,
        Hide,
        Close,
        Quit,
        Accel,
        Wheel,
        AccelAvailable,
        Clipboard,
        SockAct,
        DragEnter,
        DragMove,
        DragLeave,
        Drop,
        DragResponse,
        ChildInserted,
        ChildRemoved,
        LayoutHint,
        ActivateControl,
        DeactivateControl,
        User
    };

    QEvent(QEvent::Type);
    QEvent(const QEvent &);
    ~QEvent();
    QEvent::Type type() const;
} Qt::Event;

