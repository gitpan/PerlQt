#include <qpalette.h>

struct QPalette {
    enum ColorGroup { Normal, Disabled, Active, NColorGroups };

    QPalette();
    QPalette(const QColor &);
    QPalette(const QPalette &);
    QPalette(const QColor &, const QColor &);
    QPalette(const QColorGroup &, const QColorGroup &, const QColorGroup &);
    ~QPalette();
    QPalette &operator = (const QPalette &);
    bool operator == (const QPalette &) const;
    bool operator != (const QPalette &) const;
    const char *{serial} operator << () const : pig_serialize($this);
    void operator >> (const char *{serial}) : pig_deserialize($this, $1);
    const QColorGroup &active() const;
    const QBrush &brush(QPalette::ColorGroup, QColorGroup::ColorRole) const;
    const QColor &color(QPalette::ColorGroup, QColorGroup::ColorRole) const;
    QPalette copy() const;
    const QColorGroup &disabled() const;
    bool isCopyOf(const QPalette &);
    const QColorGroup &normal() const;
    int serialNumber() const;
    void setActive(const QColorGroup &);
    void setBrush(QPalette::ColorGroup, QColorGroup::ColorRole, const QBrush &);
    void setBrush(QColorGroup::ColorRole, const QBrush &);
    void setColor(QPalette::ColorGroup, QColorGroup::ColorRole, const QColor &);
    void setColor(QColorGroup::ColorRole, const QColor &);
    void setDisabled(const QColorGroup &);
    void setNormal(const QColorGroup &);
} Qt::Palette;
