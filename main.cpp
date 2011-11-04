#if defined(QT_GUI_LIB)
    #include <QApplication>
#else
    #include <QCoreApplication>
#endif

#include <QDir>

#include <memory>

int main(int argc, char **argv)
{
    std::auto_ptr<QCoreApplication> app(
            #if defined(QT_GUI_LIB)
                new QApplication(argc, argv)
            #else
                new QCoreApplication(argc, argv)
            #endif
                );

    QString appInstallPath = QCoreApplication::applicationDirPath();
    QString appUserPath;

    const QStringList args = QCoreApplication::arguments();
    Q_FOREACH(QString arg, args)
    {
        static const QString kAppInstallPathArg = "--app-install-path";
        static const QString kAppUserPathArg = "--app-user-path";

        if(arg.startsWith(kAppInstallPathArg))
        {
            appInstallPath = arg.remove(kAppInstallPathArg).simplified();
        }
        else if(arg.startsWith("--app-user-path"))
        {
            appUserPath = arg.remove(kAppUserPathArg).simplified();
        }
    }


    return app->exec();
}
