#ifndef NOTIFYMANAGER_H
#define NOTIFYMANAGER_H

#include <QObject>

class NotifyManager : public QObject
{
	Q_OBJECT

public:
	NotifyManager();
	~NotifyManager();

signals:
	void signalSkinChanged(const QColor& color);

public:
	static NotifyManager* getInstance();
	//通知其它窗口更改皮肤
	void notifyOtherWindowChangeSkin(const QColor& color);

private:
	static NotifyManager* instance;
};

#endif // NOTIFYMANAGER_H
