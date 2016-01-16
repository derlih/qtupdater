#ifndef SMARTFETCHER_H
#define SMARTFETCHER_H

#include "fetcher.h"

#include <QUrl>

class SmartFetcher : public Fetcher
{
    Q_OBJECT
public:
    explicit SmartFetcher(const QUrl url, QObject *parent = 0);

    void fetch();

private:
    Fetcher *mFetcher;
};

#endif // SMARTFETCHER_H
