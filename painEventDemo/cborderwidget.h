#ifndef CBORDERWIDGET_H
#define CBORDERWIDGET_H

#include <QWidget>

class CBorderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CBorderWidget(QWidget *parent = nullptr);

     void paintEvent(QPaintEvent* event);

signals:

public slots:

private:
    bool bBorder;
};

#endif // CBORDERWIDGET_H
