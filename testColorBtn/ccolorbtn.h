#ifndef CCOLORBTN_H
#define CCOLORBTN_H

#include <QWidget>
#include <QPushButton>
class CColorBtn : public QPushButton
{
    Q_OBJECT
public:
    explicit CColorBtn(QWidget *parent = nullptr);

signals:

public slots:
protected:
    void paintEvent(QPaintEvent* event);
};

#endif // CCOLORBTN_H