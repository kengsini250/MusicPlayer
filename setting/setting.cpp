#include "setting.h"
#include "ui_setting.h"

Setting::Setting(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Setting)
{
  ui->setupUi(this);

  connect(ui->buttonBox,&QDialogButtonBox::accepted,[this]{
      if(backgroundImg.isEmpty()){}
      else emit backgroundImgPath(backgroundImg);
      qDebug()<<backgroundImg;
    });

  //select file
  connect(ui->backgroundPushButton,&QPushButton::clicked,[this]{
      QString t = QFileDialog::getOpenFileName(this,"Image",".","Image(*.jpg *.png)");
      backgroundImg = t;
    });

  //Request(test)
  manager = new QNetworkAccessManager(this);
  connect(ui->backgroundLineEdit,&QLineEdit::textChanged,[this]{
      QString _b = ui->backgroundLineEdit->text();
      if(_b.isEmpty()){}
      else{
          r.setUrl(_b);
          connect(manager,&QNetworkAccessManager::finished,[this](QNetworkReply *reply){
            if(reply->error() == QNetworkReply::NoError){
                QByteArray bytes = reply->readAll();
#ifdef QT_DEBUG
                QString t = "../MusicPlayer/pic/temp/test.png";
#else
                QString t = "./pic/temp/test.png";
#endif
                QFile file(t);
                if (file.open(QIODevice::Append))
                  file.write(bytes);
                file.close();
                backgroundImg = t;
              }
          });
          manager->get(r);
        }
    });
}

Setting::~Setting()
{
  delete ui;
}
