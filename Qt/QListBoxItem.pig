#include <qlistbox.h>

suicidal virtual class QListBoxItem {
    QListBoxItem(QListBox * = 0);
    virtual ~QListBoxItem();
    virtual int height(const QListBox *) const;
    QListBox *listBox() const;
    virtual const QPixmap *pixmap() const;
    bool selected() const;
    virtual QString text() const;
    virtual int width(const QListBox *) const;
protected:
    abstract void paint(QPainter *);
    void setText(const QString &);
} Qt::ListBoxItem;
