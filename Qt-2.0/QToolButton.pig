#include <qtoolbutton.h>

suicidal virtual class QToolButton : virtual QButton {
    QToolButton(QWidget *, const char * = 0);

; In perl, it's receiver(5). In any other language, it should be receiver(4)

    QToolButton(const QPixmap &, const QString &, const QString &, QObject *{receiver(5)}, const char *{member(4)}, QToolBar *, const char * = 0);
    QToolButton(QIconSet, const QString &, const QString &, QObject *{receiver(5)}, const char *{member(4)}, QToolBar *, const char * = 0);
    virtual ~QToolButton();
    QIconSet iconSet() const;
    virtual void setIconSet(const QIconSet &);
    virtual void setOn(bool) slot;
    virtual void setTextLabel(const char *, bool = TRUE) slot;
    virtual void setUsesBigPixmap(bool) slot;
    virtual void setUsesTextLabel(bool) slot;
    virtual QSize sizeHint() const;
    virtual QSizePolicy sizePolicy() const;
    void toggle() slot;
    QString textLabel() const;
    bool usesBigPixmap() const;
    bool usesTextLabel() const;
protected:
    virtual void drawButton(QPainter *);
    virtual void drawButtonLabel(QPainter *);
    virtual void enterEvent(QEvent *);
    virtual void leaveEvent(QEvent *);
    bool uses3D() const;
} Qt::ToolButton;
