#include <qslider.h>

suicidal virtual class QSlider : virtual QWidget, virtual QRangeControl {
    enum TickSetting { NoMarks, Above, Left, Below, Right, Both };

    QSlider(QWidget * = 0, const char * = 0);
    QSlider(Qt::Orientation, QWidget * = 0, const char * = 0);
    QSlider(int, int, int, int, Qt::Orientation, QWidget * = 0, const char * = 0);
    void addStep() slot;
    virtual QSize minimumSizeHint() const;
    Qt::Orientation orientation() const;
    virtual void setOrientation(Qt::Orientation);
    virtual void setPalette(const QPalette &);
    virtual void setTickInterval(int);
    virtual void setTickmarks(QSlider::TickSetting);
    virtual void setTracking(bool);
    virtual void setValue(int) slot;
    virtual QSize sizeHint() const;
    virtual QSizePolicy sizePolicy() const;
    QRect sliderRect() const;
    void subtractStep() slot;
    int tickInterval() const;
    QSlider::TickSetting tickmarks() const;
    bool tracking() const;
protected:
    void drawTicks(QPainter *, int, int, int = 1) const;
    void drawTicks(QPainter *, const QColorGroup &, int, int, int = 1) const;
    void drawWinGroove(QPainter *, QCOORD);
    virtual void focusInEvent(QFocusEvent *);
    virtual void focusOutEvent(QFocusEvent *);
    virtual void keyPressEvent(QKeyEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void paintEvent(QPaintEvent *);
    virtual void paintSlider(QPainter *, const QColorGroup &, const QRect &);
    virtual void rangeChange();
    virtual void resizeEvent(QResizeEvent *);
    void sliderMoved(int) signal;
    void sliderPressed() signal;
    void sliderReleased() signal;
    virtual void styleChange(QStyle &);
    virtual int thickness() const;
    virtual void updateMask();
    virtual void valueChange();
    void valueChanged(int) signal;
    virtual void wheelEvent(QWheelEvent *);
} Qt::Slider;
