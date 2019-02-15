#include "clickrightbutton.h"
#include "ui_clickrightbutton.h"
#include <qDebug>
#include <QRect>
#include <QObject>

ClickRightButton::ClickRightButton(widget *parent) :
    QDialog(parent),
    ui(new Ui::ClickRightButton),
    parent(parent)
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    //this->setWindowTitle(tr("分组设置"));
    this->newGroup = NULL;
    this->moveUi = NULL;
}

ClickRightButton::~ClickRightButton()
{
    delete ui;
    qDebug() << "ui delete";
}

void ClickRightButton::on_createGroup_clicked()
{
    this->newGroup = new QLineEdit();
    this->newGroup->setWindowTitle(tr("创建分组"));
    this->newGroup->setAttribute(Qt::WA_DeleteOnClose);
    this->newGroup->setText(tr("Input Your Group Name"));
    QObject::connect(this->newGroup, SIGNAL(returnPressed()), this->parent, SLOT(rightButtonClickNewGroup()));
    //QRect tempRect(this->geometry());
   // qDebug() << "width" << tempRect.width();
   // this->newGroup->setGeometry(tempRect);
    this->newGroup->show();
}

QLineEdit* ClickRightButton::getNewGroup() {
    return this->newGroup;
}

void ClickRightButton::on_deleteGroup_clicked()
{
    this->newGroup = new QLineEdit();
    this->newGroup->setWindowTitle(tr("删除分组"));
    this->newGroup->setText(tr("Input Your Group Name"));
    this->newGroup->setAttribute(Qt::WA_DeleteOnClose);
    QObject::connect(this->newGroup, SIGNAL(returnPressed()), this->parent, SLOT(rightButtonDeleteGroup()));
    //QRect tempRect(this->geometry());
   // qDebug() << "width" << tempRect.width();
   // this->newGroup->setGeometry(tempRect);
    this->newGroup->show();
}

void ClickRightButton::on_moveFriendToGroup_clicked()
{
    this->moveUi = new MoveFriendToNewGroup();
    this->moveUi->setAttribute(Qt::WA_DeleteOnClose);
    QObject::connect(this->moveUi->getLineEdit2(), SIGNAL(returnPressed()), this->parent, SLOT(moveButtonToNewGroup()));
    this->moveUi->show();
}

MoveFriendToNewGroup* ClickRightButton::getMoveUi() {
    return this->moveUi;
}
