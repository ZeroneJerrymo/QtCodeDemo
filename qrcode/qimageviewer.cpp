#include "qimageviewer.h"
#include <QStyleOption>


QImageViewer::QImageViewer(QWidget *parent) :
    QWidget(parent)
{
}

void QImageViewer::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    if (m_pixmap.isNull())
        return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    QSize pixSize = m_pixmap.size();
    pixSize.scale(event->rect().size(), Qt::KeepAspectRatio);

    QPoint topleft;
    topleft.setX((this->width() - pixSize.width()) / 2);
    topleft.setY((this->height() - pixSize.height()) / 2);

    painter.drawPixmap(topleft, m_pixmap.scaled(pixSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

const QPixmap* QImageViewer::pixmap() const
{
    return &m_pixmap;
}

void QImageViewer::setPixmap(const QPixmap &pix)
{
    m_pixmap = pix;
    this->update();
}
