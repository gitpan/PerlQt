#include <qtabwidget.h>

suicidal virtual class QTabWidget : virtual QWidget {
    enum TabPosition { Top, Bottom };
    QTabWidget(QWidget * = 0, const char * = 0);
    virtual ~QTabWidget();
    void addTab(QWidget *, const QString &);
    void addTab(QWidget *, QTab *);
    void addTab(QWidget *, const QIconSet &, const QString &);
    void changeTab(QWidget *, const QString &);
    void changeTab(QWidget *, const QIconSet &, const QString &);
    QWidget *currentPage() const;
    void insertTab(QWidget *, const QString &, int = -1);
    void insertTab(QWidget *, QTab *, int = -1);
    void insertTab(QWidget *, const QIconSet &, const QString &, int = -1);
    bool isTabEnabled(QWidget *) const;
    int margin() const;
    virtual QSize minimumSizeHint() const;
    void removePage(QWidget *);
    void setMargin(int);
    void setTabEnabled(QWidget *, bool);
    void setTabPosition(QTabWidget::TabPosition);
    void showPage(QWidget *);
    virtual QSize sizeHint() const;
    QString tabLabel(QWidget *);
    QTabWidget::TabPosition tabPosition() const;
protected:
    virtual bool eventFilter(QObject *, QEvent *);
    virtual void resizeEvent(QResizeEvent *);
    void selected(const QString &) signal;
    void setTabBar(QTabBar *);
    virtual void showEvent(QShowEvent *);
    virtual void styleChange(QStyle &);
    QTabBar *tabBar() const;
    virtual void updateMask();
} Qt::TabWidget;
