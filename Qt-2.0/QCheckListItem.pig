#include <qlistview.h>

suicidal virtual class QCheckListItem {
    enum Type { RadioButton, CheckBox, Controller };

    QCheckListItem(QCheckListItem *, const QString &, QCheckListItem::Type = QCheckListItem::Controller);
    QCheckListItem(QListViewItem *, const QString &, QCheckListItem::Type = QCheckListItem::Controller);
    QCheckListItem(QListView *, const QString &, QCheckListItem::Type = QCheckListItem::Controller);
    QCheckListItem(QListViewItem *, const QString &, const QPixmap &);
    QCheckListItem(QListView *, const QString &, const QPixmap &);
    bool isOn() const;
    virtual void paintCell(QPainter *, const QColorGroup &, int, int, int);
    virtual void paintFocus(QPainter *, const QColorGroup &, const QRect &);
    virtual void setOn(bool);
    virtual void setup();
    QString text() const;
    QString text(int) const;
    QCheckListItem::Type type() const;
    virtual int width(const QFontMetrics &, const QListView *, int) const;
protected:
    virtual void activate();
    virtual void paintBranches(QPainter *, const QColorGroup &, int, int, int, Qt::GUIStyle);
    virtual void stateChange(bool);
    void turnOffChild();
} Qt::CheckListItem;
