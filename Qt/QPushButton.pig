#include <qpushbutton.h>

suicidal virtual class QPushButton : virtual QButton {
    QPushButton(QWidget * = 0, const char * = 0);
    QPushButton(const QString &, QWidget * = 0, const char * = 0);
    virtual ~QPushButton();
    bool autoDefault() const;
    bool isDefault() const;
    bool isMenuButton() const;
    void move(const QPoint &);
    virtual void move(int, int);
    void resize(const QSize &);
    virtual void resize(int, int);
    virtual void setAutoDefault(bool);
    virtual void setDefault(bool);
    virtual void setIsMenuButton(bool);
    virtual void setGeometry(const QRect &);
    virtual void setGeometry(int, int, int, int);
    virtual void setOn(bool) slot;
    virtual void setToggleButton(bool);
    virtual QSize sizeHint() const;
    virtual QSizePolicy sizePolicy() const;
    void toggle() slot;
protected:
    virtual void drawButton(QPainter *);
    virtual void drawButtonLabel(QPainter *);
    virtual void focusInEvent(QFocusEvent *);
    virtual void focusOutEvent(QFocusEvent *);
    virtual void resizeEvent(QResizeEvent *);
    virtual void updateMask();
} Qt::PushButton;
