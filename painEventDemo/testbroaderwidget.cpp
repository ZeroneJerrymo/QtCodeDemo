#include "testbroaderwidget.h"
#include "ui_testbroaderwidget.h"

#include <QPainter>


testBroaderWidget::testBroaderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::testBroaderWidget)
{
    ui->setupUi(this);
}

testBroaderWidget::~testBroaderWidget()
{
    delete ui;
}

