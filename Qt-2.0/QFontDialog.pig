#include <qfontdialog.h>

namespace QFontDialog {
    static QFont getFont(bool *, QWidget * = 0, const char * = 0);
    static QFont getFont(bool *, const QFont &, QWidget * = 0, const char * = 0);
} Qt::FontDialog;
