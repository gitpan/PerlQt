#include <qhbuttongroup.h>

suicidal virtual class QHButtonGroup : virtual QButtonGroup {
    QHButtonGroup(QWidget * = 0, const char * = 0);
    QHButtonGroup(const QString &, QWidget * = 0, const char * = 0);
    virtual ~QHButtonGroup();
} Qt::HButtonGroup;
