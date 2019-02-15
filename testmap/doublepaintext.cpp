#include "doublepaintext.h"
#include "ui_doublepaintext.h"

doublePaintext::doublePaintext(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::doublePaintext)
{
    ui->setupUi(this);
}

doublePaintext::~doublePaintext()
{
    delete ui;
}
