#include <qlistbox.h>

suicidal virtual class QListBoxText : virtual QListBoxItem {
    QListBoxText(QListBox *, const QString & = QString::null);
    QListBoxText(const QString & = QString::null);
    virtual ~QListBoxText();
    virtual int height(const QListBox *) const;
    virtual int width(const QListBox *) const;
protected:
    virtual void paint(QPainter *);
} Qt::ListBoxText;
