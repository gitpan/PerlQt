#include <qtextbrowser.h>

suicidal virtual class QTextBrowser : virtual QTextView {
    QTextBrowser(QWidget * = 0, const char * = 0);
    virtual ~QTextBrowser();
    virtual void backward() slot;
    virtual void forward() slot;
    virtual void home() slot;
    void scrollToAnchor(const QString &);
    virtual void setSource(const QString &);
    virtual void setText(const QString &, const QString & = QString::null);
    QString source() const;
protected:
    void backwardAvailable(bool) signal;
    void forwardAvailable(bool) signal;
    void highlighted(const QString &) signal;
    virtual void keyPressEvent(QKeyEvent *);
    void textChanged() signal;
    virtual void viewportMouseMoveEvent(QMouseEvent *);
    virtual void viewportMousePressEvent(QMouseEvent *);
    virtual void viewportMouseReleaseEvent(QMouseEvent *);
} Qt::TextBrowser;
