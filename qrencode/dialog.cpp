#include "dialog.h"
#include "ui_dialog.h"
#include "qr/qrencode.h"
#include "qrwidget.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    //QRcode *qr=QRcode_encodeString("my string", 1, QR_ECLEVEL_L, QR_MODE_8,0);
    ui->lineEdit->setText(ui->widget->getString());
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    QString str = ui->lineEdit->text();
    if(str != ""){
        ui->widget->setString(str);
    }
}

void Dialog::on_pushButton_2_clicked()
{
    uint32_t size = ui->widget->getQRWidth();
    QString pathname = ui->widget->getString();
    pathname += ".png";
    ui->widget->saveImage(pathname, size*10);
}
