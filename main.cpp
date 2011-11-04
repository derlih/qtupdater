#if defined(QT_GUI_LIB)
#include <QApplication>
#else
#include <QCoreApplication>
#endif

#include <QDir>
#include <QUrl>
#include <QScopedPointer>

#include "updater.h"

//===========================================================================//

int main(int argc, char **argv)
{
    QScopedPointer<QCoreApplication> app(
            #if defined(QT_GUI_LIB)
                new QApplication(argc, argv)
            #else
                new QCoreApplication(argc, argv)
            #endif
                );

    QString appInstallPath = QCoreApplication::applicationDirPath();
    QString appUserPath;
    QUrl updateScript;

    const QStringList args = QCoreApplication::arguments();
    Q_FOREACH(QString arg, args)
    {
        static const QString kAppInstallPathArg = "--app-install-path=";
        static const QString kAppUserPathArg = "--app-user-path=";
        static const QString kUpdateScriptArg = "--update-script=";

        if(arg.startsWith(kAppInstallPathArg))
        {
            appInstallPath = arg.remove(kAppInstallPathArg).simplified();
        }
        else if(arg.startsWith(kAppUserPathArg))
        {
            appUserPath = arg.remove(kAppUserPathArg).simplified();
        }
        else if(arg.startsWith(kUpdateScriptArg))
        {
            updateScript = arg.remove(kUpdateScriptArg).simplified();
        }
    }

    if(updateScript.isEmpty() && args.size() == 2)
    {
        updateScript = args.at(1);
    }

    try
    {
        Updater updater(updateScript, appInstallPath, appUserPath, app.data());
        return app->exec();
    }
    catch(...)
    {
        return 1;
    }
}
