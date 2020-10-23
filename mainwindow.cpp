#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  setWindowFlag(Qt::FramelessWindowHint);

  //browse
  QString t = "https://www.google.co.jp/";
  ui->addressLineEdit->setText(t);
  ui->webEngineView->load(QUrl(t));
  connect(ui->goPushButton, &QPushButton::clicked, [this] {
      ui->webEngineView->load(QUrl(ui->addressLineEdit->text()));
    });
  connect(ui->webEngineView, &QWebEngineView::loadStarted, [] {
      //ui->statusBar->showMessage("loading...");
    });
  connect(ui->webEngineView, &QWebEngineView::loadFinished, [](bool end) {
      if (end == true) {
          //ui->statusBar->showMessage("Finished");
        }
    });

  //setting
  setting = new Setting;

  //Qss
  Qss qss(":/qss/qss.qss");
  setStyleSheet(qss.getQss());
  setWindowIcon(QIcon(":/pic/mainIcon.jpg"));

  //no edit
  ui->_AllMusic->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui->_MyList->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui->_AddMusic->setEnabled(0);

  //slider
  connect(ui->slider,&QSlider::sliderMoved,[=](int i){
      if(!(music.mediaStatus() == QMediaPlayer::NoMedia)){
          music.pause();
          music.setPosition(i);
        }
    });
  connect(ui->slider,&QSlider::sliderReleased,&music,&QMediaPlayer::play);

  connect(&music,&QMediaPlayer::durationChanged,[=](qint64 d){
      ui->slider->setMaximum(d);
      MusicData t = musicTime(d);
      QString time = QString::number(t.h)+" : "+QString::number(t.m)+" : "+QString::number(t.s);
      ui->timeLabel_2->setText(time);
    });
  connect(&music,&QMediaPlayer::positionChanged,[=](qint64 d){
      ui->slider->setValue(d);
      MusicData t = musicTime(d);
      QString time = QString::number(t.h)+" : "+QString::number(t.m)+" : "+QString::number(t.s);
      ui->timeLabel_1->setText(time);
    });

  //listview clear selection
  connect(ui->_AllMusic,&QListView::clicked,ui->_MyList,&QListView::clearSelection);
  connect(ui->_MyList,&QListView::clicked,ui->_AllMusic,&QListView::clearSelection);

  //update folder
  connect(ui->_AllMusic,&QListView::doubleClicked,[this](QModelIndex index){
    QString p = path.path() + "/" + index.data().toString();
    QFileInfo currTarget(p);
    if(currTarget.isDir())
      {
        path.setPath(p);
        path.setPath(path.absolutePath());
        updateListUI();
      }
    else
      //play music
      {
        music.setMedia(QMediaContent(p));
        music.play();
      }
  });

  //add music
  connect(ui->_AddMusic,&QPushButton::clicked,[&]{
      QString name = ui->_AllMusic->currentIndex().data().toString();
      addFolder(&path, name, &list);
      updateMyList();
    });

  //delete music
  connect(ui->_DeleteMusic,&QPushButton::clicked,[&]{
      if(!list.isNull()){
          list.deleteMusic(ui->_MyList->currentIndex());
          //saveload.save(list);//auto save
          updateMyList();
        }
    });

  //play music (my list)
  connect(ui->_MyList,&QListView::doubleClicked,[&](QModelIndex index){
    QString name = index.data().toString();
    QString p = list.getMusic(index)->getMusicPath();
    music.setMedia(QUrl::fromLocalFile(p));
    music.play();
    list.updatePlaying(index);
    //statusBar()->showMessage(name);
  });

  //change state
  connect(ui->_Play,&QPushButton::clicked,[&]{
      switch(music.state())
        {
        case QMediaPlayer::PlayingState:
          music.pause();
          break;
        case QMediaPlayer::PausedState:
          music.play();
          break;
        case QMediaPlayer::StoppedState:
          break;
        }
    });

  //next music
  connect(ui->_Next,&QPushButton::clicked,[&]{
      if(!list.isNull()){
          Music* temp = list.nextMusic();
          QString p = temp->getMusicPath();
          qDebug()<<p;
          music.setMedia(QUrl::fromLocalFile(p));
          music.play();
          //statusBar()->showMessage(temp->getMusicName());
        }
    });

  //previous music
  connect(ui->_Pre,&QPushButton::clicked,[&]{
      if(!list.isNull()){
          Music* temp = list.preMusic();
          QString p = temp->getMusicPath();
          music.setMedia(QUrl::fromLocalFile(p));
          music.play();
          //statusBar()->showMessage(temp->getMusicName());
        }
    });

}

MainWindow::~MainWindow()
{
  delete ui;
  delete setting;
}

void MainWindow::updateListUI()
{
  QStringList allFile = path.entryList();
  allFile.removeOne(".");
  QStandardItemModel* fileItem = new QStandardItemModel(this);
  auto p = allFile.begin();
  QString fileInfo = path.path()+"/"+*p;
  while(p != allFile.end())
    {
      QFileInfo currTarget(fileInfo);
      if(currTarget.isDir()||(*p).contains(".mp3")||(*p).contains(".wav")||(*p).contains(".flac")){
          QStandardItem* file = new QStandardItem(*p);
          fileItem->appendRow(file);
        }
      p++;
    }
  ui->_AllMusic->setModel(fileItem);
}

void MainWindow::updateMyList()
{
  auto allMusic = list.getMusicList();
  QStandardItemModel* fileItem = new QStandardItemModel(this);
  QString name;
  auto p = allMusic.begin();
  while(p!=allMusic.end()){
      name = (*p)->getMusicName();
      QStandardItem* file = new QStandardItem(name);
      fileItem->appendRow(file);
      p++;
    }
  ui->_MyList->setModel(fileItem);
}

void MainWindow::paintEvent(QPaintEvent *)
{
  auto tmp = QPixmap(backgroundImg);
  if(tmp.isNull())
    {
      tmp = QPixmap(":/pic/background.jpg");
    }
  QPixmap img = tmp.scaled(size());
  QPainter painter(this);
  painter.drawPixmap(rect(),img);
}

//open folder
void MainWindow::openDir(const QDir &p)
{
  path = p;
  ui->_AddMusic->setEnabled(1);
  updateListUI();
}

//open setting dialog
void MainWindow::settingDialog()
{
  setting->show();
  setting->activateWindow();
  connect(setting,&Setting::backgroundImgPath,[this](const QString& p){backgroundImg = p;update();});
}

void MainWindow::showhideWeb()
{
    if(!HideWebViewFlag)
    {
        ui->webEngineView->hide();
        ui->addressLineEdit->hide();
        ui->goPushButton->hide();


    }else{
        ui->webEngineView->show();
        ui->addressLineEdit->show();
        ui->goPushButton->show();
    }

    HideWebViewFlag = !HideWebViewFlag;
}

//save
void MainWindow::save()
{
  saveload.save(list);
}

//load
void MainWindow::load()
{
  list = saveload.load();
  updateMyList();
}
