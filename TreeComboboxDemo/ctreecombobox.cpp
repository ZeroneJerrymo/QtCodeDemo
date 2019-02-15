#include "ctreecombobox.h"

#include <QTreeWidget>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QEvent>
#include <QToolTip>
CTreeComboBox::CTreeComboBox(QWidget *parent):QComboBox(parent),m_curSetDlg(NULL)
{
    ConstructTree();
    // ConstructTable();表格下拉框
}

CTreeComboBox::~CTreeComboBox()
{

}

void CTreeComboBox::addTreeData(QMap<QString, QStringList> mp_data, bool b_CheckState)
{
    if(m_curSetDlg == NULL)
        return;
    QTreeWidget * ptreeWidget  = dynamic_cast< QTreeWidget *> (m_curSetDlg);
    QMap<QString, QStringList>::iterator iter;
    for (iter = mp_data.begin(); iter!= mp_data.end(); ++iter) {

        QTreeWidgetItem *rootItem = new QTreeWidgetItem(ptreeWidget,QStringList()<< iter.key());
        if(b_CheckState)
        {
            rootItem->setCheckState(0,Qt::Unchecked);
        }
        QStringList childList = iter.value();
        for(int i = 0; i < childList.count(); i++)
        {
            QTreeWidgetItem *pchildItem = new QTreeWidgetItem(rootItem,QStringList()<<childList.value(i));
            if(b_CheckState)
            {
                pchildItem->setCheckState(0,Qt::Unchecked);
            }
        }
    }
}

QWidget *CTreeComboBox::getCurrentWidget()
{
    return  m_curSetDlg;
}

void CTreeComboBox::ConstructTree()
{
    QTreeWidget * treeWidget = new QTreeWidget(this);
    treeWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    treeWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    treeWidget->setFocusPolicy(Qt::NoFocus);
    treeWidget->header()->setVisible(false);
    m_curSetDlg =  treeWidget;

    this->setItemDelegate(delege);
    QTreeWidgetItem * item = new QTreeWidgetItem;


    this->setModel(treeWidget->model());

    this->setView(treeWidget);

}
