#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPainter>
#include <QTimer>
#include <QTime>

namespace Ui {
class Dialog2;
}

class Dialog2 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog2(QWidget *parent = 0);
    ~Dialog2();
private:
    Ui::Dialog2 *ui;
    QImage img;
    QTimer *Timer;
    QString name[5];
    bool pflag;
public slots:
    void changPflag();
public:
    void paintEvent(QPaintEvent *);

};

#endif // DIALOG_H
