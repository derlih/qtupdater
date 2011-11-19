#include "updater.h"
#include "updaterexception.h"
#include "fetchers/smartfetcher.h"

#include <QScriptEngine>

#ifdef QT_SCRIPTTOOLS_LIB
#include <QScriptEngineDebugger>
#include <QAction>
#endif

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
        , engine()

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
    QScriptEngine engine;

#ifdef QT_SCRIPTTOOLS_LIB
    QScriptEngineDebugger debugger;
#endif
};

//===========================================================================//

Updater::Updater(const QUrl updateScript, const QString appInstallPath, const QString appUserPath, QObject *parent)
    : QObject(parent)
    , d_ptr(new UpdaterPrivate(this, updateScript, appInstallPath, appUserPath))
{
    Q_D(Updater);

    connect(&d->fetcher, SIGNAL(done(QByteArray)), this, SLOT(onScriptFetchDone(QByteArray)));
    connect(&d->fetcher, SIGNAL(error(QString)), this, SIGNAL(scriptFetchError(QString)));
    d->fetcher.fetch();
}

Updater::~Updater()
{
    delete d_ptr;
}

void Updater::onScriptFetchDone(QByteArray data)
{
    Q_D(Updater);

#ifdef QT_SCRIPTTOOLS_LIB
    d->debugger.attachTo(&d->engine);
    d->debugger.action(QScriptEngineDebugger::InterruptAction)->trigger();
#endif

    d->engine.evaluate(data);
}
