#include <qiconset.h>

struct QIconSet {
    enum Size { Automatic, Small, Large };
    enum Mode { Normal, Disabled, Active };

    QIconSet(const QPixmap &, QIconSet::Size = QIconSet::Automatic);
    QIconSet(const QIconSet &);
    ~QIconSet();
    QIconSet &operator = (const QIconSet &);
    void detach();
    bool isGenerated(QIconSet::Size, QIconSet::Mode) const;
    QPixmap pixmap(QIconSet::Size, QIconSet::Mode) const;
    QPixmap pixmap() const;
    void reset(const QPixmap &, QIconSet::Size);
    void setPixmap(const QPixmap &, QIconSet::Size, QIconSet::Mode = QIconSet::Normal);
    void setPixmap(const QString &, QIconSet::Size, QIconSet::Mode = QIconSet::Normal);
} Qt::IconSet;
