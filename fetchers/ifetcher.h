#ifndef IFETCHER_H
#define IFETCHER_H

#include <QObject>

class IFetcher : public QObject
{
    Q_OBJECT
public:
    virtual ~IFetcher() {}

    virtual void fetch() = 0;

Q_SIGNALS:
    void done(QByteArray);
    void error(QString);
};

#endif // IFETCHER_H
