#include <qtranslator.h>

suicidal virtual class QTranslator : virtual QObject {
    enum SaveMode { Everything, Stripped };

    QTranslator(QObject *, const char * = 0);
    virtual ~QTranslator();
    void clear();
    bool contains(const char *, const char *) const;
    virtual QString find(const char *, const char *) const;
    void insert(const char *, const char *, const QString &);
    bool load(const QString &, const QString & = QString::null, const QString & = QString::null, const QString & = QString::null);
    void remove(const char *, const char *);
    bool save(const QString &, QTranslator::SaveMode = QTranslator::Everything);
    void squeeze();
    void unsqueeze();
} Qt::Translator;
