#include <qtextview.h>

suicidal virtual class QTextView : virtual QScrollView {
    QTextView(QWidget * = 0, const char * = 0);
    QTextView(const QString &, const QString & = QString::null, QWidget * = 0, const char * = 0);
    virtual ~QTextView();
    virtual QString context() const;
    QString documentTitle() const;
    virtual int heightForWidth(int) const;
    const QColor &linkColor() const;
    bool linkUnderline() const;
    QMimeSourceFactory *mimeSourceFactory() const;
    const QBrush &paper();
    const QColorGroup &paperColorGroup() const;
    void setLinkColor(const QColor &);
    void setLinkUnderline(bool);
    void setMimeSourceFactory(QMimeSourceFactory *);
    void setPaper(const QBrush &);
    void setPaperColorGroup(const QColorGroup &);
    void setStyleSheet(QStyleSheet *);
    virtual void setText(const QString &, const QString & = QString::null);
    void setTextFormat(Qt::TextFormat);
    QStyleSheet *styleSheet() const;
    virtual QString text() const;
    Qt::TextFormat textFormat() const;
protected:
    virtual void drawContentsOffset(QPainter *, int, int, int, int, int, int);
    virtual void keyPressEvent(QKeyEvent *);
    virtual void paletteChange(const QPalette &);
    virtual void resizeEvent(QResizeEvent *);
;    QRichText &richText() const;
    virtual void viewportMousePressEvent(QMouseEvent *);
    virtual void viewportMouseReleaseEvent(QMouseEvent *);
    virtual void viewportMouseMoveEvent(QMouseEvent *);
    virtual void viewportResizeEvent(QResizeEvent *);
} Qt::TextView;
