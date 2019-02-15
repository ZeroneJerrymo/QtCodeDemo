#ifndef WYFACE_H
#define WYFACE_H

#include <QWidget>
#include <QDialog>
#include "ui_wyface.h"
#include <QString>
#include <QCloseEvent>

namespace Ui {
class WyFace;
}

class WyFace : public QDialog
{
    Q_OBJECT
public:
    WyFace(QWidget *parent = 0);
    ~WyFace();
    QString getPth();

private:
    Ui::WyFace *ui;
    QString pth;
private slots:
    void clickFace();
    void on_toolButton_1_clicked();
    void on_toolButton_2_clicked();
    void on_toolButton_3_clicked();
    void on_toolButton_4_clicked();
    void on_toolButton_5_clicked();
    void on_toolButton_6_clicked();
    void on_toolButton_7_clicked();
    void on_toolButton_8_clicked();
    void on_toolButton_9_clicked();
};
#endif // FACE_H
