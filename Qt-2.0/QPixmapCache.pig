#include <qpixmapcache.h>

namespace QPixmapCache {
    static int cacheLimit();
    static void clear();
    static QPixmap *find(const QString &);
    static bool find(const QString &, QPixmap &);
    static bool insert(const QString &, QPixmap *);
    static void insert(const QString &, const QPixmap &);
    static void setCacheLimit(int);
} Qt::PixmapCache;

