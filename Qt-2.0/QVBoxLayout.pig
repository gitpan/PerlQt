#include <qlayout.h>

suicidal virtual class QVBoxLayout : virtual QBoxLayout {
    QVBoxLayout(int = -1, const char * = 0);
    QVBoxLayout(QLayout *, int = -1, const char * = 0);
    QVBoxLayout(QWidget *, int = 0, int = -1, const char * = 0);
    virtual ~QVBoxLayout();
} Qt::VBoxLayout;

