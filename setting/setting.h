#ifndef SETTING_H
#define SETTING_H

#include <QDialog>

#include <QString>
#include <QFileDialog>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QByteArray>
#include <QFile>

namespace Ui {
  class Setting;
}

class Setting : public QDialog
{
  Q_OBJECT

public:
  explicit Setting(QWidget *parent = nullptr);
  ~Setting();

private:
  Ui::Setting *ui;
  QString backgroundImg = "";
  QNetworkAccessManager *manager;
  QNetworkRequest r;

signals:
  void backgroundImgPath(const QString& p);
};

#endif // SETTING_H
