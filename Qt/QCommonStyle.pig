#include <qcommonstyle.h>

class QCommonStyle : QStyle {
    virtual QRect comboButtonFocusRect(int, int, int, int);
    virtual QRect comboButtonRect(int, int, int, int);
    virtual int defaultFrameWidth() const;
    virtual void drawComboButton(QPainter *, int, int, int, int, const QColorGroup &, bool = FALSE, bool = FALSE, bool = TRUE, const QBrush * = 0);
    virtual void drawComboButtonMask(QPainter *, int, int, int, int);
    virtual void drawPushButtonLabel(QPushButton *, QPainter *);
    virtual void drawSliderGrooveMask(QPainter *, int, int, int, int, QCOORD, Qt::Orientation);
    virtual void drawSliderMask(QPainter *, int, int, int, int, Qt::Orientation, bool, bool);
    virtual void drawTab(QPainter *, const QTabBar *, QTab *, bool);
    virtual void drawTabMask(QPainter *, const QTabBar *, QTab *, bool);
    virtual void getButtonShift(int &, int &);
    virtual int maximumSliderDragDistance() const;
    virtual int popupSubmenuIndicatorWidth(const QFontMetrics &);
    virtual QStyle::ScrollControl scrollBarPointOver(const QScrollBar *, int, const QPoint &);
    virtual void tabbarMetrics(const QTabBar *, int &, int &, int &);
private:
    ~QCommonStyle();
} Qt::CommonStyle;
