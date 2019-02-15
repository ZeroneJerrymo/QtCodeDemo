#include "zo_itemwidget.h"

#include <QLabel>

Zo_ItemWidget::Zo_ItemWidget(QWidget *parent)
{
    hLayout = new QHBoxLayout();
    hLayout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(hLayout);

}

void Zo_ItemWidget::setWindowAlignment(Zo_ItemWidget::WIDGETTYPE type, ZO_Alignment Alignment)
{
    if(WIDGETTYPE == WIDGET_Label)
    {
        m_itemwgt = new QLabel(this);
        if(Alignment ==  ZO_Center)
        {
            hLayout->setAlignment(widget, Qt::AlignCenter);
        }
        hLayout->addWidget( m_itemwgt);
    }
}

void Zo_ItemWidget::itemWidgetDataClear()
{
    m_itemwgt->clear();
}
