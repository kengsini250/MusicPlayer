#ifndef QSS_H
#define QSS_H

#include <QFile>
#include <QString>

class Qss
{
public:
  Qss();
  Qss(const QString& qssFile);
  QString getQss();
private:
  QString qss;
};

#endif // QSS_H
