#include <QPicture>
#include "qimageviewer.h"
#include "qrcodewidget.h"
#include "ui_qrcode.h"
#include "qrencode.h"
#include "qrenc.c"
#include <QFileDialog>
//#include <QDebug>

#pragma comment(lib,"libpng16.lib")
#pragma comment(lib,"zlib.lib")

QRCodeWidget::QRCodeWidget(QWidget *parent) :
    QWidget(parent, Qt::Dialog),
    ui(new Ui::QRCode)
{
//    QTextCodec *codec = QTextCodec::codecForName("utf8");
//    QTextCodec::setCodecForLocale(codec);
    ui->setupUi(this);
    strcpy(outfile , "output.png");

    QSize logoSize;
    logoSize.setWidth(ui->imageWidget->width()*xRate);
    logoSize.setHeight(ui->imageWidget->height()*yRate);
    ui->logowidget->resize(logoSize);
    QPoint topleft;
    topleft.setX(ui->imageWidget->width()*(1-xRate)/2);
    topleft.setY(ui->imageWidget->height()*(1-yRate)/2);
    ui->logowidget->move(topleft);
    ui->logowidget->hide();
    ui->logowidget->setWindowFlags(Qt::WindowStaysOnTopHint);
    ui->logowidget->show();

    setWindowTitle(tr("QrCode"));
}

QRCodeWidget::~QRCodeWidget()
{
    delete ui;
}

void QRCodeWidget::on_pushButton_clicked()
{

    QString info = ui->lineEdit->text();
    if (info.isEmpty()) {
        return;
    }

    margin = 1;
    ::size = 7;
    version = 2;

    qrencode((unsigned char *)info.toStdString().data(), info.length(), outfile);

    if (!(logoFileName.isNull())&&(logoFileName != ""))
    {
        QImage resultImage;
        QImage qrCodeImage(outfile);
        QSize resultSize;
        resultSize.setWidth(qrCodeImage.width());
        resultSize.setHeight(qrCodeImage.height());
        resultImage = QImage(resultSize, QImage::Format_ARGB32_Premultiplied);

        QPainter painter(&resultImage);
        painter.setCompositionMode(QPainter::CompositionMode_Source);
        painter.fillRect(resultImage.rect(), Qt::transparent);
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

        QImage image = QImage();
        image.load(logoFileName);
        QSize logoSize;
        logoSize.setWidth(qrCodeImage.width()*xRate);
        logoSize.setHeight(qrCodeImage.height()*yRate);
        QImage newImage = image.scaled(logoSize,Qt::KeepAspectRatio,Qt::SmoothTransformation);
        QPoint logoPoint((qrCodeImage.width() - newImage.width()) / 2,
                         (qrCodeImage.height() - newImage.height()) / 2);
        painter.drawImage(logoPoint, newImage);

        painter.setCompositionMode(QPainter::CompositionMode_DestinationAtop);
        painter.drawImage(0, 0, qrCodeImage);
        painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
        painter.fillRect(resultImage.rect(), Qt::white);
        painter.end();

        resultImage.save(outfile);
//        ui->imageWidget->setPixmap(QPixmap::fromImage(resultImage));
    }
//    else
    ui->imageWidget->setPixmap(QPixmap(outfile));
}

void QRCodeWidget::on_radioButton_toggled(bool checked)
{
    if (checked)
    {
        logoFileName = QFileDialog::getOpenFileName(this, tr("Open Logo Image"));
        if (!logoFileName.isEmpty())
            ui->logowidget->setPixmap(QPixmap(logoFileName));
        else
            ui->radioButton->setChecked(false);
    }
    else
    {
        ui->logowidget->setPixmap(QPixmap());
        ui->imageWidget->update();
        logoFileName = "";
    }
}


