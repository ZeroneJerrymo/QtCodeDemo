#ifndef CLICKRIGHTBUTTON_H
#define CLICKRIGHTBUTTON_H

#include <QDialog>
#include <QLineEdit>
#include <widget.h>
#include "movefriendtonewgroup.h"

namespace Ui {
class ClickRightButton;
}
class widget;
class ClickRightButton : public QDialog
{
    Q_OBJECT

public:
    ClickRightButton(widget *parent = 0);
    ~ClickRightButton();
    QLineEdit* getNewGroup();
     MoveFriendToNewGroup* getMoveUi();
private slots:
    void on_createGroup_clicked();

    void on_deleteGroup_clicked();

    void on_moveFriendToGroup_clicked();

private:
    Ui::ClickRightButton *ui;
    QLineEdit* newGroup;
    widget* parent;
    MoveFriendToNewGroup* moveUi;
};

#endif // CLICKRIGHTBUTTON_H


