#include "addpeople.h"
#include "ui_addpeople.h"
#include <QDebug>
#include <QMessageBox>

AddPeople::AddPeople(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPeople)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("人员添加"));

    connect(ui->TakeAPotoBtn,SIGNAL(clicked()),this,SLOT(on_TakeAPotoBtn_clicked()),Qt::UniqueConnection);
}

AddPeople::~AddPeople()
{
    delete ui;
}

void AddPeople::TrainingModel()
{
    //读取你的CSV文件路径.
    //string fn_csv = string(argv[1]);
    std::string fn_csv = "./Data/at.txt";

    // 2个容器来存放图像数据和对应的标签
    std::vector<cv::Mat> images;
    std::vector<int> labels;
    // 读取数据. 如果文件不合法就会出错
    // 输入的文件名已经有了.
    try
    {
        read_csv(fn_csv, images, labels);
    }
    catch (cv::Exception& e)
    {
        std::cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
        // 文件有问题，我们啥也做不了了，退出了
        return;
    }
    // 如果没有读取到足够图片，也退出.
    if (images.size() <= 1) {
        std::string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
        CV_Error(CV_StsError, error_message);
    }

    // 下面的几行代码仅仅是从你的数据集中移除最后一张图片
    //[gm:自然这里需要根据自己的需要修改，他这里简化了很多问题]
    cv::Mat testSample = images[images.size() - 1];
//    int testLabel = labels[labels.size() - 1];
    images.pop_back();
    labels.pop_back();
    // 下面几行创建了一个特征脸模型用于人脸识别，
    // 通过CSV文件读取的图像和标签训练它。
    // T这里是一个完整的PCA变换
    //如果你只想保留10个主成分，使用如下代码
    //      cv::createEigenFaceRecognizer(10);
    //
    // 如果你还希望使用置信度阈值来初始化，使用以下语句：
    //      cv::createEigenFaceRecognizer(10, 123.0);
    //
    // 如果你使用所有特征并且使用一个阈值，使用以下语句：
    cv::createEigenFaceRecognizer(0, 123.0);

    cv::Ptr<cv::FaceRecognizer> model = cv::createEigenFaceRecognizer();
    model->train(images, labels);
    model->save("MyFacePCAModel.xml");

/*    cv::Ptr<cv::FaceRecognizer> model1 = cv::createFisherFaceRecognizer();
    model1->train(images, labels);
    model1->save("MyFaceFisherModel.xml");*/


    // 下面对测试图像进行预测，predictedLabel是预测标签结果
//    int predictedLabel = model->predict(testSample);
//    int predictedLabel1 = model1->predict(testSample);
//    int predictedLabel2 = model2->predict(testSample);

    // 还有一种调用方式，可以获取结果同时得到阈值:
          int predictedLabel = -1;
          double confidence = 0.0;
          model->predict(testSample, predictedLabel, confidence);
          qDebug()<<"confidencePCA:"<<confidence;

}

cv::Mat AddPeople::norm_0_255(cv::InputArray _src)
{
      cv::Mat src = _src.getMat();
      // 创建和返回一个归一化后的图像矩阵:
      cv::Mat dst;
      switch (src.channels()) {
      case1:
          cv::normalize(_src, dst, 0, 255, cv::NORM_MINMAX, CV_8UC1);
          break;
      case3:
          cv::normalize(_src, dst, 0, 255, cv::NORM_MINMAX, CV_8UC3);
          break;
      default:
          src.copyTo(dst);
          break;
      }
      return dst;
}

void AddPeople::read_csv(const std::string& filename, std::vector<cv::Mat>& images, std::vector<int>& labels)
{
    char separator = ';';
    std::ifstream file(filename.c_str(), std::ifstream::in);
    if (!file) {
        QMessageBox::warning(NULL,tr("错误"),tr("read_csv文件打开失败"),QMessageBox::Ok);
        return;
    }
    std::string line, path, classlabel;
    while (std::getline(file, line)) {
        std::stringstream liness(line);
        std::getline(liness, path, separator);
        std::getline(liness, classlabel);
        if (!path.empty() && !classlabel.empty()) {
            images.push_back(cv::imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}

void AddPeople::disposePic()
{
    file.CreateFile(QString::number( MaxNumAboutPeople,10));
    QString sourceFilePath="addData\\";
    QString targetFilePath="Data\\"+QString::number(MaxNumAboutPeople,10);
    targetFilePath.append("\\");
    QString sourceFile;
    QString targetFile;
    for(int i=0;i<10;i++)
    {
        sourceFile.append(sourceFilePath+QString::number(i+1,10));
        sourceFile.append(".jpg");
        targetFile.append(targetFilePath);
        targetFile.append(QString::number(i,10));
        targetFile.append(".jpg");
        this->detectAndDisplay(sourceFile,targetFile);
        sourceFile.clear();
        targetFile.clear();
    }
}

void AddPeople::AddCSV()
{
    file.MakecsvFile();
}

void AddPeople::detectAndDisplay(QString source, QString target)
{
    std::string face_cascade_name = "haarcascade_frontalface_alt.xml";
    cv::CascadeClassifier face_cascade;   //定义人脸分类器

    cv::Mat frame = cv::imread(source.toStdString());
    if(!frame.data)
    {
        qDebug()<<source;
        QMessageBox::warning(this,tr("提示"),tr("frame读取失败"),QMessageBox::Ok);
        return;
    }
    if (!face_cascade.load(face_cascade_name))
    {
        QMessageBox::warning(this,tr("错误"),tr("haarcascade_frontalface_alt.xml加载失败"),QMessageBox::Ok);
        return;
    }
    std::vector<cv::Rect> faces;
    cv::Mat img_gray;

    cv::cvtColor(frame, img_gray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(img_gray, img_gray);

    face_cascade.detectMultiScale(img_gray, faces, 1.1, 3, CV_HAAR_DO_ROUGH_SEARCH, cv::Size(50, 50));

    for (int j = 0; j < (int)faces.size(); j++)
    {
        cv::Mat faceROI = frame(faces[j]);
        cv::Mat MyFace;
        cv::Mat gray_MyFace;
        if (faceROI.cols > 100)
        {
            cv::resize(faceROI, MyFace, cv::Size(92, 112));
            cv::cvtColor(MyFace, gray_MyFace, CV_BGR2GRAY);
            imwrite(target.toStdString(), gray_MyFace);
        }
    }
}

void AddPeople::on_TakeAPotoBtn_clicked()
{
    if(ui->NamelineEdit->text()==NULL)
    {
        QMessageBox::warning(this,tr("错误"),tr("请输入姓名"),QMessageBox::Ok);
    }
    else
    {
        ui->NamelineEdit->setEnabled(false);
        ui->TakeAPotoBtn->setEnabled(false);
        capture=new cv::VideoCapture(0);
        int i=0;
        while (i!=10)
        {
            char key = cv::waitKey(100);
            *capture >> frame;
            imshow("frame", frame);
            std::string filename = cv::format("AddData\\%d.jpg", i+1);

            switch (key)
            {
            case'p':
                i++;
                imwrite(filename, frame);
                imshow("photo", frame);
                cv::waitKey(500);
                cv::destroyWindow("photo");
                break;
            default:
                break;
            }
        }
        capture->release();
        cv::destroyWindow("frame");
        ui->NamelineEdit->setEnabled(true);
        ui->TakeAPotoBtn->setEnabled(true);
    }
    int i=file.GetMaxNum("Data//people.txt");
    //qDebug()<<i<<endl;
    QString text=QString::number(i,10)+" "+ui->NamelineEdit->text();
    file.AddPeople("Data//people.txt",text);
    MaxNumAboutPeople=i;

}


