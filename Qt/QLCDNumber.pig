#undef HEX
#undef DEC
#undef BIN
#undef OCT
#undef Hex
#undef Dec
#undef Bin
#undef Oct
#include <qlcdnumber.h>

suicidal virtual class QLCDNumber : virtual QFrame {
    enum Mode {
        HEX,
        DEC,
        OCT,
        BIN,
	Hex,
	Dec,
	Oct,
	Bin
    };
    enum SegmentStyle {
        Outline,
        Filled,
        Flat
    };

    QLCDNumber(QWidget * = 0, const char * = 0);
    QLCDNumber(uint, QWidget * = 0, const char * = 0);
    virtual ~QLCDNumber();
    bool checkOverflow(int) const;
    bool checkOverflow(double) const;
    void display(int) slot;
    void display(double) slot;
    void display(const QString &) slot;
    int intValue() const;
    QLCDNumber::Mode mode() const;
    int numDigits() const;
    QLCDNumber::SegmentStyle segmentStyle() const;
    virtual void setBinMode() slot;
    virtual void setDecMode() slot;
    virtual void setHexMode() slot;
    virtual void setOctMode() slot;
    virtual void setMode(QLCDNumber::Mode);
    virtual void setNumDigits(int);
    virtual void setSegmentStyle(QLCDNumber::SegmentStyle);
    virtual void setSmallDecimalPoint(bool) slot;
    virtual QSize sizeHint() const;
    virtual QSizePolicy sizePolicy() const;
    double value() const;
protected:
    virtual void drawContents(QPainter *);
    void overflow() signal;
} Qt::LCDNumber;
