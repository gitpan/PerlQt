#include <qwizard.h>

suicidal virtual class QWizard : virtual QDialog {
    QWizard(QWidget * = 0, const char * = 0, bool = FALSE, Qt::WFlags = 0);
    virtual ~QWizard();
    virtual void addPage(QWidget *, const QString &);
    virtual bool appropriate(QWidget *) const;
    QPushButton *backButton() const;
    QPushButton *cancelButton() const;
    QWidget *currentPage() const;
    QPushButton *finishButton() const;
    virtual bool eventFilter(QObject *, QEvent *);
    QPushButton *helpButton() const;
    QPushButton *nextButton() const;
    virtual void removePage(QWidget *);
    virtual void setAppropriate(QWidget *, bool);
    virtual void show();
    virtual void showPage(QWidget *);
    virtual void setBackEnabled(QWidget *, bool);
    virtual void setFinish(QWidget *, bool);
    virtual void setFinishEnabled(QWidget *, bool);
    virtual void setFont(const QFont &);
    virtual void setHelpEnabled(QWidget *, bool);
    virtual void setNextEnabled(QWidget *, bool);
    QString title(QWidget *) const;
protected:
    virtual void back() slot;
    virtual void layOutButtonRow(QHBoxLayout *);
    virtual void layOutTitleRow(QHBoxLayout *, const QString &);
    virtual void next() slot;
    virtual void help() slot;
    void helpClicked() signal;
} Qt::Wizard;
