#include <qtoolbar.h>

suicidal virtual class QToolBar : virtual QWidget {
    QToolBar(const QString &, QMainWindow *, QMainWindow::ToolBarDock = QMainWindow::Top, bool = FALSE, const char * = 0);
    QToolBar(const QString &, QMainWindow *, QWidget *, bool = FALSE, const char * = 0, Qt::WFlags = 0);
    QToolBar(QMainWindow * = 0, const char * = 0);
    virtual ~QToolBar();
    void addSeparator();
    virtual bool event(QEvent *);
    virtual bool eventFilter(QObject *, QEvent *);
    QString label() const;
    QMainWindow *mainWindow();
    QToolBar::Orientation orientation() const;
    virtual void setLabel(const QString &);
    virtual void setOrientation(QToolBar::Orientation);
    virtual void setStretchableWidget(QWidget *);
    virtual void show();
protected:
    void paintEvent(QPaintEvent *);
} Qt::ToolBar;
