#include <qprinter.h>

virtual class QPrinter : QPaintDevice {
    enum Orientation { Portrait, Landscape };
    enum PageSize    { A4, B5, Letter, Legal, Executive,
                       A0, A1, A2, A3, A5, A6, A7, A8, A9, B0, B1,
                       B10, B2, B3, B4, B6, B7, B8, B9, C5E, Comm10E,
                       DLE, Folio, Ledger, Tabloid, NPageSize };
    enum PageOrder   { FirstPageFirst, LastPageFirst };
    enum ColorMode   { GrayScale, Color };
    QPrinter();
    virtual ~QPrinter();
    bool abort();
    bool aborted() const;
    QPrinter::ColorMode colorMode() const;
    QString creator() const;
    QString docName() const;
    int fromPage() const;
    bool fullPage() const;
    QSize margins() const;
    int maxPage() const;
    int minPage() const;
    bool newPage();
    int numCopies() const;
    QPrinter::Orientation orientation() const;
    QString outputFileName() const;
    bool outputToFile() const;
    QPrinter::PageOrder pageOrder() const;
    QPrinter::PageSize pageSize() const;
    QString printerName() const;
    QString printerSelectionOption() const;
    QString printProgram() const;
    virtual void setColorMode(QPrinter::ColorMode);
    virtual void setCreator(const QString &);
    virtual void setDocName(const QString &);
    virtual void setFromTo(int, int);
    virtual void setFullPage(bool);
    virtual void setMinMax(int, int);
    virtual void setNumCopies(int);
    virtual void setOrientation(QPrinter::Orientation);
    virtual void setOutputFileName(const QString &);
    virtual void setOutputToFile(bool);
    virtual void setPageOrder(QPrinter::PageOrder);
    virtual void setPageSize(QPrinter::PageSize);
    virtual void setPrinterName(const QString &);
    virtual void setPrinterSelectionOption(const QString &);
    virtual void setPrintProgram(const QString &);
    void setup(QWidget * = 0);
    int toPage() const;
} Qt::Printer;
