#include <qstylesheet.h>

suicidal class QStyleSheetItem {
    enum AdditionalStyleValues { Undefined  = - 1};
    enum DisplayMode { DisplayBlock, DisplayInline, DisplayListItem,
		       DisplayNone };
    enum ListStyle { ListDisc, ListCircle, ListSquare, ListDecimal,
		     ListLowerAlpha, ListUpperAlpha };
    enum Margin { MarginLeft, MarginRight, MarginTop, MarginBottom,
		  MarginAll, MarginVertical, MarginHorizontal };
    enum WhiteSpaceMode {WhiteSpaceNormal, WhiteSpacePre };

    QStyleSheetItem(QStyleSheet *, const QString &);
    ~QStyleSheetItem();
    int alignment() const;
    bool allowedInContext(const QStyleSheetItem *) const;
    QColor color() const;
    QString contexts() const;
    bool definesFontItalic() const;
    bool definesFontUnderline() const;
    QStyleSheetItem::DisplayMode displayMode() const;
    QString fontFamily() const;
    bool fontItalic() const;
    int fontSize() const;
    bool fontUnderline() const;
    int fontWeight() const;
    bool isAnchor() const;
    QStyleSheetItem::ListStyle listStyle() const;
    int logicalFontSize() const;
    int logicalFontSizeStep() const;
    int margin(QStyleSheetItem::Margin) const;
    QString name() const;
    int numberOfColumns() const;
    bool selfNesting() const;
    void setAlignment(int);
    void setAnchor(bool);
    void setColor(const QColor &);
    void setContexts(const QString &);
    void setDisplayMode(QStyleSheetItem::DisplayMode);
    void setFontFamily(const QString &);
    void setFontItalic(bool);
    void setFontSize(int);
    void setFontUnderline(bool);
    void setFontWeight(int);
    void setListStyle(QStyleSheetItem::ListStyle);
    void setLogicalFontSize(int);
    void setLogicalFontSizeStep(int);
    void setMargin(QStyleSheetItem::Margin, int);
    void setNumberOfColumns(int);
    void setSelfNesting(bool);
    void setWhiteSpaceMode(QStyleSheetItem::WhiteSpaceMode);
    QStyleSheet *styleSheet();    // watch for const
    QStyleSheetItem::WhiteSpaceMode whiteSpaceMode() const;
} Qt::StyleSheetItem;
