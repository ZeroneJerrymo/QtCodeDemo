#ifndef MOVEFRIENDTONEWGROUP_H
#define MOVEFRIENDTONEWGROUP_H

#include <QDialog>
#include <QLineEdit>
namespace Ui {
class MoveFriendToNewGroup;
}

class MoveFriendToNewGroup : public QDialog
{
    Q_OBJECT

public:
    explicit MoveFriendToNewGroup(QWidget *parent = 0);
    ~MoveFriendToNewGroup();
   QString getUserName(void);
    QString getGroupName(void);
    QLineEdit* getLineEdit2();
private:
    Ui::MoveFriendToNewGroup *ui;
};

#endif // MOVEFRIENDTONEWGROUP_H
