#include <qscrollbar.h>

suicidal virtual class QScrollBar : virtual QWidget, virtual QRangeControl {
    QScrollBar(QWidget * = 0, const char * = 0);
    QScrollBar(Qt::Orientation, QWidget * = 0, const char * = 0);
    QScrollBar(int, int, int, int, int, Qt::Orientation, QWidget * = 0, const char * = 0);
    virtual ~QScrollBar();
    bool draggingSlider() const;
    Qt::Orientation orientation() const;
    virtual void setOrientation(Qt::Orientation);
    virtual void setPalette(const QPalette &);
    virtual void setTracking(bool);
    virtual QSize sizeHint() const;
    virtual QSizePolicy sizePolicy() const;
    bool tracking() const;
protected:
    virtual void keyPressEvent(QKeyEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    void nextLine() signal;
    void nextPage() signal;
    virtual void paintEvent(QPaintEvent *);
    void prevLine() signal;
    void prevPage() signal;
    virtual void rangeChange();
    virtual void resizeEvent(QResizeEvent *);
    void sliderMoved(int) signal;
    void sliderPressed() signal;
    QRect sliderRect() const;
    void sliderReleased() signal;
    int sliderStart() const;
    virtual void stepChange();
    virtual void styleChange(QStyle &);
    virtual void valueChange();
    void valueChanged(int) signal;
    virtual void wheelEvent(QWheelEvent *);
} Qt::ScrollBar;
