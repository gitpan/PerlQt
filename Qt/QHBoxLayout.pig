#include <qlayout.h>

suicidal virtual class QHBoxLayout : virtual QBoxLayout {
    QHBoxLayout(int = -1, const char * = 0);
    QHBoxLayout(QLayout *, int = -1, const char * = 0);
    QHBoxLayout(QWidget *, int = 0, int = -1, const char * = 0);
    virtual ~QHBoxLayout();
} Qt::HBoxLayout;
