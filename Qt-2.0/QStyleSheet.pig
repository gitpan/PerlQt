#include <qstylesheet.h>

suicidal virtual class QStyleSheet : virtual QObject {
    QStyleSheet(QObject * = 0, const char * = 0);
    virtual ~QStyleSheet();
    static QString convertFromPlainText(const QString &);
    static QStyleSheet *defaultSheet();
    virtual void error(const QString &) const;
    void insert(QStyleSheetItem *);
    QStyleSheetItem *item(const QString &);   // no poly on const yet
    static bool mightBeRichText(const QString &);
    virtual void scaleFont(QFont &, int) const;
    static void setDefaultSheet(QStyleSheet *);
;    virtual QTextNode *tag(const QString &, const QMap<QString, QString> &, const QString &, const QMimeSourceFactory &, bool = FALSE) const;
} Qt::StyleSheet;
