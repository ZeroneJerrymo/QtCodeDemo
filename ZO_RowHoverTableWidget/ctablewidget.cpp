#include "ctablewidget.h"
#include <QMessageBox>
#include <QPoint>
TableWidget::TableWidget(QWidget *parent) :    QWidget(parent)
{
    setGeometry(100,100,600,300);
    defaultBkColor = QColor(255,255,255);   //默认背景色
    previousColorRow = -1;
    tableWidget = new QTableWidget(this);
    tableWidget->setRowCount(10);   //设置行数为10
    tableWidget->setColumnCount(5); //设置列数为5
    tableWidget->setGeometry(10,10,580,280);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);   //设置整行选择
    tableWidget->setMouseTracking(true);    //开启捕获鼠标功能
    tableWidget->setStyleSheet("QTableWidget{	font: 16pt \"楷体\"; border:0 px;selection-background-color:rgb(241, 241, 241); \
                                                        item-border-bottom:1px solid #EEF1F7 ; }"
                  );  //设置选中行颜色
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);    //禁止编辑表格
    for (int i=0; i<10; i++)
        for (int j=0; j<5;j++)
        {
            QTableWidgetItem *item = new QTableWidgetItem(QIcon(":/btn1_bright"), "Jan");
            tableWidget->setItem(i,j,item);
        }
    connect(tableWidget,SIGNAL(cellEntered(int,int)),this,SLOT(mycellEntered(int,int)));
}
void TableWidget::mycellEntered(int row, int column)
{
    QTableWidgetItem *item = 0;     //还原上一行的颜色
    item = tableWidget->item(previousColorRow, 0);
    if (item != 0)
    {
        this->setRowColor(previousColorRow, defaultBkColor);
    }
    //设置当前行的颜色
    item = tableWidget->item(row, column);
    if (item != 0 && !item->isSelected() && !item->text().isEmpty())
    {        this->setRowColor(row, QColor(193,210,240));    }
    //设置行的索引
    previousColorRow = row;
}
//设置某一行的颜色

void TableWidget::setRowColor(int row, QColor color)
{
    for (int col=0; col<tableWidget->columnCount(); col++)
    {
        QTableWidgetItem *item = tableWidget->item(row, col);
        item->setBackgroundColor(color);
    }
}
