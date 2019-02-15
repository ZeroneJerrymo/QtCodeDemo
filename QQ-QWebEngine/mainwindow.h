#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QWebEngineView>


#include "faceform.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_pushButton_clicked();
    void disTime();

    void on_pushButton_2_clicked();
    void addFace(QString text);

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;

    void AsendMsgShow(QString msg);
    void BSendMsgShow(QString msg);
    void revMsgShow(QString msg);

    QTimer *m_timer;
    bool disFlag;
    QWebEngineView* m_pView;
    faceForm *m_faceForm;
    bool faceFormFlag;

};

#endif // MAINWINDOW_H
