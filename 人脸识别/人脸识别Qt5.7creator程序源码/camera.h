#ifndef CAMERA_H
#define CAMERA_H

#include <QDialog>
#include <opencv2/opencv.hpp>
#include <QImage>
#include <QPixmap>

namespace Ui {
class CAMERA;
}

class CAMERA : public QDialog
{
    Q_OBJECT

public:
    explicit CAMERA(QWidget *parent = 0);
    ~CAMERA();
    void StartCamera();

private:
    Ui::CAMERA *ui;
    cv::Mat frame;
    cv::VideoCapture *capture;
    QImage img;
};

#endif // CAMERA_H
