#include "cborderwidget.h"
#include <QLayout>
#include <QPainter>
CBorderWidget::CBorderWidget(QWidget *parent) : QWidget(parent)
  ,bBorder(true)
{
   setWindowFlags(Qt::FramelessWindowHint|Qt::WindowMinimizeButtonHint);

}

void CBorderWidget::paintEvent(QPaintEvent *event)
{
    if(bBorder)
    {
          this->layout()->setContentsMargins(2,2,2,2);

        QPainter painter(this);
        QPen pen;
        pen.setWidth(5);
        pen.setColor(Qt::black);
        painter.setPen(pen);
        painter.drawRect(this->rect());
    }

}
