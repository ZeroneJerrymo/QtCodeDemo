#include "mainwindow.h"
#include <QApplication>
#include "dialog.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Dialog * m_dlg = new Dialog;
    if(m_dlg->exec() == QDialog::Accepted)
    {
        delete m_dlg;
    }else{
         delete m_dlg;
    }
    return a.exec();
}
