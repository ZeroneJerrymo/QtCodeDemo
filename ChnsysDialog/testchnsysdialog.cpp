#include "testchnsysdialog.h"
#include "ui_testchnsysdialog.h"
#include "chnsystitlewidget.h"
testChnsysDialog::testChnsysDialog(QWidget *parent) :
    ChnsysDialog(parent)

{
    this->resize(300,400);

    m_title->setTitleText("标题");
}

testChnsysDialog::~testChnsysDialog()
{
    //delete ui;
}
