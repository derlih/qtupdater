#ifndef SCRIPTCONSOLE_H
#define SCRIPTCONSOLE_H

#include <QObject>

class ScriptConsole : public QObject
{
    Q_OBJECT
public:
    explicit ScriptConsole(QObject *parent = 0);

public Q_SLOTS:
    void log(QString msg);
    void debug(QString msg);
    void warn(QString msg);
    void critical(QString msg);
};

#endif // SCRIPTCONSOLE_H
