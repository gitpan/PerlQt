#define INCLUDE_MENUITEM_DEF
#include <qmenudata.h>

suicidal class QMenuItem {
    QMenuItem();
    ~QMenuItem();
    int id() const;
    QIconSet *iconSet() const;
    bool isChecked() const;
    bool isDirty() const;
    bool isEnabled() const;
    bool isSeparator() const;
    int key() const;
    QPixmap *pixmap() const;
    QPopupMenu *popup() const;
    void setDirty(bool);
    void setText(const QString &);
    void setWhatsThis(const QString &);
    QString text() const;
    QString whatsThis() const;
} Qt::MenuItem;
