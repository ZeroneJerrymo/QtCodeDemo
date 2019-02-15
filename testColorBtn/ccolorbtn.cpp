#include "ccolorbtn.h"

#include <QPainter>

CColorBtn::CColorBtn(QWidget *parent) : QPushButton(parent)
{

}

void CColorBtn::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QBrush pBrush;
    pBrush.setColor(QColor(255,255,255));
    pBrush.
    painter.setBrush(pBrush);

}
