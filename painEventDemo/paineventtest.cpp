#include "paineventtest.h"

#include <QPainter>
#include <QPushButton>

painEventTest::painEventTest(QWidget *parent) : QWidget(parent)
{
    this->resize(300,300);
    QPushButton* pb_ck= new QPushButton("点击",this);
    connect(pb_ck, SIGNAL(clicked()), this, SLOT(slot_setbackcolor()));
    pcolor =QColor( "#c0cadd");
    QPixmap pixmap ;
    pixmap.fill(pcolor);
   pb_ck ->setBackgroundRole(QPalette::Dark);

}

void painEventTest::paintEvent(QPaintEvent *event)
{
  // QColor("#c0cadd");
   QPainter painter(this);
   painter.setBrush(pcolor);
    //   painter.drawPixmap(this->rect(),pixmap);
       painter.drawRect(this->rect());
      // painter.drawLine()
       rgb(233,233,235);

}

void painEventTest::slot_setbackcolor()
{
     pcolor =QColor( "#f5f6f9");
     update();
}
