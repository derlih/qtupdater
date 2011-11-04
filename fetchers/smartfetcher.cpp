#include "smartfetcher.h"
#include "updaterexception.h"
#include "filefetcher.h"

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
        throw InvalidSchemeException("Url scheme is empty");
    }
    else if(urlScheme == "file")
    {
        return new FileFetcher(url, parent);
    }

    throw InvalidSchemeException("Unsupported scheme");
}
