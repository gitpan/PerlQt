#include <qgrid.h>

suicidal virtual class QGrid : virtual QFrame {
    enum Direction { Horizontal, Vertical };
    QGrid(int, QWidget * = 0, const char * = 0, Qt::WFlags = 0);
    QGrid(int, QGrid::Direction, QWidget * = 0, const char * = 0, Qt::WFlags = 0);
    void setSpacing(int);
protected:
    virtual void frameChanged();
} Qt::Grid;
