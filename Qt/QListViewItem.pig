#include <qlistview.h>

suicidal virtual class QListViewItem {
    QListViewItem(QListView *);
    QListViewItem(QListViewItem *);
    QListViewItem(QListView *, QListViewItem *);
    QListViewItem(QListViewItem *, QListViewItem *);
    QListViewItem(QListView *, QString, QString = QString::null, QString = QString::null, QString = QString::null, QString = QString::null, QString = QString::null, QString = QString::null, QString = QString::null);
    QListViewItem(QListViewItem *, QString, QString = QString::null, QString = QString::null, QString = QString::null, QString = QString::null, QString = QString::null, QString = QString::null, QString = QString::null);
    QListViewItem(QListView *, QListViewItem *, QString, QString = QString::null, QString = QString::null, QString = QString::null, QString = QString::null, QString = QString::null, QString = QString::null, QString = QString::null);
    QListViewItem(QListViewItem *, QListViewItem *, QString, QString = QString::null, QString = QString::null, QString = QString::null, QString = QString::null, QString = QString::null, QString = QString::null, QString = QString::null);
    virtual ~QListViewItem();
    int childCount() const;
    int depth() const;
    QListViewItem *firstChild() const;
    int height() const;
    virtual void insertItem(QListViewItem *);
    virtual void invalidateHeight();
    bool isExpandable() const;
    bool isOpen() const;
    bool isSelectable() const;
    bool isSelected() const;
    QListViewItem *itemAbove();
    QListViewItem *itemBelow();
    int itemPos() const;
    virtual QString key(int, bool) const;
    QListView *listView() const;
    QListViewItem *nextSibling() const;
    virtual void paintBranches(QPainter *, const QColorGroup &, int, int, int, Qt::GUIStyle);
    virtual void paintCell(QPainter *, const QColorGroup &, int, int, int);
    virtual void paintFocus(QPainter *, const QColorGroup &, const QRect &);
    QListViewItem *parent() const;
    virtual const QPixmap *pixmap(int) const;
    void repaint() const;
    virtual void setExpandable(bool);
    virtual void setOpen(bool);
    virtual void setPixmap(int, const QPixmap &);
    virtual void setSelectable(bool);
    virtual void setSelected(bool);
    virtual void setText(int, const QString &);
    virtual void setup();
    virtual void sortChildItems(int, bool);
    virtual void takeItem(QListViewItem *);
    virtual QString text(int) const;
    int totalHeight() const;
    virtual int width(const QFontMetrics &, const QListView *, int) const;
    void widthChanged(int = -1) const;
protected:
    virtual void activate();
    virtual void enforceSortOrder() const;
    virtual void setHeight(int);
} Qt::ListViewItem;
