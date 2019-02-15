#ifndef QRWIDGET_H
#define QRWIDGET_H

#include <QWidget>
#include "qr/qrencode.h"

class QRWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QRWidget(QWidget *parent = 0);
    ~QRWidget();
    void setString(QString str);
    int getQRWidth() const;
    bool saveImage(QString name, int size);
    QString getString();
private:
    void draw(QPainter &painter, int width, int height);
    QString string;
    QRcode *qr;
signals:

protected:
    void paintEvent(QPaintEvent *);
    QSize sizeHint() const;
    QSize minimumSizeHint() const;
public slots:
};

#endif // QRWIDGET_H
