#include <qprogressbar.h>

suicidal virtual class QProgressBar : virtual QFrame {
    QProgressBar(QWidget * = 0, const char * = 0, Qt::WFlags = 0);
    QProgressBar(int, QWidget * = 0, const char * = 0, Qt::WFlags = 0);
    bool centerIndicator() const;
    bool indicatorFollowsStyle() const;
    virtual QSize minimumSizeHint() const;
    int progress() const;
    void reset() slot;
    void setCenterIndicator(bool);
    void setIndicatorFollowsStyle(bool);
    void setProgress(int) slot;
    void setTotalSteps(int) slot;
    virtual void show();
    virtual QSize sizeHint() const;
    virtual QSizePolicy sizePolicy() const;
    int totalSteps() const;
protected:
    virtual void drawContents(QPainter *);
    virtual void drawContentsMask(QPainter *);
    virtual bool setIndicator(QString &, int, int);
    virtual void styleChange(QStyle &);
} Qt::ProgressBar;
