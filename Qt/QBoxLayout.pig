#include <qlayout.h>

suicidal virtual class QBoxLayout : virtual QLayout {
    enum Direction { LeftToRight, RightToLeft, TopToBottom, BottomToTop,
                     Down, Up };

    QBoxLayout(QBoxLayout::Direction, int = -1, const char * = 0);
    QBoxLayout(QWidget *, QBoxLayout::Direction, int = 0, int = -1, const char * = 0);
    QBoxLayout(QLayout *, QBoxLayout::Direction, int = -1, const char * = 0);
    virtual ~QBoxLayout();
    virtual void addItem(QLayoutItem *);
    void addLayout(QLayout *, int = 0);
    void addSpacing(int);
    void addStretch(int = 0);
    void addStrut(int);
    void addWidget(QWidget *, int = 0, int = 0);
    QBoxLayout::Direction direction() const;
    virtual QSizePolicy::ExpandData expanding() const;
    virtual bool hasHeightForWidth() const;
    virtual int heightForWidth(int) const;
    virtual void invalidate();
    virtual QLayoutIterator iterator();
    virtual QSize maximumSize() const;
    virtual QSize minimumSize() const;
    virtual void setGeometry(const QRect &);
    bool setStretchFactor(QWidget *, int);
    virtual QSize sizeHint() const;
} Qt::BoxLayout;
