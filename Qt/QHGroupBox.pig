#include <qhgroupbox.h>

suicidal virtual class QHGroupBox : virtual QGroupBox {
    QHGroupBox(QWidget * = 0, const char * = 0);
    QHGroupBox(const QString &, QWidget * = 0, const char * = 0);
    virtual ~QHGroupBox();
} Qt::HGroupBox;
