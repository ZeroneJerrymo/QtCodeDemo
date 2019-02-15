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
	//���õȼ�
	void setLevelPixmap(int level);
	//����ͷ��
	void setHeadPixmap(const QString& headPath);
	//�����û�����
	void setUserName(const QString& username);
	//����״̬�����˵�ͼ��
	void setStatusMenuIcon(const QString& statusPath);
	//�������APPӦ��
	QWidget* addOtherAppExtension(const QString& apppath, const QString& appName);
	//��ʼ�������б�
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
