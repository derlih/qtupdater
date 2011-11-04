#include "filefetcher.h"

class FileFetcherPrivate
{
public:
    FileFetcherPrivate(FileFetcher *parent, const QUrl url)
        : q_ptr(parent)
        , url(url)
    {
    }

    Q_DECLARE_PUBLIC(FileFetcher)
    FileFetcher * const q_ptr;

    const QUrl url;
};



FileFetcher::FileFetcher(const QUrl url, QObject *parent)
    : IFetcher(parent)
    , d_ptr(new FileFetcherPrivate(this, url))
{
}

FileFetcher::~FileFetcher()
{
    delete d_ptr;
}

void FileFetcher::fetch()
{

}
