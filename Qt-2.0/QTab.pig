#include <qtabbar.h>

struct QTab {
    QTab();
    virtual ~QTab();
    variable bool enabled() const;
    variable QIconSet *iconset() const;
    variable int id() const;
    variable QString label() const;
    variable QRect rect() const : $this->r;
    variable void setEnabled(bool);
    variable void setIconset(QIconSet *);
    variable void setId(int);
    variable void setLabel(const char *);
    variable void setRect(const QRect &) : $this->r = $1;
} Qt::Tab;

