#include "fetcher.hpp"

#include <QUrl>


class HTTPFetcher : public Fetcher
{
public:
  HTTPFetcher(const QUrl &url);
  virtual ~HTTPFetcher();
};
