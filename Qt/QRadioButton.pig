#include <qradiobutton.h>

suicidal virtual class QRadioButton : virtual QButton {
    QRadioButton(QWidget *, const char * = 0);
    QRadioButton(const QString &, QWidget *, const char * = 0);
    bool isChecked() const;
    void setChecked(bool);
    virtual QSize sizeHint() const;
    virtual QSizePolicy sizePolicy() const;
protected:
    virtual void drawButton(QPainter *);
    virtual void drawButtonLabel(QPainter *);
    virtual void focusInEvent(QFocusEvent *);
    virtual bool hitButton(const QPoint &) const;
    virtual void resizeEvent(QResizeEvent *);
    virtual void updateMask();
} Qt::RadioButton;
