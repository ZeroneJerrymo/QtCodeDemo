#include "testtable.h"
#include "ui_testtable.h"

testtable::testtable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::testtable)
{
    ui->setupUi(this);
}

testtable::~testtable()
{
    delete ui;
}
