#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class CProfessionalWordDbWgt;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
    void slot_setspeech();
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    CProfessionalWordDbWgt*  pshowWiget;
};

#endif // MAINWINDOW_H
