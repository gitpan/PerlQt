#include <qsessionmanager.h>

; This class generates a warning.... darn

class QSessionManager : QObject {
    enum RestartHint { RestartIfRunning, RestartAnyway,
		       RestartImmediately, RestartNever };
    bool allowsErrorInteraction();
    bool allowsInteraction();
    void cancel();
    QStringList discardCommand() const;
    HANDLE handle() const;
    bool isPhase2() const;
    void release();
    void requestPhase2();
    QStringList restartCommand() const;
    QSessionManager::RestartHint restartHint() const;
    void setRestartHint(QSessionManager::RestartHint);
    void setDiscardCommand(const QStringList &);
    void setProperty(const QString &, const QString &);
    void setProperty(const QString &, const QStringList &);
    void setRestartCommand(const QStringList &);
    QString sessionId() const;
private:
    ~QSessionManager();
} Qt::SessionManager;
