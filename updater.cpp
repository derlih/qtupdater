#include "updater.h"

#include <QLabel>

#include <stdexcept>

class UpdaterException : public std::runtime_error
{
public:
    explicit UpdaterException(const QString what) : std::runtime_error(what.toStdString()) {}
};

class UpdaterPrivate
{
public:
    UpdaterPrivate(Updater *parent, const QUrl updateScript, const QString appInstallPath, const QString appUserPath)
        : q_ptr(parent)
        , updateScript(updateScript)
        , appInstallPath(appInstallPath)
        , appUserPath(appUserPath)

    {
        if(updateScript.isEmpty())
            throw UpdaterException("Update script is empty");
    }

    Q_DECLARE_PUBLIC(Updater)
    Updater * const q_ptr;

    const QUrl updateScript;
    const QString appInstallPath;
    const QString appUserPath;
};

Updater::Updater(const QUrl updateScript, const QString appInstallPath, const QString appUserPath, QObject *parent)
    : QObject(parent)
    , d_ptr(new UpdaterPrivate(this, updateScript, appInstallPath, appUserPath))
{
}

Updater::~Updater()
{
    delete d_ptr;
}
