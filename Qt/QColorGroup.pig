#include <qpalette.h>

struct QColorGroup {
    enum ColorRole { Foreground, Button, Light, Midlight, Dark, Mid,
                     Text, BrightText, ButtonText, Base, Background, Shadow,
                     Highlight, HighlightedText,
                     NColorRoles };

    QColorGroup();
    QColorGroup(const QColorGroup &);
    QColorGroup(const QColor &, const QColor &, const QColor &, const QColor &, const QColor &, const QColor &, const QColor &);
    QColorGroup(const QBrush &, const QBrush &, const QBrush &, const QBrush &, const QBrush &, const QBrush &, const QBrush &, const QBrush &, const QBrush &);
    ~QColorGroup();
    QColorGroup &operator = (const QColorGroup &);
    bool operator == (const QColorGroup &) const;
    bool operator != (const QColorGroup &) const;
    const QColor &background() const;
    const QColor &base() const;
    const QColor &brightText() const;
    const QBrush &brush(QColorGroup::ColorRole) const;
    const QColor &button() const;
    const QColor &buttonText() const;
    const QColor &color(QColorGroup::ColorRole) const;
    const QColor &dark() const;
    const QColor &foreground() const;
    const QColor &highlight() const;
    const QColor &highlightedText() const;
    const QColor &light() const;
    const QColor &mid() const;
    const QColor &midlight() const;
    void setBrush(QColorGroup::ColorRole, const QBrush &);
    void setColor(QColorGroup::ColorRole, const QColor &);
    const QColor &shadow() const;
    const QColor &text() const;
} Qt::QColorGroup;
