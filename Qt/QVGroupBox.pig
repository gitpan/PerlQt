#include <qvgroupbox.h>

suicidal virtual class QVGroupBox : virtual QGroupBox {
    QVGroupBox(QWidget * = 0, const char * = 0);
    QVGroupBox(const QString &, QWidget * = 0, const char * = 0);
    virtual ~QVGroupBox();
} Qt::VGroupBox;
