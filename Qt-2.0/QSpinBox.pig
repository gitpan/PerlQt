#include <qspinbox.h>

suicidal virtual class QSpinBox : virtual QFrame, virtual QRangeControl {
    QSpinBox(QWidget * = 0, const char * = 0);
    QSpinBox(int, int, int = 1, QWidget * = 0, const char * = 0 );
    virtual ~QSpinBox();
    virtual QString cleanText() const;
    virtual QString prefix() const;
    virtual void setEnabled(bool) slot;
    virtual void setPrefix(const QString &) slot;
    virtual void setSuffix(const QString &) slot;
    virtual void setSpecialValueText(const QString &);
    virtual void setValidator(const QValidator *);
    virtual void setValue(int) slot;
    virtual void setWrapping(bool);
    virtual QSize sizeHint() const;
    virtual QSizePolicy sizePolicy() const;
    QString specialValueText() const;
    virtual void stepDown() slot;
    virtual void stepUp() slot;
    virtual QString suffix() const;
    QString text() const;
    const QValidator *validator() const;
    bool wrapping() const;
protected:
    QString currentValueText();
    QPushButton *downButton() const;
    QLineEdit *editor() const;
    virtual bool eventFilter(QObject *, QEvent *);
    virtual void interpretText();
    virtual int mapTextToValue(bool *);
    virtual QString mapValueToText(int);
    virtual void rangeChange();
    virtual void resizeEvent(QResizeEvent *);
    virtual void styleChange(QStyle &);
    void textChanged() slot;
    QPushButton *upButton() const;
    virtual void updateDisplay();
    virtual void valueChange();
    void valueChanged(int) signal;
    void valueChanged(const char *) signal;
    virtual void wheelEvent(QWheelEvent *);
} Qt::SpinBox;
