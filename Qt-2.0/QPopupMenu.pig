#include <qpopupmenu.h>

suicidal virtual class QPopupMenu : virtual QFrame, virtual QMenuData {
    QPopupMenu(QWidget * = 0, const char * = 0);
    virtual ~QPopupMenu();
    virtual bool customWhatsThis() const;
    int exec();
    int exec(const QPoint &, int = 0);
    virtual void hide();
    int idAt(int) const;
    int idAt(const QPoint &) const;
    bool isCheckable() const;
    void popup(const QPoint &, int = 0);
    virtual void setActiveItem(int);
    virtual void setCheckable(bool);
    virtual void setFont(const QFont &);
    virtual void show();
    virtual QSize sizeHint() const;
    virtual void updateItem(int);
protected:
    void aboutToShow() signal;
    void activated(int) signal;
    void activatedRedirect(int) signal;
    virtual void closeEvent(QCloseEvent *);
    virtual void drawContents(QPainter *);
    void drawItem(QPainter *, int, QMenuItem *, bool, int, int, int, int);
    void highlighted(int) signal;
    void highlightedRedirect(int) signal;
    int itemHeight(int) const;
    int itemHeight(QMenuItem *) const;
    virtual void keyPressEvent(QKeyEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void paintEvent(QPaintEvent *);
    virtual void timerEvent(QTimerEvent *);
    virtual void styleChange(QStyle &);
} Qt::PopupMenu;
