#ifndef QQMAINWINDOW_H
#define QQMAINWINDOW_H

#include "BasicWindow.h"
#include "ui_qqmainwindow.h"

class QTreeWidgetItem;
class QQMainWindow : public BasicWindow
{
	Q_OBJECT

public:
	QQMainWindow(QWidget *parent = 0);
	~QQMainWindow();

public:
	//设置等级
	void setLevelPixmap(int level);
	//设置头像
	void setHeadPixmap(const QString& headPath);
	//设置用户名称
	void setUserName(const QString& username);
	//设置状态下拉菜单图标
	void setStatusMenuIcon(const QString& statusPath);
	//添加其它APP应用
	QWidget* addOtherAppExtension(const QString& apppath, const QString& appName);
	//初始化好友列表
	void initContactTree();

private slots:
	void onItemExpanded(QTreeWidgetItem * item);
	void onItemCollapsed(QTreeWidgetItem * item);
	void onItemClicked(QTreeWidgetItem * item, int column);
	void onAppIconCliked();

private:
	void initControl();
	void initStrangerTree();
	void addMyFriendInfo(QTreeWidgetItem* pRootGroupItem);
	void addStarngerInfo(QTreeWidgetItem* pRootGroupItem);

private:
	void resizeEvent(QResizeEvent *event) override;
	bool eventFilter(QObject *watched, QEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;

private:
	Ui::QQMainWindowClass ui;
};

#endif // QQMAINWINDOW_H
