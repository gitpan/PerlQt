#include <qtooltip.h>

suicidal class QToolTipGroup : QObject {
    QToolTipGroup(QObject *, const char * = 0);
    virtual ~QToolTipGroup();
    bool delay() const;
    void setDelay(bool) slot;
protected:
    void removeTip() signal;
    void showTip(const char *) signal;
} Qt::ToolTipGroup;

