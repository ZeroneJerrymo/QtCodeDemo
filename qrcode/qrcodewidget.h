#ifndef QRCODE_H
#define QRCODE_H

#include <QWidget>
#include <QTextCodec>

namespace Ui {
class QRCode;
}

class QRCodeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QRCodeWidget(QWidget *parent = 0);
    ~QRCodeWidget();

private slots:
    void on_pushButton_clicked();

    void on_radioButton_toggled(bool checked);

private:
    Ui::QRCode *ui;
    char outfile[128];
    double xRate =0.24;
    double yRate =0.24;
    QString logoFileName;
};

#endif // QRCODE_H
