#include "movefriendtonewgroup.h"
#include "ui_movefriendtonewgroup.h"

MoveFriendToNewGroup::MoveFriendToNewGroup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MoveFriendToNewGroup)
{
    ui->setupUi(this);
}

MoveFriendToNewGroup::~MoveFriendToNewGroup()
{
    delete ui;
}

QString MoveFriendToNewGroup::getUserName() {
    return this->ui->lineEdit->text();
}

QString MoveFriendToNewGroup::getGroupName() {
    return this->ui->lineEdit_2->text();
}

QLineEdit* MoveFriendToNewGroup::getLineEdit2() {
    return this->ui->lineEdit_2;
}
