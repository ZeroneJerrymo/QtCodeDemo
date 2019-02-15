#include "zo_rowhovertablewidget.h"

#include <QEvent>
#include <QMouseEvent>
#include <QStandardItemModel>

Zo_RowHoverTableWidget::Zo_RowHoverTableWidget(QWidget *parent) : QTableWidget(parent)
{
    this->setMouseTracking(true);//设置可捕获鼠标移动事件，很重要
    lastRowBkColor = QColor(0x00,0xff,0x00,0x00);//透明颜色

    previousColorRow = -1;
    m_hoverColor  = QColor(200,255, 255);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);   //设置整行选择
    //this->setStyleSheet("selection-background-color:rgba(0,0,0,50)");  //设置选中行颜色
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);    //禁止编辑表格
    connect(this,SIGNAL(cellEntered(int,int)),this,SLOT(m_cellEntered(int,int)));
}

void Zo_RowHoverTableWidget::setHoverColor(QColor color)
{
    m_hoverColor = color;
}

void Zo_RowHoverTableWidget::leaveEvent(QEvent *event)
{
    QTableWidgetItem *item = 0;

    //还原上一行的颜色
    item = this->item(previousColorRow, 0);
    if (item != 0)
    {
        this->setRowColor(previousColorRow, lastRowBkColor);
    }
}

void Zo_RowHoverTableWidget::setRowColor(int row, QColor color)
{
    for (int col=0; col<this->columnCount(); col++)
    {
        QTableWidgetItem *item = this->item(row, col);
        item->setBackgroundColor(color);
    }
}


void Zo_RowHoverTableWidget::m_cellEntered(int row, int column)
{
    QTableWidgetItem *pitem = 0;

    //还原上一行的颜色
    pitem = this->item(previousColorRow, 0);
    if (pitem != 0)
    {
        this->setRowColor(previousColorRow, lastRowBkColor);
    }

    //设置当前行的颜色
    pitem = this->item(row, column);
    if (pitem != 0 && !pitem->isSelected())
    {
        this->setRowColor(row, QColor(10,20,20));
    }

    //设置行的索引
    previousColorRow = row;
}

Zo_RowHoverTableView::Zo_RowHoverTableView(QWidget *parent)
{

  //  Zo_RowHoverTableModel table_model;
    setMouseTracking(true);
  //  this->setModel(&table_model);
    QStandardItemModel* model = new QStandardItemModel(this);
    model->setItem(0, 0, new QStandardItem("张三"));
    model->setItem(0, 1, new QStandardItem("3"));
    model->setItem(0, 2, new QStandardItem("男"));

}

void Zo_RowHoverTableView::mouseMoveEvent ( QMouseEvent * event)
{
        int row = indexAt(event->pos()).row();
        updateRow(row);
}

void Zo_RowHoverTableView::leaveEvent ( QEvent * event )
{
        table_model->setHoverRow(-1);
    int column_count= model()->columnCount();
        for (int i = column_count- 1; i >= 0; i--)
        {
                update(model()->index(current_row, i));
        }
        current_row = -1;
}
void Zo_RowHoverTableView::updateRow(int row)
{
        if (row == current_row)
                return;

        table_model->setHoverRow(row);
   int column_count= model()->columnCount();
        for (int i = column_count- 1; i >= 0; i--)
        {
                update(model()->index(current_row, i));
                update(model()->index(row, i));
        }
       // table_model->showToolTip(row);  //自定义方法用来进行QToolTip的显示
        current_row = row;
}

Zo_RowHoverTableModel::Zo_RowHoverTableModel(QObject *pobject)
{

}

void Zo_RowHoverTableModel::setHoverRow(int hover_row)
{
        this->hover_row = hover_row;
}

QVariant Zo_RowHoverTableModel::data(const QModelIndex &index, int role) const
{
        if (!index.isValid())
                return QVariant();

        int row = index.row();  //行号
//        if (row < 0 || row >= list_file.size())
//                return QVariant();

//        int column = index.column();
//        QString name = list_file.at(row);
        switch (role) {
        case Qt::BackgroundColorRole:{
                        if (row == hover_row) {
                                return QColor(180, 200, 220);
                        }
                }
        case Qt::DecorationRole: {  //图标
                        //...
                }
        case Qt::DisplayRole: {  //文本
                        //...
                }
        case Qt::TextAlignmentRole: {  //对齐方式
                        //...
                }
        default:
                return QVariant();
        }

        return QVariant();
}
