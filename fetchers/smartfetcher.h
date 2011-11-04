#ifndef SMARTFETCHER_H
#define SMARTFETCHER_H

#include "ifetcher.h"

#include <QUrl>

class SmartFetcher : public IFetcher
{
    Q_OBJECT
public:
    explicit SmartFetcher(const QUrl url, QObject *parent = 0);

    void fetch();

private:
    IFetcher *mFetcher;
};

#endif // SMARTFETCHER_H
