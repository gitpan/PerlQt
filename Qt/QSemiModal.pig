#include <qsemimodal.h>

suicidal virtual class QSemiModal : virtual QWidget {
    QSemiModal(QWidget * = 0, const char * = 0, bool = FALSE, Qt::WFlags = 0);
    virtual ~QSemiModal();
    void move(const QPoint &);
    virtual void move(int, int);
    void resize(const QSize &);
    virtual void resize(int, int);
    virtual void setGeometry(int, int, int, int);
    virtual void show();
} Qt::SemiModal;
