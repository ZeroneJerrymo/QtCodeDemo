#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->tableWidget, SIGNAL(cellEntered(int, int)), this, SLOT(slot_cellEntered(int, int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_cellEntered(int row, int column)
{
    QTableWidgetItem *item = ui->tableWidget->item(row, column);
    if (item != 0 && !item->isSelected())
    {
        for (int col = 0; col<ui->tableWidget->columnCount(); col++)
        {
            QTableWidgetItem *pitem = ui->tableWidget->item(row, col);
            pitem->setBackgroundColor(QColor(20,20,20));
        }
       // ui.tableWidget->setRowColor(row, QColor(10, 20, 20));
    }
}
