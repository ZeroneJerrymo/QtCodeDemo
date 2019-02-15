#include "csetbackgroundwgt.h"
#include "csetbackgroundwgt.h"
#include "ui_csetbackgroundwgt.h"

#include <QPainter>

CSetBackGroundWgt::CSetBackGroundWgt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CSetBackGroundWgt)
{
    ui->setupUi(this);
    this->resize(400, 400);
    m_color =   QColor(255,255, 255);
}

CSetBackGroundWgt::~CSetBackGroundWgt()
{
    delete ui;
}

void CSetBackGroundWgt::setBackgroundColor(QColor pColor)
{
    m_color = pColor;
    update();
}

void CSetBackGroundWgt::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QBrush brush(m_color);

    painter.setBrush(brush);
    painter.drawRect(this->rect());
}
