#include "smartfetcher.h"
#include "updaterexception.h"
#include "filefetcher.h"
#include "httpfetcher.h"

//===========================================================================//

static IFetcher* fetcherFactory(const QUrl url, QObject *parent);

//===========================================================================//

SmartFetcher::SmartFetcher(const QUrl url, QObject *parent)
    : IFetcher(parent)
    , mFetcher(fetcherFactory(url, this))
{
    connect(mFetcher, SIGNAL(done(QByteArray)), this, SIGNAL(done(QByteArray)));
    connect(mFetcher, SIGNAL(error(QString)), this, SIGNAL(error(QString)));
}

void SmartFetcher::fetch()
{
    mFetcher->fetch();
}

//===========================================================================//

IFetcher* fetcherFactory(const QUrl url, QObject *parent)
{
    const QString urlScheme = url.scheme();
    if(urlScheme.isEmpty())
    {
//        throw InvalidSchemeException("Url scheme is empty");
        return new FileFetcher(QUrl::fromLocalFile(url.toString()));
    }
    else if(urlScheme == "file")
    {
        return new FileFetcher(url, parent);
    }
    else if(urlScheme == "http" || urlScheme == "https")
    {
        return new HttpFetcher(url, parent);
    }

    throw InvalidSchemeException("Unsupported scheme");
}
