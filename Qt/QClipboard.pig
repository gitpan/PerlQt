#include <qclipboard.h>

class QClipboard : QObject {
    void clear();
    QMimeSource *data() const;
    QImage image();
    QPixmap pixmap();
    void setData(QMimeSource *);
    void setImage(const QImage &);
    void setPixmap(const QPixmap &);
    void setText(const QString &);
    QString text();
protected:
    virtual void connectNotify(const char *);
    void dataChanged() signal;
    virtual void event(QEvent *);
private:
    ~QClipboard();
} Qt::Clipboard;
