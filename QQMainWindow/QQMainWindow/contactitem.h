#ifndef CONTACTITEM_H
#define CONTACTITEM_H

#include <QWidget>
#include "ui_contactitem.h"

class ContactItem : public QWidget
{
	Q_OBJECT

public:
	ContactItem(QWidget *parent = 0);
	~ContactItem();

public:
	void setUserName(const QString& userName);
	void setSignName(const QString& signName);
	void setHeadPixmap(const QPixmap& headPath);
	QSize getHeadLabelSize() const;

private:
	void initControl();

private:
	Ui::ContactItem ui;
};

#endif // CONTACTITEM_H
