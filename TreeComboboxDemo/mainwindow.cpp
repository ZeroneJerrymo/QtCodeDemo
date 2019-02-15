#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTreeWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    QTreeWidget * treeWidget = new QTreeWidget(this);
//    QTreeWidgetItem *rootItem = new QTreeWidgetItem(treeWidget, QStringList()<<"rootStringList");

//    ui-> comboBox->setModel(treeWidget->model());
//    ui->comboBox->setView(treeWidget);
    QMap<QString, QStringList>  mp_data;
    mp_data.insert("江苏高院", QStringList()<<"第一法院"<<"第二法院"<<"第三法院");
    mp_data.insert("江苏高院", QStringList()<<"第一法院"<<"第二法院"<<"第三法院");
    ui->comboBox->addTreeData(mp_data,true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
