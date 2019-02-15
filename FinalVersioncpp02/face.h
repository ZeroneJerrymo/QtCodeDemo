#ifndef FACE_H
#define FACE_H

#include <QWidget>
#include <QDialog>
#include "ui_face.h"
#include <QString>
#include <QCloseEvent>

namespace Ui {
class Face;
}

class FFace : public QDialog
{
    Q_OBJECT
public:
    FFace(QWidget *parent = 0);
    ~FFace();
    QString getPth();

private:
    Ui::Face *ui;
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
