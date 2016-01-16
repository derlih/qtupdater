#include "helperfunctions.h"
#include "scriptconsole.h"
#include "fetchers/smartfetcher.h"

#include <QCoreApplication>
#include <QTimer>
#include <QByteArray>
#include <QCryptographicHash>

//===========================================================================//

static void addConsoleObjectToEngine(QScriptEngine &engine);
static void addFetcherTypeToEngine(QScriptEngine &engine);
static void addQuitFunctionToEngine(QScriptEngine &engine);

static void addHashFunctionsToEngine(QScriptEngine &engine);

//===========================================================================//

void prepareScriptEngine(QScriptEngine &engine)
{
    addConsoleObjectToEngine(engine);
    addFetcherTypeToEngine(engine);
    addQuitFunctionToEngine(engine);
    addHashFunctionsToEngine(engine);
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


#include <QDebug>
static QScriptValue calculateHash(QScriptContext *context, QScriptEngine *engine, QCryptographicHash::Algorithm algorithm)
{
    if(context->argumentCount() != 1)
    {
        context->throwError("Invalid argument count");
        return engine->nullValue();
    }

    const QByteArray &data = qScriptValueToValue<QByteArray>(context->argument(0));
    const QByteArray &hash = QCryptographicHash::hash(data, algorithm);

    QString result;
    for(int i = 0, sz = hash.size(); i < sz; ++i)
    {
        result += QString::number(hash.at(i), 16).right(2);
    }

    return result;
}

static QScriptValue calculateMd4(QScriptContext *context, QScriptEngine *engine)
{
    return calculateHash(context, engine, QCryptographicHash::Md4);
}

static QScriptValue calculateMd5(QScriptContext *context, QScriptEngine *engine)
{
    return calculateHash(context, engine, QCryptographicHash::Md5);
}

static QScriptValue calculateSha1(QScriptContext *context, QScriptEngine *engine)
{
    return calculateHash(context, engine, QCryptographicHash::Sha1);
}

void addHashFunctionsToEngine(QScriptEngine &engine)
{
    const QScriptValue scriptMd4Fun = engine.newFunction(calculateMd4, 1);
    const QScriptValue scriptMd5Fun = engine.newFunction(calculateMd5, 1);
    const QScriptValue scriptSha1Fun = engine.newFunction(calculateSha1, 1);

    engine.globalObject().setProperty("md4", scriptMd4Fun);
    engine.globalObject().setProperty("md5", scriptMd5Fun);
    engine.globalObject().setProperty("sha1", scriptSha1Fun);
}
