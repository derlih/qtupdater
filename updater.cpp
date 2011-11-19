#include "updater.h"
#include "updaterexception.h"
#include "fetchers/smartfetcher.h"
#include "scripthelpers/scriptconsole.h"

#include <QScriptEngine>
#include <QCoreApplication>
#include <QTimer>

#if defined(USE_SCRIPT_DEBUGGER)
#include <QScriptEngineDebugger>
#include <QAction>
#endif

//===========================================================================//

static QScriptValue quitApplication(QScriptContext *context, QScriptEngine *engine);

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
#if defined(USE_SCRIPT_DEBUGGER)
        , debugger()
#endif

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

#if defined(USE_SCRIPT_DEBUGGER)
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

#if defined(USE_SCRIPT_DEBUGGER)
    d->debugger.attachTo(&d->engine);
//    d->debugger.action(QScriptEngineDebugger::InterruptAction)->trigger();
#endif

    { // Add 'console' object to js context
        ScriptConsole *console = new ScriptConsole(this);
        QScriptValue scriptConsole = d->engine.newQObject(console);
        d->engine.globalObject().setProperty("console", scriptConsole);
    }

    { // Add 'quit' function to js context
        QScriptValue scriptQuitFun = d->engine.newFunction(quitApplication);
        d->engine.globalObject().setProperty("quit", scriptQuitFun);
    }

    d->engine.evaluate(data);
}

//===========================================================================//

#include <QDebug>
QScriptValue quitApplication(QScriptContext *context, QScriptEngine *engine)
{
    Q_UNUSED(context);
    QTimer::singleShot(0, QCoreApplication::instance(), SLOT(quit()));
    return engine->nullValue();
}
