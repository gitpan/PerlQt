#include <qbutton.h>

suicidal virtual class QButton : virtual QWidget {
    enum ToggleType { SingleShot, Toggle, Tristate };
    enum ToggleState { Off, NoChange, On };

    QButton(QWidget * = 0, const char * = 0, Qt::WFlags = 0);
    virtual ~QButton();
    int accel() const;
    void animateClick() slot;
    bool autoRepeat() const;
    bool autoResize() const;
    virtual bool focusNextPrevChild(bool);
    QButtonGroup *group() const;
    bool isDown() const;
    bool isExclusiveToggle() const;
    bool isOn() const;
    bool isToggleButton() const;
    const QPixmap *pixmap() const;
    void setAccel(int);
    virtual void setAutoRepeat(bool);
    virtual void setAutoResize(bool);
    virtual void setDown(bool);
    virtual void setPixmap(const QPixmap &);
    virtual void setText(const QString &);
    QButton::ToggleState state() const;
    QString text() const;
    void toggle() slot;
    QButton::ToggleType toggleType() const;
protected:
    void clicked() signal;
    virtual void drawButton(QPainter *);
    virtual void drawButtonLabel(QPainter *);
    virtual void enabledChange(bool);
    virtual void focusInEvent(QFocusEvent *);
    virtual void focusOutEvent(QFocusEvent *);
    virtual bool hitButton(const QPoint &) const;
    virtual void keyPressEvent(QKeyEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void paintEvent(QPaintEvent *);
    void pressed() signal;
    void released() signal;
    void setOn(bool);
    void setToggleButton(bool);
    virtual void setToggleType(QButton::ToggleType);
    virtual void setState(QButton::ToggleState);
    void stateChanged(int) signal;
    void toggled(bool) signal;
} Qt::Button;
