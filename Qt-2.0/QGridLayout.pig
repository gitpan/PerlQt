#include <qlayout.h>

suicidal virtual class QGridLayout : virtual QLayout {
    enum Corner { TopLeft, TopRight, BottomLeft, BottomRight };

    QGridLayout(int, int, int = -1, const char * = 0);
    QGridLayout(QWidget *, int, int, int = 0, int = -1, const char * = 0);
    QGridLayout(QLayout *, int, int, int = -1, const char * = 0);
    virtual ~QGridLayout();
    void addColSpacing(int, int);
    void addRowSpacing(int, int);
    virtual void addItem(QLayoutItem *);
    void addLayout(QLayout *, int, int);
    void addMultiCell(QLayoutItem *, int, int, int, int, int = 0);
    void addMultiCellWidget(QWidget *, int, int, int, int, int = 0);
    void addWidget(QWidget *, int, int, int = 0);
    void expand(int, int);
    virtual QSizePolicy::ExpandData expanding() const;
    virtual bool hasHeightForWidth() const;
    virtual int heightForWidth(int) const;
    virtual void invalidate();
    virtual QLayoutIterator iterator();
    virtual QSize maximumSize() const;
    virtual QSize minimumSize() const;
    int numCols() const;
    int numRows() const;
    virtual void setColStretch(int, int);
    virtual void setGeometry(const QRect &);
    void setOrigin(QGridLayout::Corner);
    virtual void setRowStretch(int, int);
    virtual QSize sizeHint() const;
protected:
    void add(QLayoutItem *, int, int);
    bool findWidget(QWidget *, int *, int *);
} Qt::GridLayout;
