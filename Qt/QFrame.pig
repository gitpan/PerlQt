#include <qframe.h>

suicidal virtual class QFrame : virtual QWidget {
    enum Shape { NoFrame, Box, Panel, WinPanel, HLine, VLine, StyledPanel,
                 PopupPanel, MShape };
    enum Shadow { Plain, Raised, Sunken, MShadow };

    QFrame(QWidget * = 0, const char * = 0, Qt::WFlags = 0, bool = TRUE);
    virtual ~QFrame();
    QRect contentsRect() const;
    QFrame::Shadow frameShadow() const;
    QFrame::Shape frameShape() const;
    QRect frameRect() const;
    int frameStyle() const;
    int frameWidth() const;
    int lineWidth() const;
    int margin() const;
    int midLineWidth() const;
    virtual void setFrameRect(const QRect &);
    void setFrameShadow(QFrame::Shadow);
    void setFrameShape(QFrame::Shape);
    virtual void setFrameStyle(int);
    virtual void setLineWidth(int);
    virtual void setMargin(int);
    virtual void setMidLineWidth(int);
    virtual QSize sizeHint() const;
    virtual QSizePolicy sizePolicy() const;
protected:
    virtual void drawContents(QPainter *);
    virtual void drawContentsMask(QPainter *);
    virtual void drawFrame(QPainter *);
    virtual void drawFrameMask(QPainter *);
    virtual void frameChanged();
    virtual void paintEvent(QPaintEvent *);
    virtual void resizeEvent(QResizeEvent *);
    virtual void updateMask();
} Qt::Frame;
