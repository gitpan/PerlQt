#include <qsizepolicy.h>

struct QSizePolicy {
    enum SizeType { Fixed,
                    Minimum,
                    Maximum,
                    Preferred,
                    MinimumExpanding,
                    Expanding };
    enum ExpandData { NoDirection,
                      Horizontal,
                      Vertical,
                      BothDirections };

    QSizePolicy();
    QSizePolicy(QSizePolicy::SizeType, QSizePolicy::SizeType, bool = FALSE);
    QSizePolicy(const QSizePolicy &);
    QSizePolicy::ExpandData expanding() const;
    bool hasHeightForWidth() const;
    QSizePolicy::SizeType horData() const;
    bool mayGrowHorizontally() const;
    bool mayGrowVertically() const;
    bool mayShrinkHorizontally() const;
    bool mayShrinkVertically() const;
    void setHeightForWidth(bool);
    void setHorData(QSizePolicy::SizeType);
    void setVerData(QSizePolicy::SizeType);
    QSizePolicy::SizeType verData() const;
} Qt::SizePolicy;
