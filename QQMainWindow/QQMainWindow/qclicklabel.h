#ifndef QCLICKLABEL_H
#define QCLICKLABEL_H

#include <QLabel>

class QClickLabel : public QLabel
{
	Q_OBJECT

public:
	QClickLabel(QWidget *parent);
	~QClickLabel();

signals:
	void clicked();

private:
	void mousePressEvent(QMouseEvent *event);
};

#endif // QCLICKLABEL_H
