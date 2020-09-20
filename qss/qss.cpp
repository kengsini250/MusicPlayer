#include "qss.h"

Qss::Qss()
{
}

Qss::Qss(const QString &qssFile)
{
  QFile* file = new QFile(qssFile);
  if(file->open(QIODevice::ReadOnly))
    {
      qss = QLatin1String(file->readAll());
    }else{
    }
  file->close();
}

QString Qss::getQss()
{
  return qss;
}
