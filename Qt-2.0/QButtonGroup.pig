#include <qbuttongroup.h>

suicidal virtual class QButtonGroup : virtual QGroupBox {
    QButtonGroup(QWidget * = 0, const char * = 0);
    QButtonGroup(const QString &, QWidget * = 0, const char * = 0);
    QButtonGroup(int, Qt::Orientation, QWidget * = 0, const char * = 0);
    QButtonGroup(int, Qt::Orientation, const QString &, QWidget * = 0, const char * = 0);
    virtual ~QButtonGroup();
    int count() const;
    QButton *find(int) const;
    int id(QButton *) const;
    int insert(QButton *, int = -1);
    bool isExclusive() const;
    bool isRadioButtonExclusive() const;
    virtual void moveFocus(int);
    void remove(QButton *);
    QButton *selected();
    virtual void setButton(int);
    virtual void setExclusive(bool);
    virtual void setRadioButtonExclusive(bool);
protected:
    void buttonClicked() slot;
    void buttonPressed() slot;
    void buttonReleased() slot;
    void buttonToggled(bool) slot;
    void clicked(int) signal;
    void pressed(int) signal;
    void released(int) signal;
} Qt::ButtonGroup;
