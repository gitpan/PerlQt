#include <qtabbar.h>

suicidal virtual class QTabBar : virtual QWidget {
    enum Shape {
        RoundedAbove,
        RoundedBelow,
        TriangularAbove,
        TriangularBelow
    };
    QTabBar(QWidget * = 0, const char * = 0);
    virtual ~QTabBar();
    virtual int addTab(QTab *);
    int currentTab() const;
    virtual int insertTab(QTab *, int = -1);
    bool isTabEnabled(int) const;
    int keyboardFocusTab() const;
    virtual void layoutTabs();
    virtual void removeTab(QTab *);
    void setCurrentTab(int) slot;
    void setCurrentTab(QTab *) slot;
    void setShape(QTabBar::Shape);
    void setTabEnabled(int, bool);
    QTabBar::Shape shape() const;
    virtual void show();
    virtual QSize sizeHint() const;
    virtual QSizePolicy sizePolicy() const;
    QTab *tab(int);
protected:
    virtual void keyPressEvent(QKeyEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void paint(QPainter *, QTab *, bool) const;
    virtual void paintEvent(QPaintEvent *);
    virtual void paintLabel(QPainter *, const QRect &, QTab *, bool) const;
    virtual QTab *selectTab(const QPoint &) const;
    void selected(int) signal;
    QList<QTab>* tabList();
    void updateMask();
} Qt::TabBar;
