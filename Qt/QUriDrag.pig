#include <qdragobject.h>

suicidal virtual class QUriDrag : virtual QStoredDrag {
    QUriDrag(QWidget * = 0, const char * = 0);
    QUriDrag(QStrList, QWidget * = 0, const char * = 0);
    ~QUriDrag();
    static bool canDecode(const QMimeSource *);
    static bool decode(const QMimeSource *, QStrList &);
    static bool decodeLocalFiles(const QMimeSource *, QStringList &);
    static bool decodeToUnicodeUris(const QMimeSource *, QStringList &);
    static const char *localFileToUri(const QString &);
    void setFilenames(QStringList);
    void setUnicodeUris(QStringList);
    virtual void setUris(QStrList);
    static const char *unicodeUriToUri(const QString &);
    static QString uriToLocalFile(const char *);
    static QString uriToUnicodeUri(const char *);
} Qt::UriDrag;
