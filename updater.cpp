#include "updater.h"
#include "updaterexception.h"
#include "fetchers/smartfetcher.h"

#include <QLabel>

//===========================================================================//

class UpdaterPrivate
{
public:
    UpdaterPrivate(Updater *parent, const QUrl updateScript, const QString appInstallPath, const QString appUserPath)
        : q_ptr(parent)
        , updateScript(updateScript)
        , appInstallPath(appInstallPath)
        , appUserPath(appUserPath)
        , fetcher(updateScript)

    {
        if(updateScript.isEmpty())
            throw UpdaterException("Update script is empty");
    }

    Q_DECLARE_PUBLIC(Updater)
    Updater * const q_ptr;

    const QUrl updateScript;
    const QString appInstallPath;
    const QString appUserPath;

    SmartFetcher fetcher;
};

//===========================================================================//

Updater::Updater(const QUrl updateScript, const QString appInstallPath, const QString appUserPath, QObject *parent)
    : QObject(parent)
    , d_ptr(new UpdaterPrivate(this, updateScript, appInstallPath, appUserPath))
{
    Q_D(Updater);

    connect(&d->fetcher, SIGNAL(done(QByteArray)), this, SLOT(onScriptFetchDone(QByteArray)));
    connect(&d->fetcher, SIGNAL(error(QString)), this, SLOT(scriptFetchError(QString)));
    d->fetcher.fetch();
}

Updater::~Updater()
{
    delete d_ptr;
}

void Updater::onScriptFetchDone(QByteArray data)
{
    Q_UNUSED(data);
}
