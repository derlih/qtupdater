#include "scriptconsole.h"

#include <QDebug>

ScriptConsole::ScriptConsole(QObject *parent)
    : QObject(parent)
{
}

void ScriptConsole::log(QString msg)
{
    qDebug() << msg;
}

void ScriptConsole::warn(QString msg)
{
    qWarning() << msg;
}

void ScriptConsole::critical(QString msg)
{
    qCritical() << msg;
}
