#include <qcheckbox.h>

suicidal virtual class QCheckBox : virtual QButton {
    QCheckBox(QWidget *, const char * = 0);
    QCheckBox(const QString &, QWidget *, const char * = 0);
    bool isChecked() const;
    void setChecked(bool);
    void setNoChange();
    void setTristate(bool = TRUE);
    virtual QSize sizeHint() const;
    virtual QSizePolicy sizePolicy() const;
protected:
    virtual void drawButton(QPainter *);
    virtual void drawButtonLabel(QPainter *);
    virtual void resizeEvent(QResizeEvent *);
    virtual void updateMask();
} Qt::CheckBox;
