#include <qmime.h>

virtual class QMimeSourceFactory {
    QMimeSourceFactory();
    virtual ~QMimeSourceFactory();
    virtual const QMimeSource *data(const QString &) const;
    const QMimeSource *data(const QString &, const QString &) const;
    static QMimeSourceFactory *defaultFactory();
    virtual QString makeAbsolute(const QString &, const QString &) const;
    static void setDefaultFactory(QMimeSourceFactory *);
    virtual void setData(const QString &, QMimeSource *);
    virtual void setExtensionType(const QString &, const char *);
    virtual void setFilePath(const QStringList &);
    virtual void setImage(const QString &, const QImage &);
    virtual void setPixmap(const QString &, const QPixmap &);
    virtual void setText(const QString &, const QString &);
} Qt::MimeSourceFactory;
