#include <qabstractlayout.h>

virtual class QSpacerItem : virtual QLayoutItem {
    QSpacerItem(int, int, QSizePolicy::SizeType = QSizePolicy::Minimum, QSizePolicy::SizeType = QSizePolicy::Minimum);
    void changeSize(int, int, QSizePolicy::SizeType = QSizePolicy::Minimum, QSizePolicy::SizeType = QSizePolicy::Minimum);
    virtual QSizePolicy::ExpandData expanding() const;
    virtual QRect geometry() const;
    virtual bool isEmpty() const;
    virtual QSize maximumSize() const;
    virtual QSize minimumSize() const;
    virtual void setGeometry(const QRect &);
    virtual QSize sizeHint() const;
    virtual QSpacerItem *spacerItem();
} Qt::SpacerItem;
