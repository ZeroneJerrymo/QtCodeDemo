#include "camera.h"
#include "ui_camera.h"

CAMERA::CAMERA(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CAMERA)
{
    ui->setupUi(this);
    setWindowTitle(tr("获取人物截图"));
    StartCamera();
}
void CAMERA::StartCamera()
{
   capture=new cv::VideoCapture(0);
    while (1)
    {
        *capture>>frame;
        cv::cvtColor(frame,frame,CV_BGR2RGB);
        img=QImage((const unsigned char*)(frame.data),frame.cols,frame.rows,frame.cols*frame.channels(),QImage::Format_RGB888);
        ui->label->clear();
        img=img.scaled(ui->label->size());
        ui->label->setPixmap(QPixmap::fromImage(img));
        QTest::qSleep(250);

    }
}

CAMERA::~CAMERA()
{
    delete ui;
    delete capture;
}
