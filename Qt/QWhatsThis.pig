#include <qwhatsthis.h>

virtual class QWhatsThis {
    QWhatsThis(QWidget *);
    virtual ~QWhatsThis();
    static void add(QWidget *, const QString &);
    static void enterWhatsThisMode();
    static bool inWhatsThisMode();
;;;;; Buggy
    static void leaveWhatsThisMode(const QString & = QString::null, const QPoint & = QCursor::pos());
    static void remove(QWidget *);
    virtual QString text(const QPoint &);
;;;;; Buggy
    static QString textFor(QWidget *, const QPoint & = QPoint());
    static QToolButton *whatsThisButton(QWidget *);
} Qt::WhatsThis;

