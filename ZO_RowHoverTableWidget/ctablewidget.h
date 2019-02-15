#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H
#include <QTableWidget>
#include <QEvent>
class TableWidget : public QWidget
{    Q_OBJECT
 public:
     explicit TableWidget(QWidget *parent = 0);
 protected:
     void setRowColor(int row, QColor color);
 signals:
 public slots:
      void mycellEntered(int row, int column);
 private:
       QTableWidget *tableWidget;
        QColor defaultBkColor;
         int previousColorRow;
};
#endif // TABLEWIDGET_H
