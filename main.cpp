#if defined(QT_GUI_LIB)
#include <QApplication>
#else
#include <QCoreApplication>
#endif

#include <QDir>
#include <QUrl>
#include <QScopedPointer>
#include <QNetworkProxy>

#include "updater.h"
#include "updaterexception.h"

//===========================================================================//

static void setupProxy();

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
        setupProxy();

        Updater updater(updateScript, appInstallPath, appUserPath, app.data());
        return app->exec();
    }
    catch(...)
    {
        return 1;
    }
}

//===========================================================================//

void setupProxy()
{
    QNetworkProxy::ProxyType proxyType = QNetworkProxy::DefaultProxy;
    QString proxyHost;
    quint64 proxyPort = 0;
    QString proxyUser;
    QString proxyPassword;

    const QStringList args = QCoreApplication::arguments();
    Q_FOREACH(QString arg, args)
    {
        static const QString kProxyTypeArg = "--proxy-type=";
        static const QString kProxyHostArg = "--proxy-host=";
        static const QString kProxyPortArg = "--proxy-port=";
        static const QString kProxyUserArg = "--proxy-user=";
        static const QString kProxyPasswordArg = "--proxy-password=";

        if(arg.startsWith(kProxyTypeArg))
        {
            const QString proxyTypeStr = arg.remove(kProxyTypeArg).simplified();
            if(proxyTypeStr == "socks5")
                proxyType = QNetworkProxy::Socks5Proxy;
            else if(proxyTypeStr == "http")
                proxyType = QNetworkProxy::HttpProxy;
            else
                throw InvalidArgException("Invalid '" + kProxyTypeArg + "' parameter");
        }
        else if(arg.startsWith(kProxyHostArg))
        {
            proxyHost = arg.remove(kProxyHostArg).simplified();
        }
        else if(arg.startsWith(kProxyPortArg))
        {
            bool ok;
            proxyPort = arg.remove(kProxyPortArg).simplified().toUShort(&ok);
            if(!ok)
                throw InvalidArgException("Invalid '" + kProxyPortArg + "' parameter");

            if(proxyPort == 0)
                throw InvalidArgException("Proxy port is set to 0");
        }
        else if(arg.startsWith(kProxyUserArg))
        {
            proxyUser = arg.remove(kProxyUserArg).simplified();
        }
        else if(arg.startsWith(kProxyPasswordArg))
        {
            proxyPassword = arg.remove(kProxyPasswordArg).simplified();
        }
    }

    if(proxyHost.isEmpty())
        return;

    if(proxyUser.isEmpty() != proxyPassword.isEmpty()) // Logical XOR :-)
        throw InvalidArgException("Invalid proxy authorization parameters");

    QNetworkProxy proxy(proxyType, proxyHost, proxyPort, proxyUser, proxyPassword);
    QNetworkProxy::setApplicationProxy(proxy);
}
