#include "scriptconsole.h"

#include <QDebug>

//===========================================================================//

static void printToConsole(QtMsgType type, QString msg);

//===========================================================================//

ScriptConsole::ScriptConsole(QObject *parent)
    : QObject(parent)
{

}

void ScriptConsole::log(QString msg)
{
    printToConsole(QtDebugMsg, msg);
}

void ScriptConsole::warn(QString msg)
{
    printToConsole(QtWarningMsg, msg);
}

void ScriptConsole::critical(QString msg)
{
    printToConsole(QtCriticalMsg, msg);
}

//===========================================================================//

void printToConsole(QtMsgType type, QString msg)
{
    QDebug d = qDebug();

    if(type == QtWarningMsg)
        d = qWarning();
    else
        d = qCritical();

    d << "[JS]" << msg;
}
