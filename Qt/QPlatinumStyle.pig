#include <qplatinumstyle.h>

virtual class QPlatinumStyle : virtual QWindowsStyle {
    QPlatinumStyle();
    virtual QRect buttonRect(int, int, int, int);
    virtual QRect comboButtonFocusRect(int, int, int, int);
    virtual QRect comboButtonRect(int, int, int, int);
    virtual void drawBevelButton(QPainter *, int, int, int, int, const QColorGroup &, bool = FALSE, const QBrush * = 0);
    virtual void drawButton(QPainter *, int, int, int, int, const QColorGroup &, bool = FALSE, const QBrush * = 0);
    virtual void drawCheckMark(QPainter *, int, int, int, int, const QColorGroup &, bool, bool);
    virtual void drawComboButton(QPainter *, int, int, int, int, const QColorGroup &, bool = FALSE, bool = FALSE, bool = TRUE, const QBrush * = 0);
    virtual void drawExclusiveIndicator(QPainter *, int, int, int, int, const QColorGroup &, bool, bool = FALSE, bool = TRUE);
    virtual void drawIndicator(QPainter *, int, int, int, int, const QColorGroup &, int, bool = FALSE, bool = TRUE);
    virtual void drawIndicatorMask(QPainter *, int, int, int, int, int);
    virtual void drawPopupMenuItem(QPainter *, bool, int, int, QMenuItem *, const QPalette &, bool, bool, int, int, int, int);
    virtual void drawPopupPanel(QPainter *, int, int, int, int, const QColorGroup &, int = 2, const QBrush * = 0);
    virtual void drawPushButton(QPushButton *, QPainter *);
    virtual void drawPushButtonLabel(QPushButton *, QPainter *);
    virtual void drawScrollBarControls(QPainter *, const QScrollBar *, int, uint, uint);
    virtual void drawSlider(QPainter *, int, int, int, int, const QColorGroup &, Qt::Orientation, bool, bool);
    virtual void drawSliderGroove(QPainter *, int, int, int, int, const QColorGroup &, QCOORD, Qt::Orientation);
    virtual void drawSliderMask(QPainter *, int, int, int, int, Qt::Orientation, bool, bool);
    virtual QSize exclusiveIndicatorSize() const;
    virtual int extraPopupMenuItemWidth(bool, int, QMenuItem *, const QFontMetrics &);
    virtual QSize indicatorSize() const;
    virtual int maximumSliderDragDistance() const;
    virtual void polishPopupMenu(QPopupMenu *);
    virtual int popupMenuItemHeight(bool, QMenuItem *, const QFontMetrics &);
    virtual void scrollBarMetrics(const QScrollBar *, int &, int &, int &, int &);
    virtual QStyle::ScrollControl scrollBarPointOver(const QScrollBar *, int, const QPoint &);
    virtual int sliderLength() const;
protected:
    void drawRiffles(QPainter *, int, int, int, int, const QColorGroup &, bool);
    void drawScrollBarBackground(QPainter *, int, int, int, int, const QColorGroup &, bool, const QBrush * = 0);
    QColor mixedColor(const QColor &, const QColor &);
} Qt::PlatinumStyle;
