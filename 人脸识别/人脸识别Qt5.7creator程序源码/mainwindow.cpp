#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTextCodec>
#include <iostream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    statusLabel1=new QLabel;
    ui->setupUi(this);
    this->setWindowTitle(tr("人脸识别系统-南邮通达STITP项目"));
    this->setStatusBar();
    this->setMaximumSize(796,310);
    this->setMinimumSize(796,310);

    m_timerId = startTimer(1000);

    connect(ui->Add_action,SIGNAL(triggered(bool)),this,SLOT(on_Add_action_triggered()),Qt::UniqueConnection);
    connect(ui->dispose_action,SIGNAL(triggered(bool)),SLOT(on_dispose_action_triggered()),Qt::UniqueConnection);
    connect(ui->action_addcsv,SIGNAL(triggered(bool)),SLOT(on_action_addcsv_triggered()),Qt::UniqueConnection);
    connect(ui->action_TrainnigModel,SIGNAL(triggered(bool)),this,SLOT(on_action_TrainnigModel_triggered()),Qt::UniqueConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setStatusBar()
{
    ui->statusBar->addWidget(statusLabel1);
    QString statusLabel1MSG="当前时间:";
    QDateTime Currtime=QDateTime::currentDateTime();
    QString CurrTimeStr=Currtime.toString("yyyy-MM-dd hh:mm:ss");
    statusLabel1MSG.append(CurrTimeStr);
    statusLabel1->setText(statusLabel1MSG);

}

void MainWindow::timerEvent(QTimerEvent *event)
{
    this->setStatusBar();
}

void MainWindow::on_Add_action_triggered()
{
    addpeople.show();
}

void MainWindow::on_dispose_action_triggered()
{
    addpeople.disposePic();
}

void MainWindow::on_action_addcsv_triggered()
{
    addpeople.AddCSV();
}

void MainWindow::on_action_TrainnigModel_triggered()
{
    addpeople.TrainingModel();
}


void MainWindow::on_action_FaceRecognition_triggered()
{
    int label=0;
    addpeople.file.getManLabel();
    double confidence=0.0;
    cv::VideoCapture cap(0);    //打开默认摄像头
    if (!cap.isOpened())
    {
        QMessageBox::warning(this,tr("错误"),tr("摄像头打开失败"),QMessageBox::Ok);
        return;
    }
    cv::Mat frame;
    cv::Mat gray;

    cv::CascadeClassifier cascade;
    bool stop = false;
    //训练好的文件名称，放置在可执行文件同目录下
    cascade.load("haarcascade_frontalface_alt.xml");

    cv::Ptr<cv::FaceRecognizer> modelPCA = cv::createEigenFaceRecognizer();
    modelPCA->load("MyFacePCAModel.xml");
    int sl=0;
    while (!stop)
    {
        cap >> frame;

        //建立用于存放人脸的向量容器
        std::vector<cv::Rect> faces(0);

        cv::cvtColor(frame, gray, CV_BGR2GRAY);
        //改变图像大小，使用双线性差值
        //resize(gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR);
        //变换后的图像进行直方图均值化处理
        cv::equalizeHist(gray, gray);

        cascade.detectMultiScale(gray, faces,
            1.1, 2,cv::CASCADE_FIND_BIGGEST_OBJECT|cv::CASCADE_DO_ROUGH_SEARCH,
            cv::Size(30, 30));

        cv::Mat face;
        cv::Point text_lb;

        for (size_t i = 0; i < faces.size(); i++)
        {
            if (faces[i].height > 0 && faces[i].width > 0)
            {
                face = gray(faces[i]);
                text_lb = cv::Point(faces[i].x, faces[i].y);
                cv::rectangle(frame, faces[i], cv::Scalar(255, 0, 0), 1, 8, 0);
            }
        }

        cv::Mat face_test;

        int predictPCA = 0;
        if (face.rows >= 120)
        {
            cv::resize(face, face_test, cv::Size(92, 112));

        }
        //Mat face_test_gray;
        //cvtColor(face_test, face_test_gray, CV_BGR2GRAY);

        if (!face_test.empty())
        {
            //测试图像应该是灰度图
            int predictedLabel=-1;
            predictPCA = modelPCA->predict(face_test);
            modelPCA->predict(face_test,predictedLabel,confidence);
            qDebug()<<"predictedLabel:"<<predictedLabel;
            qDebug()<<"confidence:"<<confidence;
            qDebug()<<"s1:"<<sl;

        }
        if(sl>20)
        {
            if(label<5)
                QMessageBox::information(this,tr("失败"),tr("人脸库无此人"),QMessageBox::Ok);
            else
                QMessageBox::information(this,tr("失败"),tr("人脸确认度低"),QMessageBox::Ok);
            return;
        }
        if(predictPCA!=-1&&predictPCA!=1&&confidence<3200)
            label++;
        if(predictPCA==1||predictPCA==0)
            label--;
        qDebug()<<"label:"<<label;
        cv::waitKey(50);
        if(label>12)
        {
            //qDebug()<<predictPCA;
            //std::string name = "Being recognized";
            //cv::putText(frame, name, text_lb, cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 0, 255));
            //qDebug()<<"姓名"<<addpeople.file.who[predictPCA];
            QString name="你是-";
            name.append(addpeople.file.who[predictPCA]);
            QMessageBox::information(this,tr("识别成功"),name,QMessageBox::Ok);
            return;
        }
        sl++;

        imshow("face", frame);
        if (cv::waitKey(50) >= 0)
            stop = true;
    }
}

void MainWindow::on_actionData_triggered()
{
    QString path=QDir::currentPath();//获取程序当前目录
    path.append("\\Data");
    path.replace("/","\\");//将地址中的"/"替换为"\"，因为在Windows下使用的是"\"。
    QProcess::startDetached("explorer "+path);//打开上面获取的目录
}

void MainWindow::on_action_use_triggered()
{
    QString path=QDir::currentPath();//获取程序当前目录
    path.append("\\use");
    path.replace("/","\\");//将地址中的"/"替换为"\"，因为在Windows下使用的是"\"。
    QProcess::startDetached("explorer "+path);//打开上面获取的目录
}

void MainWindow::on_action_about_triggered()
{
    QMessageBox::information(this,tr("提示"),tr("本程序由南邮通达STITP组设计"),QMessageBox::Ok);
}


