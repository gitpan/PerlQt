#include <qfocusdata.h>

class QFocusData {
    int count() const;
    QWidget *focusWidget() const;
    QWidget *home();
    QWidget *next();
    QWidget *prev();
} Qt::FocusData;
