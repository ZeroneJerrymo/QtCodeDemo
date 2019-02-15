#include "chnsystitlewidget.h"
#include "chnsystitlebuttongroup.h"
#include <QHBoxLayout>
#include <QMouseEvent>
ChnsysTitleWidget::ChnsysTitleWidget(QWidget *parent) : QWidget(parent)
  , m_isPressed (false)
{
    this->setObjectName("dialogTitle");

    m_titleIcon = new QLabel(this);
    m_titleLabel = new  QLabel(this);
    m_titlebtnGroup = new ChnsysTitleButtonGroup(this);
   QHBoxLayout* hLayout = new QHBoxLayout;
   hLayout->addWidget(m_titleIcon);
   hLayout->addWidget(m_titleLabel);
   hLayout->addStretch();

   hLayout->addWidget(m_titlebtnGroup);
   this->setLayout(hLayout);
}

void ChnsysTitleWidget::setTitleText(QString titleText)
{
    m_titleLabel->setText(titleText);
}

void ChnsysTitleWidget::setTitleIcon(QString pIconPath)
{
    QPixmap pixmap;
    pixmap.load(pIconPath);
    pixmap.scaled(m_titleIcon->size(), Qt::KeepAspectRatio);
    m_titleIcon->setPixmap(pixmap);
}

void ChnsysTitleWidget::mousePressEvent(QMouseEvent *event)
{
    //当鼠标左键点击时.

        m_isPressed = true;
        m_startMovePos = event->globalPos();
        return QWidget::mousePressEvent(event);
}

void ChnsysTitleWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_isPressed = false;
      return QWidget::mouseReleaseEvent(event);
}

void ChnsysTitleWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isPressed)
        {
        //移动的位置
            QPoint movePoint = event->globalPos() - m_startMovePos;

            if(parentWidget())
            {
                QPoint widgetPos = this->parentWidget()->pos();
                m_startMovePos = event->globalPos();
                parentWidget()->move(widgetPos.x() + movePoint.x(), widgetPos.y() + movePoint.y());
            }
        }

        return QWidget::mouseMoveEvent(event);
}
