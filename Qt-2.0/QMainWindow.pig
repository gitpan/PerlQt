#include <qmainwindow.h>

suicidal virtual class QMainWindow : virtual QWidget {
    enum ToolBarDock {
        Unmanaged,
        TornOff,
        Top,
        Bottom,
        Right,
        Left
    };
    QMainWindow(QWidget * = 0, const char * = 0, Qt::WFlags = 0);
    virtual ~QMainWindow();
    void addToolBar(QToolBar *, QMainWindow::ToolBarDock = QMainWindow::Top, bool = FALSE);
    void addToolBar(QToolBar *, const QString &, QMainWindow::ToolBarDock = QMainWindow::Top, bool = FALSE);
    QWidget *centralWidget() const;
    virtual bool eventFilter(QObject *, QEvent *);
    bool isDockEnabled(QMainWindow::ToolBarDock) const;
    QMenuBar *menuBar() const;
    void moveToolBar(QToolBar *, QMainWindow::ToolBarDock = QMainWindow::Top);
    void removeToolBar(QToolBar *);
    bool rightJustification() const;
    virtual void setCentralWidget(QWidget *);
    virtual void setDockEnabled(QMainWindow::ToolBarDock, bool);
    void setRightJustification(bool) slot;
    void setUsesBigPixmaps(bool) slot;
    virtual void show();
    QStatusBar *statusBar() const;
    QToolTipGroup *toolTipGroup() const;
    bool usesBigPixmaps() const;
protected:
    virtual void childEvent(QChildEvent *);
    virtual bool event(QEvent *);
    virtual void paintEvent(QPaintEvent *);
    void pixmapSizeChanged(bool) signal;
    virtual void resizeEvent(QResizeEvent *);
    void setUpLayout() slot;
    virtual void styleChange(QStyle &);
} Qt::MainWindow;
