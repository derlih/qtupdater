#include "filefetcher.h"
#include "updaterexception.h"

#include <QFile>

//===========================================================================//

class FileFetcherPrivate
{
public:
    FileFetcherPrivate(FileFetcher *parent, const QUrl url)
        : q_ptr(parent)
        , url(url)
    {
        if(url.scheme() != "file")
            throw InvalidSchemeException("Url scheme is not 'file://'");

        file.setFileName(url.toLocalFile());
        if(!file.open(QIODevice::ReadOnly))
            throw UpdaterException("Can't open file " + file.fileName());
    }

    Q_DECLARE_PUBLIC(FileFetcher)
    FileFetcher * const q_ptr;

    const QUrl url;
    QFile file;
};

//===========================================================================//

FileFetcher::FileFetcher(const QUrl url, QObject *parent)
    : Fetcher(parent)
    , d_ptr(new FileFetcherPrivate(this, url))
{
}

FileFetcher::~FileFetcher()
{
    delete d_ptr;
}

void FileFetcher::fetch()
{
    Q_D(FileFetcher);
    QByteArray data = d->file.readAll();
    emit done(data);
}
