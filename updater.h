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

private:
    Q_DISABLE_COPY(Updater)
    Q_DECLARE_PRIVATE(Updater)
    UpdaterPrivate * const d_ptr;
};

#endif // UPDATER_H
