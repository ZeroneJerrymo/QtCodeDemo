#ifndef ROOTCONTATITEM_H
#define ROOTCONTATITEM_H

#include <QLabel>

class QPropertyAnimation;
class RootContatItem : public QLabel
{
	Q_OBJECT
	Q_PROPERTY(int rotation READ rotation WRITE setRotation)

public:
	RootContatItem(QWidget *parent = 0);
	~RootContatItem();

public:
	void setText(const QString& title);
	void setExpanded(bool expand);

private:
	int rotation();
	void setRotation(int rotation);

private:
	void paintEvent(QPaintEvent *event);

private:
	QPropertyAnimation * m_animation;
	QString m_titleText;
	int m_rotation;
};

#endif // ROOTCONTATITEM_H
