#include <qtooltip.h>

suicidal virtual class QToolTip {
    QToolTip(QWidget *, QToolTipGroup * = 0);
    static void add(QWidget *, const QString &);
    static void add(QWidget *, const QRect &, const QString &);
    static void add(QWidget *, const QString &, QToolTipGroup *, const QString &);
    static void add(QWidget *, const QRect &, const QString &, QToolTipGroup *, const QString &);
    static QFont font();
    QToolTipGroup *group() const;
    static QPalette palette();
    QWidget *parentWidget() const;
    static void remove(QWidget *);
    static void remove(QWidget *, const QRect &);
    static void setFont(const QFont &);
    static void setPalette(const QPalette &);
protected:
    void clear();
    abstract void maybeTip(const QPoint &);
    void tip(const QRect &, const QString &);
    void tip(const QRect &, const QString &, const QString &);
} Qt::ToolTip;
