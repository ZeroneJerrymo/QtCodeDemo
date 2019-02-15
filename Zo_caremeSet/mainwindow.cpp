#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    camera=new QCamera(this); //摄像头
    viewfinder=new QCameraViewfinder(this); // 取景器，用于显示摄像头的数据
    imageCapture=new QCameraImageCapture(camera); //获取摄像头当前帧

    ui->ImageView->addWidget(viewfinder);
    ui->ImageCapture->setScaledContents(true);
//    m_pCamera->setCaptureDestination(QCameraImageCapture::CaptureToFile);
//    //设置采集模式
//    camera->setCaptureMode(QCamera::CaptureStillImage);//将其采集为图片
//    camera->setCaptureMode(QCamera::CaptureMode::CaptureViewfinder);//将其采集到取景器中

    //设置取景器
    camera->setViewfinder(viewfinder);
    //开启相机
    camera->start();
    connect(imageCapture, SIGNAL(imageCaptured(int,QImage)), this, SLOT(displayImage(int,QImage)));

    //如果曝光和白平衡模式不是手动模式，那么就要使用请求的锁来锁定相机设置
    //按下对焦按钮，触发camera的动作，锁定相机设置：对焦于单次自动对焦模式，曝光和白平衡。
   // connect(buttonCapture, SIGNAL(clicked(bool)), camera, SLOT(searchAndLock()));
    connect(ui->buttonCapture, SIGNAL(clicked()), this, SLOT(captureImage()));
    connect(ui->buttonSave, SIGNAL(clicked()), this, SLOT(saveImage()));
    connect(ui->buttonQuit, SIGNAL(clicked()), qApp, SLOT(quit()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::captureImage()
{
    ui->statusBar->showMessage(tr("capturing..."), 1000);
    imageCapture->capture();
}

void MainWindow::displayImage(int , QImage image)
{
    ui->ImageCapture->setPixmap(QPixmap::fromImage(image));

    ui->statusBar->showMessage(tr("capture OK!"), 5000);
}

void MainWindow::saveImage()
{
    QString fileName=QFileDialog::getSaveFileName(this, tr("save file"), QDir::homePath(), tr("jpegfile(*.jpg)"));
    if(fileName.isEmpty()) {
        ui->statusBar->showMessage(tr("save cancel"), 5000);
        return;
    }
    const QPixmap* pixmap=ui->ImageCapture->pixmap();
    if(pixmap) {
        pixmap->save(fileName);
        ui->statusBar->showMessage(tr("save OK"), 5000);
    }
}
