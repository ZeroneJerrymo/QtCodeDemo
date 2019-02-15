#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "document.h"

#include <QWidget>
#include <QString>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

//public Q_SLOTS:
//    void setEnabled(bool);

private slots:
    void on_pushButton_clicked();

private:
    bool isModified() const;

    Ui::MainWidget *ui;
    Document m_content;

};

#endif // MAINWIDGET_H
