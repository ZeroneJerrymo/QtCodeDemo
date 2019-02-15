#ifndef TESTCHNSYSDIALOG_H
#define TESTCHNSYSDIALOG_H

#include <QWidget>
#include "chnsysdialog.h"

class testChnsysDialog : public ChnsysDialog
{
    Q_OBJECT

public:
    explicit testChnsysDialog(QWidget *parent = 0);
    ~testChnsysDialog();

};

#endif // TESTCHNSYSDIALOG_H
