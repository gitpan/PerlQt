#include <qmessagebox.h>

suicidal virtual class QMessageBox : virtual QDialog {
    enum Icon { NoIcon, Information, Warning, Critical };
    enum { Ok, Cancel, Yes, No, Abort, Retry,
           Ignore, ButtonMask,
           Default, Escape, FlagMask };

    QMessageBox(QWidget * = 0, const char * = 0);
    QMessageBox(const QString &, const QString &, QMessageBox::Icon, int, int, int, QWidget * = 0, const char * = 0, bool = TRUE, Qt::WFlags = Qt::WStyle_DialogBorder);
    virtual ~QMessageBox();
    static void about(QWidget *, const QString &, const QString &);
    static void aboutQt(QWidget *, const QString & = QString::null);
    virtual void adjustSize();
    QString buttonText(int) const;
    static int critical(QWidget *, const QString &, const QString &, int, int, int = 0);
    static int critical(QWidget *, const QString &, const QString &, const QString & = QString::null, const QString & = QString::null, const QString & = QString::null, int = 0, int = -1);
    QMessageBox::Icon icon() const;
    const QPixmap *iconPixmap() const;
    static int information(QWidget *, const QString &, const QString &, int, int = 0, int = 0);
    static int information(QWidget *, const QString &, const QString &, const QString & = QString::null, const QString & = QString::null, const QString & = QString::null, int = 0, int = -1 );
    void setButtonText(int, const QString &);
    void setIcon(QMessageBox::Icon);
    void setIcon(const QPixmap &);
    void setIconPixmap(const QPixmap &);
    void setText(const QString &);
    static QPixmap standardIcon(QMessageBox::Icon, Qt::GUIStyle);
    QString text() const;
    static int warning(QWidget *, const QString &, const QString &, int, int, int = 0);
    static int warning(QWidget *, const QString &, const QString &, const QString & = QString::null, const QString & = QString::null, const QString & = QString::null, int = 0, int = -1);
protected:
    virtual void keyPressEvent(QKeyEvent *);
    virtual void resizeEvent(QResizeEvent *);
    virtual void styleChanged(QStyle &);
} Qt::MessageBox;
