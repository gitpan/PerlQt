#include <qhbox.h>

suicidal virtual class QHBox : virtual QFrame {
    QHBox(QWidget * = 0, const char * = 0, Qt::WFlags = 0, bool = TRUE);
    void setSpacing(int);
protected:
    QHBox(bool, QWidget * = 0, const char * = 0, Qt::WFlags = 0, bool = TRUE);
    virtual void frameChanged();
} Qt::HBox;

