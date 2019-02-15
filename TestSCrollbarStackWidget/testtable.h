#ifndef TESTTABLE_H
#define TESTTABLE_H

#include <QWidget>

namespace Ui {
class testtable;
}

class testtable : public QWidget
{
    Q_OBJECT

public:
    explicit testtable(QWidget *parent = 0);
    ~testtable();

private:
    Ui::testtable *ui;
};

#endif // TESTTABLE_H
