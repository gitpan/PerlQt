#include <qwindowsstyle.h>

virtual class QWindowsStyle : QCommonStyle, virtual QStyle {
    QWindowsStyle();
    virtual QRect comboButtonFocusRect(int, int, int, int);
    virtual QRect comboButtonRect(int, int, int, int);
    virtual void drawArrow(QPainter *, Qt::ArrowType, bool, int, int, int, int, const QColorGroup &, bool, const QBrush * = 0);
    virtual void drawBevelButton(QPainter *, int, int, int, int, const QColorGroup &, bool = FALSE, const QBrush * = 0);
    virtual void drawButton(QPainter *, int, int, int, int, const QColorGroup &, bool = FALSE, const QBrush * = 0);
    virtual void drawCheckMark(QPainter *, int, int, int, int, const QColorGroup &, bool, bool);
    virtual void drawComboButton(QPainter *, int, int, int, int, const QColorGroup &, bool = FALSE, bool = FALSE, bool = TRUE, const QBrush * = 0);
    virtual void drawExclusiveIndicator(QPainter *, int, int, int, int, const QColorGroup &, bool, bool = FALSE, bool = TRUE);
    virtual void drawExclusiveIndicatorMask(QPainter *, int, int, int, int, bool);
    virtual void drawFocusRect(QPainter *, const QRect &, const QColorGroup &, const QColor * = 0, bool = FALSE);
    virtual void drawIndicator(QPainter *, int, int, int, int, const QColorGroup &, int, bool = FALSE, bool = TRUE);
    virtual void drawPanel(QPainter *, int, int, int, int, const QColorGroup &, bool = FALSE, int = 1, const QBrush * = 0);
    virtual void drawPopupMenuItem(QPainter *, bool, int, int, QMenuItem *, const QPalette &, bool, bool, int, int, int, int);
    virtual void drawPopupPanel(QPainter *, int, int, int, int, const QColorGroup &, int = 2, const QBrush * = 0);
    virtual void drawPushButton(QPushButton *, QPainter *);
    virtual void drawScrollBarControls(QPainter *, const QScrollBar *, int, uint, uint);
    virtual void drawSlider(QPainter *, int, int, int, int, const QColorGroup &, Qt::Orientation, bool, bool);
    virtual void drawSliderGroove(QPainter *, int, int, int, int, const QColorGroup &, QCOORD, Qt::Orientation);
    virtual void drawSliderMask(QPainter *, int, int, int, int, Qt::Orientation, bool, bool);
    virtual void drawSplitter(QPainter *, int, int, int, int, const QColorGroup &, Qt::Orientation);
    virtual void drawTab(QPainter *, const QTabBar *, QTab *, bool);
    virtual void drawTabMask(QPainter *, const QTabBar *, QTab *, bool);
    virtual QSize exclusiveIndicatorSize() const;
    virtual int extraPopupMenuItemWidth(bool, int, QMenuItem *, const QFontMetrics &);
    virtual void getButtonShift(int &, int &);
    virtual QSize indicatorSize() const;
    virtual int maximumSliderDragDistance() const;
    virtual void polishPopupMenu(QPopupMenu *);
    virtual int popupMenuItemHeight(bool, QMenuItem *, const QFontMetrics &);
    virtual void scrollBarMetrics(const QScrollBar *, int &, int &, int &, int &);
    virtual int sliderLength() const;
    virtual int splitterWidth() const;
    virtual void tabbarMetrics(const QTabBar *, int &, int &, int &);
protected:
    void drawWinShades(QPainter *, int, int, int, int, const QColor &, const QColor &, const QColor &, const QColor &, const QBrush *);
} Qt::WindowsStyle;
