#include "helperfunctions.h"
#include "scriptconsole.h"
#include "fetchers/smartfetcher.h"

#include <QCoreApplication>
#include <QTimer>

//===========================================================================//

static void addConsoleObjectToEngine(QScriptEngine &engine);
static void addFetcherTypeToEngine(QScriptEngine &engine);
static void addQuitFunctionToEngine(QScriptEngine &engine);

//===========================================================================//

void prepareScriptEngine(QScriptEngine &engine)
{
    addConsoleObjectToEngine(engine);
    addFetcherTypeToEngine(engine);
    addQuitFunctionToEngine(engine);
}

static QScriptValue quitApplication(QScriptContext *context, QScriptEngine *engine)
{
    Q_UNUSED(context);
    QTimer::singleShot(0, QCoreApplication::instance(), SLOT(quit()));
    return engine->nullValue();
}

void addConsoleObjectToEngine(QScriptEngine &engine)
{
    ScriptConsole *console = new ScriptConsole(&engine);
    const QScriptValue scriptConsole = engine.newQObject(console);
    engine.globalObject().setProperty("console", scriptConsole);
}

static QScriptValue smartFetcherFactory(QScriptContext *context, QScriptEngine *engine)
{
    if(context->argumentCount() != 1)
    {
        context->throwError("Invalid argument count");
        return engine->nullValue();
    }

    try
    {
        SmartFetcher *fetcher = new SmartFetcher(context->argument(0).toString());
        return engine->newQObject(fetcher, QScriptEngine::ScriptOwnership);
    }
    catch(std::exception &e)
    {
        context->throwError(QString(e.what()));
        return engine->nullValue();
    }
}

void addFetcherTypeToEngine(QScriptEngine &engine)
{
    const QScriptValue smartFetcherConstructor = engine.newFunction(smartFetcherFactory);
    const QScriptValue smartFetcherMetaObject = engine.newQMetaObject(&SmartFetcher::staticMetaObject, smartFetcherConstructor);
    engine.globalObject().setProperty("Fetcher", smartFetcherMetaObject);
}

void addQuitFunctionToEngine(QScriptEngine &engine)
{
    const QScriptValue scriptQuitFun = engine.newFunction(quitApplication, 1);
    engine.globalObject().setProperty("quit", scriptQuitFun);
    engine.globalObject().setProperty("abort", scriptQuitFun);
}
