#include <qfiledialog.h>

class QFileIconProvider : QObject {
    QFileIconProvider(QObject * = 0, const char * = 0);
    const QPixmap *pixmap(const QString &) : $this->pixmap(QFileInfo($1));
} Qt::FileIconProvider;
