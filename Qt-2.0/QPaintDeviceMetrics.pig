#include <qpaintdevicemetrics.h>

struct QPaintDeviceMetrics {
    enum {
        PdmWidth,
        PdmHeight,
        PdmWidthMM,
        PdmHeightMM,
        PdmNumColors,
        PdmDepth,
        PdmDpiX,
        PdmDpiY
    };

    QPaintDeviceMetrics(const QPaintDevice *);
    int depth() const;
    int height() const;
    int heightMM() const;
    int logicalDpiX() const;
    int logicalDpiY() const;
    int numColors() const;
    int width() const;
    int widthMM() const;
} Qt::PaintDeviceMetrics;
