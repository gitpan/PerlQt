#include <qsplitter.h>

suicidal virtual class QSplitter : virtual QFrame {
    enum ResizeMode { Stretch, KeepSize };

    QSplitter(QWidget * = 0, const char * = 0);
    QSplitter(Qt::Orientation, QWidget * = 0, const char * = 0);
    virtual ~QSplitter();
    virtual QSize minimumSizeHint() const;
    void moveToFirst(QWidget *);
    void moveToLast(QWidget *);
    bool opaqueResize() const;
    Qt::Orientation orientation() const;
    void refresh();
    virtual void setOpaqueResize(bool = TRUE);
    virtual void setOrientation(Qt::Orientation);
    virtual void setResizeMode(QWidget *, QSplitter::ResizeMode);
;    void setSizes(QValueList<int>);
    virtual QSize sizeHint() const;
    virtual QSizePolicy sizePolicy() const;
;    QValueList<int> sizes() const;
protected:
    int adjustPos(int, int);
    virtual void childEvent(QChildEvent *);
    virtual void drawSplitter(QPainter *, QCOORD, QCOORD, QCOORD, QCOORD);
    virtual bool event(QEvent *);
    void getRange(int, int *, int *);
    int idAfter(QWidget *) const;
    void moveSplitter(QCOORD, int);
    virtual void resizeEvent(QResizeEvent *);
    virtual void setRubberband(int);
    virtual void styleChange(QStyle &);
} Qt::Splitter;
