#include "mainwindow.h"
#include <QApplication>
#include <QHeaderView>
#include "ctablewidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    TableWidget table;


//    tabl0e.setColumnCount(4);
//    table.setColumnWidth(,20);
//    table.setColumnWidth(1,20);
//    table.setColumnWidth(2,20);
//    table.setColumnWidth(3,20);
//    QStringList headList;
//    headList<<"222","333","444","55";
//    table.setHorizontalHeaderLabels(QStringList{"案号","案由","开庭时间","开庭地点","承办人","庭审状态" });
//    table.insertRow(0);
//    table.setItem(0,0, new QTableWidgetItem("aaa"));
//    table.setItem(0,1, new QTableWidgetItem("aaa"));
//    table.setItem(0,2, new QTableWidgetItem("aaa"));

//    table.setItem(1,0, new QTableWidgetItem("aaa"));
//    table.setItem(1,1, new QTableWidgetItem("aaa"));
//    table.setItem(1,2, new QTableWidgetItem("aaa"));
//    table.setItem(1,0, new QTableWidgetItem("aaa"));
//    table.setItem(1,1, new QTableWidgetItem("aaa"));
//    table.setItem(1,2, new QTableWidgetItem("aaa"));

    table.show();
    return a.exec();
}
