#include <qlistbox.h>

suicidal virtual class QListBoxPixmap : virtual QListBoxItem {
    QListBoxPixmap(QListBox *, const QPixmap &);
    QListBoxPixmap(const QPixmap &);
    virtual ~QListBoxPixmap();
    virtual int height(const QListBox *) const;
    virtual const QPixmap *pixmap() const;
    virtual int width(const QListBox *) const;
protected:
    virtual void paint(QPainter *);
} Qt::ListBoxPixmap;

