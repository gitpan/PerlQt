#include <qfont.h>
#include <qstringlist.h>

struct QFont {
    enum CharSet   { ISO_8859_1,  Latin1, AnyCharSet,
                     ISO_8859_2,  Latin2,
                     ISO_8859_3,  Latin3,
                     ISO_8859_4,  Latin4,
                     ISO_8859_5,
                     ISO_8859_6,
                     ISO_8859_7,
                     ISO_8859_8,
                     ISO_8859_9,  Latin5,
                     ISO_8859_10, Latin6,
                     ISO_8859_11,
                     ISO_8859_12,
                     ISO_8859_13, Latin7,
                     ISO_8859_14, Latin8,
                     ISO_8859_15, Latin9,
                     KOI8R,
                     Set_Ja, Set_1,
                     Set_Ko,
                     Set_Th_TH,
                     Set_Zh,
                     Set_Zh_TW, Set_N,
                     Unicode
                    };
    enum StyleHint { Helvetica, Times, Courier, OldEnglish,  System, AnyStyle,
                     SansSerif,
                     Serif,
                     TypeWriter,
                     Decorative};
    enum Weight    { Light, Normal, DemiBold, Bold, Black };
    QFont();
    QFont(const QFont &);
    QFont(const QString &, int = 12, int = QFont::Normal, bool = FALSE);
    QFont(const QString &, int, int, bool, QFont::CharSet);
    ~QFont();
    QFont &operator = (const QFont &);
    bool operator == (const QFont &) const;
    bool operator != (const QFont &) const;
    const char *{serial} operator << () const : pig_serialize($this);
    void operator >> (const char *{serial}) : pig_deserialize($this, $1);
    bool bold() const;
    QFont::CharSet charSet() const;
    static QFont::CharSet charSetForLocale();
    static const QFont defaultFont();
    static QString encodingName(QFont::CharSet);
    bool exactMatch() const;
    QString family() const;
    bool fixedPitch() const;
    HANDLE handle() const;
    static void insertSubstitution(const QString &, const QString &);
    bool isCopyOf(const QFont &) const;
    bool italic() const;
    QString key() const;
    int pixelSize() const;
    int pointSize() const;
    float pointSizeFloat() const;
    bool rawMode() const;
    QString rawName() const;
    static void removeSubstitution(const QString &);
    void setBold(bool);
    void setCharSet(QFont::CharSet);
    static void setDefaultFont(const QFont &);
    void setFamily(const QString &);
    void setFixedPitch(bool);
    void setItalic(bool);
    void setPixelSize(int);
    void setPixelSizeFloat(float);
    void setPointSize(int);
    void setPointSizeFloat(float);
    void setRawMode(bool);
    void setRawName(const QString &);
    void setStrikeOut(bool);
    void setStyleHint(QFont::StyleHint);
    void setUnderline(bool);
    void setWeight(int);
    bool strikeOut() const;
    QFont::StyleHint styleHint() const;
    static QString substitute(const QString &);
    static QStringList substitutions();
    bool underline() const;
    int weight() const;
protected:
    int deciPointSize() const;
    QString defaultFamily() const;
    bool dirty() const;
    QString lastResortFamily() const;
    QString lastResortFont() const;
} Qt::Font;
