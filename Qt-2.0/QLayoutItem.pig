#include <qabstractlayout.h>

virtual class QLayoutItem {
    QLayoutItem(int = 0);
    virtual ~QLayoutItem();
    int alignment() const;
    abstract QSizePolicy::ExpandData expanding() const;
    abstract QRect geometry() const;
    virtual bool hasHeightForWidth() const;
    virtual int heightForWidth(int) const;
    virtual void invalidate();
    abstract bool isEmpty() const;
    virtual QLayoutIterator iterator();
    virtual QLayout *layout();
    abstract QSize maximumSize() const;
    abstract QSize minimumSize() const;
    virtual void setAlignment(int);
    abstract void setGeometry(const QRect &);
    abstract QSize sizeHint() const;
    virtual QSpacerItem *spacerItem();
    virtual QWidget *widget();
} Qt::LayoutItem;
