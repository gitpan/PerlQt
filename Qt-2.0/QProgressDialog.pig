#include <qprogressdialog.h>

suicidal virtual class QProgressDialog : virtual QSemiModal {
    QProgressDialog(QWidget * = 0, const char * = 0, bool = FALSE, Qt::WFlags = 0);
    QProgressDialog(const QString &, const QString &, int, QWidget * = 0, const char * = 0, bool = FALSE, Qt::WFlags = 0);
    virtual ~QProgressDialog();
    void cancel() slot;
    int minimumDuration() const;
    int progress() const;
    void reset() slot;
    void setBar(QProgressBar *);
    void setCancelButton(QPushButton *);
    void setCancelButtonText(const QString &) slot;
    void setLabel(QLabel *);
    void setLabelText(const QString &) slot;
    void setMinimumDuration(int) slot;
    void setProgress(int) slot;
    void setTotalSteps(int) slot;
    virtual QSize sizeHint() const;
    int totalSteps() const;
    bool wasCancelled() const;
protected:
    void cancelled() signal;
    virtual void closeEvent(QCloseEvent *);
    virtual void resizeEvent(QResizeEvent *);
    virtual void styleChange(QStyle &);
} Qt::ProgressDialog;
