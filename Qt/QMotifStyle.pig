#include <qmotifstyle.h>

virtual class QMotifStyle : QCommonStyle, virtual QStyle {
    QMotifStyle(bool = FALSE);
    virtual void drawArrow(QPainter *, Qt::ArrowType, bool, int, int, int, int, const QColorGroup &, bool, const QBrush * = 0);
    virtual void drawBevelButton(QPainter *, int, int, int, int, const QColorGroup &, bool = FALSE, const QBrush * = 0);
    virtual void drawButton(QPainter *, int, int, int, int, const QColorGroup &, bool = FALSE, const QBrush * = 0);
    virtual void drawCheckMark(QPainter *, int, int, int, int, const QColorGroup &, bool, bool);
    virtual void drawExclusiveIndicator(QPainter *, int, int, int, int, const QColorGroup &, bool, bool = FALSE, bool = TRUE);
    virtual void drawExclusiveIndicatorMask(QPainter *, int, int, int, int, bool);
    virtual void drawFocusRect(QPainter *, const QRect &, const QColorGroup &, const QColor * = 0, bool = FALSE);
    virtual void drawIndicator(QPainter *, int, int, int, int, const QColorGroup &, int, bool = FALSE, bool = TRUE);
    virtual void drawPopupMenuItem(QPainter *, bool, int, int, QMenuItem *, const QPalette &, bool, bool, int, int, int, int);
    virtual void drawPushButton(QPushButton *, QPainter *);
    virtual void drawScrollBarControls(QPainter *, const QScrollBar *, int, uint, uint);
    virtual void drawSlider(QPainter *, int, int, int, int, const QColorGroup &, Qt::Orientation, bool, bool);
    virtual void drawSliderGroove(QPainter *, int, int, int, int, const QColorGroup &, QCOORD, Qt::Orientation);
    virtual void drawSplitter(QPainter *, int, int, int, int, const QColorGroup &, Qt::Orientation);
    virtual void drawTab(QPainter *, const QTabBar *, QTab *, bool);
    virtual void drawTabMask(QPainter *, const QTabBar *, QTab *, bool);
    virtual QSize exclusiveIndicatorSize() const;
    virtual int extraPopupMenuItemWidth(bool, int, QMenuItem *, const QFontMetrics &);
    virtual QSize indicatorSize() const;
    virtual void polish(QApplication *);
    virtual void polish(QWidget *);
    virtual void polish(QPalette &);
    virtual void polishPopupMenu(QPopupMenu *);
    virtual int popupMenuItemHeight(bool, QMenuItem *, const QFontMetrics &);
    virtual void scrollBarMetrics(const QScrollBar *, int &, int &, int &, int &);
    void setUseHighlightColors(bool);
    virtual int sliderLength() const;
    virtual int splitterWidth() const;
    virtual void tabbarMetrics(const QTabBar *, int &, int &, int &);
    bool useHighlightColors() const;
} Qt::MotifStyle;
