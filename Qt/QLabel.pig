#include <qlabel.h>

suicidal virtual class QLabel : virtual QFrame {
    QLabel(QWidget * = 0, const char * = 0, Qt::WFlags = 0);
    QLabel(const QString &, QWidget * = 0, const char * = 0, Qt::WFlags = 0);
    QLabel(QWidget *, const QString &, QWidget *, const char *, Qt::WFlags = 0);
    virtual ~QLabel();
    int alignment() const;
    bool autoResize() const;
    QWidget *buddy() const;
    void clear() slot;
    virtual int heightForWidth(int) const;
    int indent() const;
    QMovie *movie() const;
    QPixmap *pixmap() const;
    virtual void setAlignment(int);
    void setAutoMask(bool);
    virtual void setAutoResize(bool);
    virtual void setBuddy(QWidget *);
    void setIndent(int);
    virtual void setMovie(const QMovie &) slot;
    virtual void setNum(int) slot;
    virtual void setNum(double) slot;
    virtual void setPixmap(const QPixmap &) slot;
    virtual void setText(const char *) slot;
    void setTextFormat(Qt::TextFormat);
    virtual QSize sizeHint() const;
    virtual QSizePolicy sizePolicy() const;
    const char *text() const;
    Qt::TextFormat textFormat() const;
protected:
    virtual void drawContents(QPainter *);
    virtual void drawContentsMask(QPainter *);
} Qt::Label;
