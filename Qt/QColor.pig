#include <qcolor.h>

struct QColor {
    enum Spec { Rgb, Hsv };
    QColor();
    QColor(const char *);
    QColor(const QColor &);
    QColor(QRgb, uint = 0xffffffff);
    QColor(int, int, int);
    QColor(int, int, int, QColor::Spec);
    QColor &operator = (const QColor &);
    bool operator == (const QColor &) const;
    bool operator != (const QColor &) const;
    const char *{serial} operator << () const : pig_serialize($this);
    void operator >> (const char *{serial}) : pig_deserialize($this, $1);
    uint alloc();
    int blue() const;
    static int blue(QRgb) : qBlue($0);
    static int currentAllocContext();
    QColor dark(int = 200) const;
    static void destroyAllocContext(int);
    static int enterAllocContext();
    static int gray(QRgb) : qGray($0);
    static int gray(int, int, int) : qGray($0, $1, $2);
    int green() const;
    static int green(QRgb) : qGreen($0);
    void hsv(int *, int *, int *) const;
    bool isDirty() const;
    bool isValid() const;
    static bool lazyAlloc();
    static void leaveAllocContext();
    QColor light(int = 150) const;
    static int maxColors();
    static int numBitPlanes();
    uint pixel() const;
    int red() const;
    static int red(QRgb) : qRed($0);
    QRgb rgb() const;
    static QRgb rgb(int, int, int) : qRgb($0, $1, $2);
    void rgb(int *, int *, int *) const;
    void setHsv(int, int, int);
    static void setLazyAlloc(bool);
    void setNamedColor(const char *);
    void setRgb(QRgb);
    void setRgb(int, int, int);
} Qt::Color;

extern const QRgb RGB_DIRTY;
extern const QRgb RGB_INVALID;
extern const QRgb RGB_DIRECT;
extern const QRgb RGB_MASK;

extern const QColor color0;
extern const QColor color1;
extern const QColor black;
extern const QColor white;
extern const QColor darkGray;
extern const QColor gray;
extern const QColor lightGray;
extern const QColor red;
extern const QColor green;
extern const QColor blue;
extern const QColor cyan;
extern const QColor magenta;
extern const QColor yellow;
extern const QColor darkRed;
extern const QColor darkGreen;
extern const QColor darkBlue;
extern const QColor darkCyan;
extern const QColor darkMagenta;
extern const QColor darkYellow;