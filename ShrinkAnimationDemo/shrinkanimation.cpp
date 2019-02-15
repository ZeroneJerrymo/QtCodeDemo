#include "shrinkanimation.h"

//这里是主界面
 ShrinkAnimation::ShrinkAnimation(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this); initControl();
}
 ShrinkAnimation::~ShrinkAnimation()
 {

 }
 void ShrinkAnimation::initControl()
 {
     ui.titleWidget->setFixedWidth(this->width());
     //这里就是那黄色区域
     StatusWidget* pWidget = new StatusWidget(ui.upWidget);
     pWidget->setFixedSize(this->width(), 48);
     pWidget->move(0, ui.titleWidget->height()); //点击效果按钮，进行效果展示
     connect(ui.pushButton, &QPushButton::clicked, [this, pWidget]()
     { //fixSizeHeight是自定义属性
         QPropertyAnimation *animation = new QPropertyAnimation(ui.upWidget, "fixSizeHeight");

         animation->setDuration(500);
         animation->setEasingCurve(QEasingCurve::InQuad); //高于最小高度，代表处于展开状态
         if (ui.upWidget->height() > 32)
         {
             animation->setEndValue(32);
         } //否做就是收缩状态
         else {
             animation->setEndValue(pWidget->height() + 32);
         }
         animation->start(QAbstractAnimation::DeleteWhenStopped);
     });
 } //这里主要是设置效果按钮的位置
 void ShrinkAnimation::resizeEvent(QResizeEvent *)
 {
     ui.titleWidget->setFixedWidth(this->width());
     ui.pushButton->move(this->width() - ui.pushButton->width(), 0);
 }
