#include <qcombobox.h>

suicidal virtual class QComboBox : virtual QWidget {
    enum Policy {
        NoInsertion, AtTop, AtCurrent, AtBottom, AfterCurrent, BeforeCurrent
    };

    QComboBox(QWidget * = 0, const char * = 0);
    QComboBox(bool, QWidget * = 0, const char * = 0);
    virtual ~QComboBox();
    bool autoCompletion() const;
    bool autoResize() const;
    void changeItem(const QString &, int);
    void changeItem(const QPixmap &, int);
    void clear();
    void clearEdit() slot;
    void clearValidator() slot;
    int count() const;
    int currentItem() const;
    QString currentText() const;
    virtual bool eventFilter(QObject *, QEvent *);
    void insertItem(const QPixmap &, int = -1);
    void insertItem(const QString &, int = -1);
    void insertStringList(const QStringList &, int = -1);
    QComboBox::Policy insertionPolicy() const;
    QListBox *listBox() const;
    int maxCount() const;
    const QPixmap *pixmap(int) const;
    void removeItem(int);
    virtual void setAutoResize(bool);
    virtual void setAutoCompletion(bool);
    virtual void setBackgroundColor(const QColor &);
    virtual void setCurrentItem(int);
    virtual void setEditText(const QString &);
    virtual void setEnabled(bool);
    virtual void setFont(const QFont &);
    virtual void setInsertionPolicy(QComboBox::Policy);
    virtual void setListBox(QListBox *);
    virtual void setMaxCount(int);
    virtual void setPalette(const QPalette &);
    virtual void setSizeLimit(int);
    virtual void setValidator(QValidator *);
    virtual QSize sizeHint() const;
    int sizeLimit() const;
    virtual QSizePolicy sizePolicy() const;
    QString text(int) const;
    const QValidator *validator() const;
protected:
    void activated(int) signal;
    void activated(const QString &) signal;
    virtual void focusInEvent(QFocusEvent *);
    void highlighted(int) signal;
    void highlighted(const QString &) signal;
    virtual void keyPressEvent(QKeyEvent *);
    virtual void mouseDoubleClickEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void paintEvent(QPaintEvent *);
    void popup();
    virtual void resizeEvent(QResizeEvent *);
    virtual void styleChange(QStyle &);
    void textChanged(const QString &) signal;
    virtual void updateMask();
} Qt::ComboBox;
