#ifndef DOUBLEPAINTEXT_H
#define DOUBLEPAINTEXT_H

#include <QWidget>

namespace Ui {
class doublePaintext;
}

class doublePaintext : public QWidget
{
    Q_OBJECT

public:
    explicit doublePaintext(QWidget *parent = 0);
    ~doublePaintext();

private:
    Ui::doublePaintext *ui;
};

#endif // DOUBLEPAINTEXT_H
