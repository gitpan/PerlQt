#include <qlayout.h>

suicidal virtual class QLayout : virtual QObject, virtual QLayoutItem {
    enum { unlimited };
    enum ResizeMode { FreeResize, Minimum, Fixed };
    QLayout(int = -1, const char * = 0);
    QLayout(QLayout *, int = -1, const char * = 0);
    QLayout(QWidget *, int = 0, int = -1, const char * = 0);
    virtual ~QLayout();
    bool activate();
    void add(QWidget *);
    abstract void addItem(QLayoutItem *);
    bool autoAdd() const;
    virtual QSizePolicy::ExpandData expanding() const;
    virtual QRect geometry() const;
    virtual bool isEmpty() const;
    bool isTopLevel() const;
    abstract QLayoutIterator iterator();
    virtual QLayout *layout();
    QWidget *mainWidget();
    int margin() const;
    virtual QSize maximumSize() const;
    virtual QSize minimumSize() const;
    QMenuBar *menuBar() const;
    virtual void setAutoAdd(bool);
    abstract void setGeometry(const QRect &);
    virtual void setMargin(int);
    virtual void setMenuBar(QMenuBar *);
    void setResizeMode(QLayout::ResizeMode);
    virtual void setSpacing(int);
    int spacing() const;
    int totalHeightForWidth(int) const;
    QSize totalMaximumSize() const;
    QSize totalMinimumSize() const;
    QSize totalSizeHint() const;
protected:
    void addChildLayout(QLayout *);
    void deleteAllItems();
    virtual bool eventFilter(QObject *, QEvent *);
} Qt::Layout;
