#include "chatbubble.h"
#include <QDebug>
#include "myapp.h"

//namespace BubbleWidget
//{

//};
BubbleList::BubbleList(QWidget *parent) :
    QWidget(parent)
{
    initVars();
    initWgts();
    initStgs();
    initConns();
}

BubbleList::~BubbleList()
{
    d->clear();
}

/*!
  private utility functions
*/
void BubbleList::initVars()
{
}

void BubbleList::initWgts()
{
    mainLayout = new QHBoxLayout(this);
    scrollbar = new QScrollBar(this);
    d = new BubbleListPrivate(this);
    this->setMinimumWidth(300);

    mainLayout->addWidget(d);
    mainLayout->addWidget(scrollbar);
    setLayout(mainLayout);
}

void BubbleList::initStgs()
{
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    scrollbar->setRange(0,0);
    scrollbar->hide();
}

void BubbleList::initConns()
{
    connect(scrollbar,SIGNAL(valueChanged(int)),d,SLOT(setCurrentIndex(int)));
    connect(d,SIGNAL(sig_setMaximum(int)),this,SLOT(setMaximum(int)));
    connect(d,SIGNAL(sig_setCurrentIndex(int)),scrollbar,SLOT(setValue(int)));
    connect(d,SIGNAL(sig_itemClicked(QString)),this,SIGNAL(sig_itemClicked(QString)));
}

void BubbleList::calcGeo()
{

}

/*!
  private slot functions
*/
void BubbleList::setMaximum(int max)
{
    if(max == 0)
    {
        scrollbar->hide();
    }else{
        scrollbar->show();
    }
    scrollbar->setRange(0,max);
}

/*!
  protected functions of PYFlashList
*/
void BubbleList::resizeEvent(QResizeEvent *)
{

}

/*!
  public interfaces of PYFlashList
*/
void BubbleList::addItem(const QString &str, const int &orientation)
{
    d->addItem(str, orientation);
}

void BubbleList::clear()
{
    d->clear();
}

void BubbleList::render()
{
    d->render();
}

/*************************************/
/*!   BubbleListPrivate section    !*/
/*************************************/
BubbleListPrivate::BubbleListPrivate(QWidget* parent):QWidget(parent)
{
    initVars();
    initSettings();
}
/*!
  private utility functions of BubbleListPrivate
 */
void BubbleListPrivate::initVars()
{
    m_currIndex = 0;
    m_VisibleItemCnt = 0;
    m_ItemCounter = 0;

    m_bAllJobsDone = false;

    m_RotateTimer = new QTimer(this);
    m_RotateTimer->setInterval(UPDATE_TIMER_INTERVAL);
    connect(m_RotateTimer,SIGNAL(timeout()),this,SLOT(DoRotation()));

    m_ItemCountTimer = new QTimer(this);
    m_ItemCountTimer->setInterval(ITEM_COUNTER_TIMER_INTERVAL);
    connect(m_ItemCountTimer,SIGNAL(timeout()),this,SLOT(UpdateItemCount()));
}

void BubbleListPrivate::initSettings()
{
    setMouseTracking(this);
}

void BubbleListPrivate::calcGeo()
{
    m_VisibleItemCnt = height() / (ITEM_HEIGHT + ITEM_SPACE + 10) + 1;
    int InvisibleItemCnt = m_IIVec.count() - m_VisibleItemCnt;

    if(InvisibleItemCnt >= 0)
    {
        emit sig_setMaximum(InvisibleItemCnt);
    }
}

void BubbleListPrivate::makeupJobs()
{
    int Guard = 0;
    for(int index = m_currIndex; index < m_IIVec.count() ;index++)
    {
        if(Guard++ > m_VisibleItemCnt)
        {
            break;
        }

        if(!m_IIVec.at(index).jobDone())
        {
            if(!m_RotateTimer->isActive())
            {
                m_RotateTimer->start();
                m_ItemCountTimer->start();
                break ;
            }
        }
    }

    // reset items which is before the current index 's angle
    for(int index = 0;index < m_currIndex ; index++)
    {
        //            if(!m_IIVec.at(index).inWrongPosition())
        //            {
        m_IIVec[index].resetAngle();
        //            }else{
        //                break;
        //            }
    }

    // reset items which is after the visible item's angle
    if((m_currIndex + m_VisibleItemCnt) < m_IIVec.count())
    {
        for(int index  = (m_currIndex + m_VisibleItemCnt);index < m_IIVec.count();index++)
        {
            //                if(m_IIVec.at(index).inWrongPosition())
            //                {
            m_IIVec[index].resetAngle();
            //                }else{
            //                    break;
            //                }
        }
    }
}

void BubbleListPrivate::wheelUp()
{
    if(--m_currIndex < 0)
    {
        m_currIndex = 0;
    }
    update();
    emit sig_setCurrentIndex(m_currIndex);
    makeupJobs();
}

void BubbleListPrivate::wheelDown()
{
    if(++m_currIndex + m_VisibleItemCnt > m_IIVec.count())
    {
        m_currIndex = m_IIVec.count() - m_VisibleItemCnt;
    }

    // 优化处理，在没添加的时候下滑动会崩溃
    if (m_currIndex < 0)
    {
        m_currIndex = 0;
    }

    update();
    emit sig_setCurrentIndex(m_currIndex);
    makeupJobs();
}

/*!
  protected functions of BubbleListPrivate
*/
void BubbleListPrivate::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::HighQualityAntialiasing|QPainter::Antialiasing);
    drawBg(&painter);
    drawItems(&painter);
    //        drawHoverRect(&painter);
}

void BubbleListPrivate::mouseMoveEvent(QMouseEvent *e)
{
    if(!m_bAllJobsDone)
    {
        return ;
    }

    int ItemCnt = e->pos().y()/ITEM_HEIGHT;
    if(m_currIndex + ItemCnt < m_IIVec.count())
    {
        QPointF topLeft(0,ItemCnt*ITEM_HEIGHT + ItemCnt*ITEM_SPACE);
        QPointF bottomRight(width(),(ItemCnt+1)*ITEM_HEIGHT + ItemCnt*ITEM_SPACE);
        m_HoverRect = QRectF(topLeft,bottomRight);
        m_strHoverText = m_IIVec.at(m_currIndex+ItemCnt).getText();
        update();
    }
}

void BubbleListPrivate::mousePressEvent(QMouseEvent *e)
{
    if(!m_bAllJobsDone)
    {
        return ;
    }
    int ItemCnt = e->pos().y() / ITEM_HEIGHT;
    if(m_currIndex + ItemCnt < m_IIVec.count())
    {
        m_selectedIndex = m_currIndex + ItemCnt;
        QString strText = m_IIVec.at(m_selectedIndex).getText();
        emit sig_itemClicked(strText);
    }
    update();
}

void BubbleListPrivate::resizeEvent(QResizeEvent *)
{
    calcGeo();
    makeupJobs();
}

void BubbleListPrivate::leaveEvent(QEvent *)
{
    m_HoverRect = QRectF();
    update();
}
void BubbleListPrivate::showEvent(QShowEvent *)
{
    calcGeo();
}

void BubbleListPrivate::wheelEvent(QWheelEvent *e)
{
    if(e->delta() > 0)
    {
        wheelUp();
    }else{
        wheelDown();
    }
}

/*!
  painting function of BubbleListPrivate
 */
void BubbleListPrivate::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient BgGradient(QPoint(0,0),QPoint(0,height()));
    BgGradient.setColorAt(0.0,BG_START_COLOR);
    BgGradient.setColorAt(1.0,BG_END_COLOR);
    //    painter->setBrush(BgGradient);
    painter->setBrush(QColor("#FFFFFF"));
    painter->setPen(QColor("#C6C6C6"));
    painter->drawRect(rect());
    if (MyApp::m_bDrawBg)
        painter->drawPixmap(rect(), QPixmap(":/images/psu.jpg"));
    painter->restore();
}

void BubbleListPrivate::drawItems(QPainter *painter)
{
    if(m_IIVec.count() == 0)
    {
        return ;
    }

    // 绘制item区域
    painter->save();

    int Guard = 0;
    qreal nItemY = 0;
    int nWidth = this->width();
    nWidth = (0 == nWidth % 2) ? nWidth : nWidth + 1;

    for(int nIndex = m_currIndex;nIndex < m_IIVec.count();nIndex++)
    {
        if(Guard++ > m_VisibleItemCnt)
        {
            break ;
        }

        QPointF topLeft(0,nItemY);
        QPointF bottomRight(nWidth, nItemY + ITEM_HEIGHT + ITEM_SPACE);
        QRectF ItemRect(topLeft,bottomRight);

        painter->save();
        QTransform t;
        t.translate(ItemRect.center().x(),ItemRect.center().y());
        //            t.rotate(m_IIVec.at(index).getAngle(),Qt::XAxis);
        t.scale(m_IIVec.at(nIndex).getZoomingFactor(),m_IIVec.at(nIndex).getZoomingFactor());
        painter->setTransform(t);

        QPointF rectTopLeft;
        QPointF rectBottomRight;
        QRectF textRect(rectTopLeft,rectBottomRight);
        QLinearGradient itemGradient(textRect.topLeft(),textRect.bottomLeft());

        QFont font("幼圆", 10);
        painter->setFont(font);
        QString strText = m_IIVec.at(nIndex).getText();
        strText.append(QString(" [ %1 ]").arg(nIndex));
        int orientation = m_IIVec.at(nIndex).getOrientation();

        // 计算文字的宽度
        QFontMetrics fm(font);
        QPainterPath path;
        int pixelsWide = fm.width(strText);
        int pixelsHigh = fm.height();

        pixelsWide = pixelsWide < (nWidth * 2 / 3) ? pixelsWide: (nWidth * 2 / 3);
        pixelsHigh = pixelsWide < (nWidth * 2 / 3) ? ITEM_HEIGHT : (((pixelsWide / (nWidth / 2)) + 1) * ITEM_HEIGHT / 2);

        if (Right == orientation)
        {
            itemGradient.setColorAt(0.0,ITEM_START_COLOR);
            itemGradient.setColorAt(1.0,ITEM_END_COLOR);

            painter->save();
            painter->setPen(Qt::red);
            // 绘制边框
            painter->drawRoundedRect(nWidth / 2 - 55, -ITEM_HEIGHT / 2, 50, 50, 2, 2);
            // 绘制头像
            painter->drawPixmap(nWidth / 2 - 54, -ITEM_HEIGHT / 2 + 1, 48, 48, QPixmap(":/images/zgl.png"));
            painter->restore();


            // 计算右边的宽度x
            int nX = (nWidth / 2) - 85 - pixelsWide;
            if (nX < 0) {
                nX = -pixelsWide - 85 + nWidth / 2;
            }
            // 计算气泡框
            painter->save();
            textRect = QRectF(nX, -ITEM_HEIGHT / 2, pixelsWide + 20, pixelsHigh);

#if 1
            // 计算气泡右边的三角
            path.addRoundedRect(textRect, 10, 10);
            path.moveTo(nWidth / 2 - 65, -ITEM_HEIGHT / 2 + 10);
            path.lineTo(nWidth / 2 - 55, -ITEM_HEIGHT / 2 + 16);
            path.lineTo(nWidth / 2 - 65, -ITEM_HEIGHT / 2 + 19);
            //            painter->fillPath(path, itemGradient);
            painter->fillPath(path, QColor("#3FA7EC"));
#else
            painter->drawPixmap(nX + 10, -ITEM_HEIGHT / 2, pixelsWide, pixelsHigh, QPixmap(":/images/bubble_out_press.9.png"));
#endif
            painter->restore();

            painter->setPen(Qt::white);
            // 重新调整文字区域
            textRect = QRectF(nX + 10, -ITEM_HEIGHT / 2, pixelsWide, pixelsHigh);
        }
        else {
            itemGradient.setColorAt(0.0, ITEM_START_COLOR_A);
            itemGradient.setColorAt(1.0, ITEM_END_COLOR_A);

            // 绘制气泡区域
            painter->save();
            textRect = QRectF(-nWidth / 2 + 65, -ITEM_HEIGHT / 2, pixelsWide + 20, pixelsHigh);
            // 左边三角
            path.addRoundedRect(textRect, 5, 5);
            path.moveTo(-nWidth / 2 + 65, -ITEM_HEIGHT / 2 + 10 );
            path.lineTo(-nWidth / 2 + 55, -ITEM_HEIGHT / 2 + 16);
            path.lineTo(-nWidth / 2 + 65, -ITEM_HEIGHT / 2 + 19);
            painter->fillPath(path, QColor("#E2E3E1"));
            painter->restore();

            // 绘制头像
            painter->save();
            painter->setPen(Qt::red);
            painter->drawRoundedRect(-nWidth / 2 + 5, -ITEM_HEIGHT / 2, 50, 50, 2, 2);
            painter->drawPixmap(-nWidth/2 + 6, -ITEM_HEIGHT / 2 + 1, 48, 48, QPixmap(":/images/head-48.png"));
            painter->restore();

            painter->setPen(QColor("#666666"));

            // 绘制文字区域
            textRect = QRectF(-nWidth / 2 + 65 + 10, -ITEM_HEIGHT / 2, pixelsWide, pixelsHigh);
        }

        painter->drawText(textRect, strText, Qt::AlignVCenter |Qt::AlignLeft);
        painter->restore();

        /// increment nItemY
        nItemY += ITEM_HEIGHT + ITEM_SPACE;
    }

    painter->restore();
}

void BubbleListPrivate::drawHoverRect(QPainter *painter)
{
    if(m_HoverRect.isEmpty() && !m_bAllJobsDone)
    {
        return ;
    }

    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient HoverGradient(m_HoverRect.topLeft(),m_HoverRect.bottomLeft());
    HoverGradient.setColorAt(0.0,HOVER_START_COLOR);
    HoverGradient.setColorAt(1.0,HOVER_END_COLOR);
    painter->setBrush(HoverGradient);
    painter->drawRoundedRect(m_HoverRect,RECT_RADIUS,RECT_RADIUS);

    QFont BoldFont;
    BoldFont.setBold(true);
    painter->setFont(BoldFont);

    painter->setPen(HOVER_TEXT_COLOR);
    painter->drawText(m_HoverRect, m_strHoverText/*, Qt::AlignLeft|Qt::AlignVCenter*/);
    painter->restore();
}

/*!
  private slot functions of BubbleListPrivate
*/
void BubbleListPrivate::DoRotation()
{
    int Guard = 0;
    bool bHasJobUndone = false;
    m_bAllJobsDone = false;
    m_HoverRect = QRectF();

    for(int index = m_currIndex;index < m_IIVec.count()/* && Guard < m_ItemCounter*/ ;index++ )
    {
        if(!m_IIVec.at(index).jobDone())
        {
            bHasJobUndone = true;
            //                m_IIVec[index].updateAngle();
            m_IIVec[index].updateZoomingFactor();
        }

        if(Guard++ > m_VisibleItemCnt)
        {
            break;
        }
        update();
    }


    if(!bHasJobUndone)
    {
        m_RotateTimer->stop();
        m_bAllJobsDone = true;
    }

}

void BubbleListPrivate::UpdateItemCount()
{
    if(++m_ItemCounter > m_VisibleItemCnt)
    {
        if(m_ItemCountTimer->isActive())
        {
            m_ItemCountTimer->stop();
            m_ItemCounter = 0;
        }
    }
}

/*!
  public interfaces of BubbleListPrivate
 */
void BubbleListPrivate::addItem(const QString &str, const int &orientation)
{
    ItemInfo ID(str, orientation);
    m_IIVec.push_back(ID);

    //    if(m_RotateTimer->isActive())
    //    {
    //        m_RotateTimer->stop();
    //    }
    //    m_RotateTimer->start();

    wheelDown();
}

void BubbleListPrivate::clear()
{
    m_IIVec.clear();
    m_currIndex = 0;
    m_VisibleItemCnt = 0;
    m_ItemCounter = 0;

    m_bAllJobsDone = false;

    update();
}

void BubbleListPrivate::render()
{
    update();
}

/*!
  public slot functions of BubbleListPrivate
*/
void BubbleListPrivate::setCurrentIndex(int curIndex)
{
    if(curIndex == m_currIndex)
    {
        return ;
    }

    //
    m_currIndex = curIndex;

    m_VisibleItemCnt = height()/ITEM_HEIGHT + 1;
    int Guard = 0;
    for(int index = m_currIndex ;index < m_IIVec.count();index++)
    {
        //            m_IIVec[index].resetAngle();
        m_IIVec[index].resetZoomingFactor();
        if(Guard++ > m_VisibleItemCnt)
        {
            break ;
        }
    }
    m_RotateTimer->start();
    m_ItemCountTimer->start();
}
