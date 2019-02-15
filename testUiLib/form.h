#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "testuilib_global.h"
namespace Ui {
class Form;
}

class TESTUILIBSHARED_EXPORT Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();

private:
    Ui::Form *ui;
};

#endif // FORM_H
