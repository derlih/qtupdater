#include "httpfetcher.h"
#include "updaterexception.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>

//===========================================================================//

class HttpFetcherPrivate
{
public:
    HttpFetcherPrivate(HttpFetcher *parent, const QUrl url)
        : q_ptr(parent)
        , url(url)
        , manager()
        , reply(0)
    {
        if(url.scheme() != "http" && url.scheme() != "https")
            throw InvalidSchemeException("Url scheme is not 'http://' or 'https://'");
    }

    void abortReplyAndClear()
    {
        if(reply)
        {
            reply->abort();
            reply->deleteLater();
            reply = 0;
        }
    }

    Q_DECLARE_PUBLIC(HttpFetcher)
    HttpFetcher * const q_ptr;

    const QUrl url;
    QNetworkAccessManager manager;
    QNetworkReply *reply;
};

//===========================================================================//

HttpFetcher::HttpFetcher(const QUrl url, QObject *parent)
    : IFetcher(parent)
    , d_ptr(new HttpFetcherPrivate(this, url))
{
}

HttpFetcher::~HttpFetcher()
{
    delete d_ptr;
}

void HttpFetcher::fetch()
{
    Q_D(HttpFetcher);
    d->abortReplyAndClear();
    d->reply = d->manager.get(QNetworkRequest(d->url));

    connect(d->reply, SIGNAL(finished()), this, SLOT(onDownloadFinished()));
    connect(d->reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onDownloadError(QNetworkReply::NetworkError)));
}

void HttpFetcher::onDownloadFinished()
{
    Q_D(HttpFetcher);
    emit done(d->reply->readAll());
    d->abortReplyAndClear();
}

void HttpFetcher::onDownloadError(QNetworkReply::NetworkError code)
{
    Q_D(HttpFetcher);
    d->abortReplyAndClear();

    QString desc;
    switch(code)
    {
    case QNetworkReply::ConnectionRefusedError:
        desc = "The remote server refused the connection (the server is not accepting requests)";
        break;
    case QNetworkReply::RemoteHostClosedError:
        desc = "The remote server closed the connection prematurely, before the entire reply was received and processed";
        break;
    case QNetworkReply::HostNotFoundError:
        desc = "The remote host name was not found (invalid hostname)";
        break;
    case QNetworkReply::TimeoutError:
        desc = "The connection to the remote server timed out";
        break;
    case QNetworkReply::SslHandshakeFailedError:
        desc = "The SSL/TLS handshake failed and the encrypted channel could not be established";
        break;
    case QNetworkReply::ProxyConnectionRefusedError:
        desc = "The connection to the proxy server was refused (the proxy server is not accepting requests)";
        break;
    case QNetworkReply::ProxyConnectionClosedError:
        desc = "The proxy server closed the connection prematurely, before the entire reply was received and processed";
        break;
    case QNetworkReply::ProxyNotFoundError:
        desc = "The proxy host name was not found (invalid proxy hostname)";
        break;
    case QNetworkReply::ProxyTimeoutError:
        desc = "The connection to the proxy timed out or the proxy did not reply in time to the request sent";
        break;
    case QNetworkReply::ProxyAuthenticationRequiredError:
        desc = "The proxy requires authentication in order to honour the request but did not accept any credentials offered (if any)";
        break;
    case QNetworkReply::ContentAccessDenied:
        desc = "The access to the remote content was denied (similar to HTTP error 401)";
        break;
    case QNetworkReply::ContentOperationNotPermittedError:
        desc = "The operation requested on the remote content is not permitted";
        break;
    case QNetworkReply::ContentNotFoundError:
        desc = "The remote content was not found at the server (similar to HTTP error 404)";
        break;
    case QNetworkReply::AuthenticationRequiredError:
        desc = "The remote server requires authentication to serve the content but the credentials provided were not accepted (if any)";
        break;
    case QNetworkReply::UnknownNetworkError:
        desc = "An unknown network-related error was detected";
        break;
    case QNetworkReply::UnknownProxyError:
        desc = "An unknown proxy-related error was detected";
        break;
    case QNetworkReply::UnknownContentError:
        desc = "An unknown error related to the remote content was detected";
        break;
    case QNetworkReply::ProtocolFailure:
        desc = "A breakdown in protocol was detected (parsing error, invalid or unexpected responses, etc.)";
        break;
    default:
        return;
    }

    emit error(desc);
}
