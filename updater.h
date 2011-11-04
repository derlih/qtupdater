#ifndef UPDATER_H
#define UPDATER_H

#include <QObject>
#include <QUrl>

class UpdaterPrivate;

class Updater : public QObject
{
    Q_OBJECT
public:
    explicit Updater(const QUrl updateScript, const QString appInstallPath, const QString appUserPath, QObject *parent = 0);
    ~Updater();

Q_SIGNALS:
    void scriptFetchError(QString error);

private Q_SLOTS:
    void onScriptFetchDone(QByteArray data);

private:
    Q_DISABLE_COPY(Updater)
    Q_DECLARE_PRIVATE(Updater)
    UpdaterPrivate * const d_ptr;
};

#endif // UPDATER_H
