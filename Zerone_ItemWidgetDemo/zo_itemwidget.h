#ifndef ZO_ITEMWIDGET_H
#define ZO_ITEMWIDGET_H

#include <QHBoxLayout>
#include <QWidget>

class Zo_ItemWidget:public  QWidget
{
    Q_OBJECT
public:
    enum WIDGETTYPE{
        WIDGET_Label = 0,
        WIDGET_ComboBox,
        WIDGET_LineEdit,
    };
    enum ZO_Alignment{
        ZO_AlignLeft = 0,
        ZO_Center ,
        ZO_AlignRight,
    };
    Zo_ItemWidget(QWidget * parent = Q_NULLPTR);

    void setWindowAlignment(WIDGETTYPE type, ZO_Alignment Alignment = ZO_Center );
    void itemWidgetDataClear();
private:
    QHBoxLayout *hLayout;
    QWidget* m_itemwgt;
};

#endif // ZO_ITEMWIDGET_H
