#ifndef HTTPFETCHER_H
#define HTTPFETCHER_H

#include "ifetcher.h"

#include <QUrl>
#include <QNetworkReply>

class HttpFetcherPrivate;

class HttpFetcher : public IFetcher
{
    Q_OBJECT
public:
    explicit HttpFetcher(const QUrl url, QObject *parent = 0);
    ~HttpFetcher();

    void fetch();

private Q_SLOTS:
    void onDownloadFinished();
    void onDownloadError(QNetworkReply::NetworkError code);
    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);

private:
    Q_DISABLE_COPY(HttpFetcher)
    Q_DECLARE_PRIVATE(HttpFetcher)
    HttpFetcherPrivate * const d_ptr;

};

#endif // HTTPFETCHER_H
