#include <QObject>
#include <QByteArray>


class Fetcher : public QObject
{
  Q_OBJECT

public:
  virtual ~Fetcher();

signals:
  void done(QByteArray);
  void error();
};
