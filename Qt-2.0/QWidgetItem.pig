#include <qabstractlayout.h>

virtual class QWidgetItem : virtual QLayoutItem {
    QWidgetItem(QWidget *);
    virtual QSizePolicy::ExpandData expanding() const;
    virtual QRect geometry() const;
    virtual bool hasHeightForWidth() const;
    virtual int heightForWidth(int) const;
    virtual bool isEmpty() const;
    virtual QSize maximumSize() const;
    virtual QSize minimumSize() const;
    virtual void setGeometry(const QRect &);
    virtual QSize sizeHint() const;
    virtual QWidget *widget();
} Qt::WidgetItem;
