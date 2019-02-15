#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "glabel.h"

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    GLabel *label[6];
    //QLabel *people;
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
