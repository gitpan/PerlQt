#define INCLUDE_MENUITEM_DEF
#include <qmenudata.h>

virtual class QMenuData {
    QMenuData();
    virtual ~QMenuData();
    int accel(int) const;
    void changeItem(int, const QString &);
    void changeItem(int, const QPixmap &);
    void changeItem(int, const QIconSet &, const QString &);
    void changeItem(int, const QIconSet &, const QPixmap &);
    void changeItem(const QString &, int); // obsolete
    void changeItem(const QPixmap &, int); // obsolete
    void changeItem(const QIconSet &, const QString &, int); // obsolete
    void clear();
    bool connectItem(int, const QObject *{receiver(3)}, const char *{member(2)});
    uint count() const;
    bool disconnectItem(int, const QObject *{unreceiver(3)}, const char *{member(2)});
    QMenuItem *findItem(int) const;
;    QMenuItem *findItem(int, QMenuData **) const;
    QIconSet *iconSet(int) const;
    int idAt(int) const;
    int indexOf(int) const;
    int insertItem(const QString &, const QObject *{receiver(3)}, const char *{member(2)}, int = 0, int = -1, int = -1);
    int insertItem(const QIconSet &, const QString &, const QObject *{receiver(3)}, const char *{member(3)}, int = 0, int = -1, int = -1);
    int insertItem(const QPixmap &, const QObject *{receiver(3)}, const char *{member(2)}, int = 0, int = -1, int = -1);
    int insertItem(const QIconSet &, const QPixmap &, const QObject *{receiver(3)}, const char *{member(2)}, int = 0, int = -1, int = -1);
    int insertItem(const QString &, int = -1, int = -1);
    int insertItem(const QIconSet &, const QString &, int = -1, int = -1);
    int insertItem(const QString &, QPopupMenu *, int = -1, int = -1);
    int insertItem(const QIconSet &, const QString &, QPopupMenu *, int = -1, int = -1);
    int insertItem(const QPixmap &, int = -1, int = -1);
    int insertItem(const QIconSet &, const QPixmap &, int = -1, int = -1);
    int insertItem(const QPixmap &, QPopupMenu *, int = -1, int = -1);
    int insertItem(const QIconSet &, const QPixmap &, QPopupMenu *, int = -1, int = -1);
    void insertSeparator(int = -1);
    bool isItemChecked(int) const;
    bool isItemEnabled(int) const;
    QPixmap *pixmap(int) const;
    void removeItem(int);
    void removeItemAt(int);
    void setAccel(int, int);
    virtual void setId(int, int);
    void setItemChecked(int, bool);
    void setItemEnabled(int, bool);
    void setWhatsThis(int, const QString &);
    QString text(int) const;
    virtual void updateItem(int);
    QString whatsThis(int) const;
protected:
    QMenuItem *findPopup(QPopupMenu *, int * = 0);
    virtual void menuContentsChanged();
    virtual void menuDelPopup(QPopupMenu *);
    virtual void menuInsPopup(QPopupMenu *);
    virtual void menuStateChanged();
} Qt::MenuData;
