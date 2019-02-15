#include "zo_treewidgetonceclickopen.h"

#include <QMouseEvent>

Zo_treeWidgetOnceClickOpen::Zo_treeWidgetOnceClickOpen(QWidget *parent) : QTreeWidget(parent)
{
    connect(this, SIGNAL( itemClicked(QTreeWidgetItem* , int )), this, SLOT(slot_expendItem(QTreeWidgetItem* , int )));

}

void Zo_treeWidgetOnceClickOpen::mouseDoubleClickEvent(QMouseEvent *event)
{
   return;
}

void Zo_treeWidgetOnceClickOpen::slot_expendItem(QTreeWidgetItem *pItem, int colum)
{
        pItem->setExpanded(!(pItem->isExpanded()));

}
