#include <qdialog.h>

suicidal virtual class QDialog : virtual QWidget {
    enum DialogCode { Rejected, Accepted };

    QDialog(QWidget * = 0, const char * = 0, bool = FALSE, Qt::WFlags = 0);
    virtual ~QDialog();
    int exec();
    virtual void hide();
    void move(const QPoint &);
    virtual void move(int, int);
    void resize(const QSize &);
    virtual void resize(int, int);
    int result() const;
    void setGeometry(const QRect &);
    virtual void setGeometry(int, int, int, int);
    virtual void show();
protected:
    virtual void accept() slot;
    virtual void closeEvent(QCloseEvent *);
    virtual void done(int) slot;
    virtual void keyPressEvent(QKeyEvent *);
    virtual void reject() slot;
    void setResult(int);
} Qt::Dialog;
