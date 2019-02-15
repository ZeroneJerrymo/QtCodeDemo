#ifndef CSETBACKGROUNDWGT_H
#define CSETBACKGROUNDWGT_H

#include <QDialog>
#include <QWidget>

namespace Ui {
class CSetBackGroundWgt;
}

class CSetBackGroundWgt : public QDialog
{
    Q_OBJECT

public:
    explicit CSetBackGroundWgt(QWidget *parent = 0);
    ~CSetBackGroundWgt();


    void setBackgroundColor(QColor);
private:
    Ui::CSetBackGroundWgt *ui;

    virtual void paintEvent(QPaintEvent*event);

    QColor m_color;
};

#endif // CSETBACKGROUNDWGT_H
