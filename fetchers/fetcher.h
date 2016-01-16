#ifndef IFETCHER_H
#define IFETCHER_H

#include <QObject>

class Fetcher : public QObject
{
    Q_OBJECT
public:
    Fetcher(QObject *parent = 0) : QObject(parent) {}
    virtual ~Fetcher() {}

public Q_SLOTS:
    virtual void fetch() = 0;

Q_SIGNALS:
    void done(QByteArray);
    void error(QString);
};

#endif // IFETCHER_H
