#include <qvbuttongroup.h>

suicidal virtual class QVButtonGroup : virtual QButtonGroup {
    QVButtonGroup(QWidget * = 0, const char * = 0);
    QVButtonGroup(const QString &, QWidget * = 0, const char * = 0);
    virtual ~QVButtonGroup();
} Qt::VButtonGroup;
