#include <qabstractlayout.h>

struct QLayoutIterator {
    QLayoutIterator(const QLayoutIterator &);
    QLayoutItem *current();
    void deleteCurrent();
    QLayoutItem *next() : ++*$this;
    QLayoutItem *takeCurrent();
} Qt::LayoutIterator;
