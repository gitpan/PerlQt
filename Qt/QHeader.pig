#include <qheader.h>

suicidal virtual class QHeader : virtual QWidget {
    QHeader(QWidget * = 0, const char * = 0);
    QHeader(int, QWidget * = 0, const char * = 0);
    virtual ~QHeader();
    int addLabel(const QString &, int = -1);
    int addLabel(const QIconSet &, const QString &, int = -1);
    int cellAt(int) const;
    int cellPos(int) const;
    int cellSize(int) const;
    int count() const;
    QIconSet *iconSet(int) const;
    QString label(int) const;
    int mapToActual(int) const;
    int mapToLogical(int) const;
    virtual void moveCell(int, int);
    int offset() const;
    Qt::Orientation orientation() const;
    virtual void setCellSize(int, int);
    virtual void setClickEnabled(bool, int = -1);
    virtual void setLabel(int, const QString &, int = -1);
    virtual void setLabel(int, const QIconSet &, const QString &, int = -1);
    virtual void setMovingEnabled(bool);
    virtual void setOffset(int) slot;
    virtual void setOrientation(Qt::Orientation);
    virtual void setResizeEnabled(bool, int = -1);
    virtual void setTracking(bool);
    virtual QSize sizeHint() const;
    virtual QSizePolicy sizePolicy() const;
    bool tracking() const;
protected:
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    void moved(int, int) signal;
    virtual void paintEvent(QPaintEvent *);
    void paintSection(QPainter *, int, QRect);
    void sectionClicked(int) signal;
    void sizeChange(int, int, int) signal;
    QRect sRect(int);
} Qt::Header;
