#include <qgroupbox.h>

suicidal virtual class QGroupBox : virtual QFrame {
    QGroupBox(QWidget * = 0, const char * = 0);
    QGroupBox(const QString &, QWidget * = 0, const char * = 0);
    QGroupBox(int, Qt::Orientation, QWidget * = 0, const char * = 0);
    QGroupBox(int, Qt::Orientation, const QString &, QWidget * = 0, const char * = 0);
    int alignment() const;
    virtual void setAlignment(int);
    virtual void setColumnLayout(int, Qt::Orientation);
    virtual void setTitle(const QString &);
    QString title() const;
protected:
    virtual void childEvent(QChildEvent *);
    virtual void paintEvent(QPaintEvent *);
    virtual void resizeEvent(QResizeEvent *);
    virtual void updateMask();
} Qt::GroupBox;
