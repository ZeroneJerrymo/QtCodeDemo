#include "qqmainwindow.h"
#include "contactitem.h"
#include "rootcontatitem.h"
#include "skinwindow.h"

#include <QPainter>
#include <QMouseEvent>
#include <QSpacerItem>
#include <QProxyStyle>
#include <QTimer>

class CustomProxyStyle : public QProxyStyle
{
public:
	virtual void drawPrimitive(PrimitiveElement element, const QStyleOption * option,
		QPainter * painter, const QWidget * widget = 0) const
	{
		if (PE_FrameFocusRect == element)
		{
			return;
		}
		else
		{
			QProxyStyle::drawPrimitive(element, option, painter, widget);
		}
	}
};

QQMainWindow::QQMainWindow(QWidget *parent)
	: BasicWindow(parent)
{
	ui.setupUi(this);
	m_styleName = "MainWindow";
	loadStyleSheet("MainWindow");
	initControl();

	QTimer* timer = new QTimer(this);
	timer->setInterval(500);
	connect(timer, &QTimer::timeout, [this](){
		static int level = 0;
		if (level == 99)
		{
			level = 0;
		}
		setLevelPixmap(level);
		level++;
	});
	timer->start();
}

QQMainWindow::~QQMainWindow()
{

}

void QQMainWindow::initControl()
{
	ui.treeWidget->setStyle(new CustomProxyStyle);

	setLevelPixmap(0);
	setUserName(QString::fromLocal8Bit("�����-������"));
	setHeadPixmap(":/QQMainWindow/Resources/MainWindow/yutiange.jpg");
	setStatusMenuIcon(":/QQMainWindow/Resources/MainWindow/StatusSucceeded.png");

	QHBoxLayout *flowLayout = new QHBoxLayout();
	flowLayout->setContentsMargins(0, 0, 0, 0);
	flowLayout->setSpacing(2);
	flowLayout->addWidget(addOtherAppExtension(":/QQMainWindow/Resources/MainWindow/app/app_7.png", "app_7"));
	flowLayout->addWidget(addOtherAppExtension(":/QQMainWindow/Resources/MainWindow/app/app_2.png", "app_2"));
	flowLayout->addWidget(addOtherAppExtension(":/QQMainWindow/Resources/MainWindow/app/app_3.png", "app_3"));
	flowLayout->addWidget(addOtherAppExtension(":/QQMainWindow/Resources/MainWindow/app/app_4.png", "app_4"));
	flowLayout->addWidget(addOtherAppExtension(":/QQMainWindow/Resources/MainWindow/app/app_5.png", "app_5"));
	flowLayout->addWidget(addOtherAppExtension(":/QQMainWindow/Resources/MainWindow/app/app_6.png", "app_6"));
	flowLayout->addStretch();
	flowLayout->addWidget(addOtherAppExtension(":/QQMainWindow/Resources/MainWindow/app/skin.png", "app_skin"));
	ui.appWidget->setLayout(flowLayout);

	ui.bottomLayout_up->addWidget(addOtherAppExtension(":/QQMainWindow/Resources/MainWindow/app/app_10.png", "app_10"));
	ui.bottomLayout_up->addWidget(addOtherAppExtension(":/QQMainWindow/Resources/MainWindow/app/app_8.png", "app_8"));
	ui.bottomLayout_up->addWidget(addOtherAppExtension(":/QQMainWindow/Resources/MainWindow/app/app_11.png", "app_11"));
	ui.bottomLayout_up->addWidget(addOtherAppExtension(":/QQMainWindow/Resources/MainWindow/app/app_9.png", "app_9"));
	ui.bottomLayout_up->addStretch();

	ui.lineEdit->installEventFilter(this);
	ui.searchLineEdit->installEventFilter(this);

	initContactTree();
	initStrangerTree();

	connect(ui.sysmin, SIGNAL(clicked(bool)), this, SLOT(onShowMin(bool)));
	connect(ui.sysclose, SIGNAL(clicked(bool)), this, SLOT(onShowClose(bool)));
}

void QQMainWindow::setHeadPixmap(const QString& headPath)
{
	ui.headLabel->setPixmap(getRoundImage(QPixmap(headPath), QPixmap(":/QQMainWindow/Resources/MainWindow/head_mask.png"), ui.headLabel->size()));
}

void QQMainWindow::setUserName(const QString& username)
{
	ui.nameLabel->adjustSize();
	QString name = ui.nameLabel->fontMetrics().elidedText(username, Qt::ElideRight, ui.nameLabel->width());
	ui.nameLabel->setText(name);
}

void QQMainWindow::setStatusMenuIcon(const QString& statusPath)
{
	QPixmap statusBtnPixmap(ui.statusBtn->size());
	statusBtnPixmap.fill(Qt::transparent);
	QPainter painter(&statusBtnPixmap);
	painter.drawPixmap(4, 4, QPixmap(statusPath));
	painter.drawPixmap(16, 3, QPixmap(":/QQMainWindow/Resources/MainWindow/arrow_normal.gft.png"));
	ui.statusBtn->setIcon(statusBtnPixmap);
	ui.statusBtn->setIconSize(ui.statusBtn->size());
}

void QQMainWindow::setLevelPixmap(int level)
{
	QPixmap levelPixmap(ui.levelBtn->size());
	levelPixmap.fill(Qt::transparent);
	QPainter painter(&levelPixmap);
	painter.drawPixmap(0, 4, QPixmap(":/QQMainWindow/Resources/MainWindow/lv.png"));
	int unitNum = level / 1 % 10;//ȡ��λ����
	int tenNum = level / 10 % 10;//ȡʮλ����
	//ʮλ
	painter.drawPixmap(10, 4, QPixmap(":/QQMainWindow/Resources/MainWindow/levelvalue.png"), tenNum * 6, 0, 6, 7);
	//��λ
	painter.drawPixmap(16, 4, QPixmap(":/QQMainWindow/Resources/MainWindow/levelvalue.png"), unitNum * 6, 0, 6, 7);
	ui.levelBtn->setIcon(levelPixmap);
	ui.levelBtn->setIconSize(ui.levelBtn->size());
}

QWidget* QQMainWindow::addOtherAppExtension(const QString& apppath, const QString& appName)
{
	QPushButton* btn = new QPushButton(this);
	btn->setFixedSize(20, 20);
	QPixmap pixmap(btn->size());
	pixmap.fill(Qt::transparent);
	QPainter painter(&pixmap);
	QPixmap appPixmap(apppath);
	painter.drawPixmap((btn->width() - appPixmap.width()) / 2, (btn->height() - appPixmap.height())/2, appPixmap);
	btn->setIcon(pixmap);
	btn->setIconSize(btn->size());
	btn->setProperty("hasborder", true);
	btn->setObjectName(appName);
	connect(btn, &QPushButton::clicked, this, &QQMainWindow::onAppIconCliked);
	return btn;
}

void QQMainWindow::onAppIconCliked()
{
	if (sender()->objectName() == "app_skin")
	{
		SkinWindow* skinWindow = new SkinWindow();
		skinWindow->show();
	}
}

void QQMainWindow::resizeEvent(QResizeEvent *event)
{
	setUserName(QString::fromLocal8Bit("�����-������"));
	__super::resizeEvent(event);
}

bool QQMainWindow::eventFilter(QObject *obj, QEvent *event)
{
	if (ui.searchLineEdit == obj)
	{
		if (event->type() == QEvent::FocusIn)
		{
			ui.searchWidget->setStyleSheet("QWidget#searchWidget {background-color:rgb(255, 255, 255);}\
										   	QPushButton#searchBtn {border-image:url(:/QQMainWindow/Resources/MainWindow/search/main_search_deldown.png);}\
											QPushButton#searchBtn:hover {border-image:url(:/QQMainWindow/Resources/MainWindow/search/main_search_delhighlight.png);}\
											QPushButton#searchBtn:pressed{ border-image:url(:/QQMainWindow/Resources/MainWindow/search/main_search_delhighdown.png);}");
										   	
		}
		else if (event->type() == QEvent::FocusOut)
		{
			ui.searchWidget->setStyleSheet(QString("QWidget#searchWidget {background-color:rgba(%1,%2,%3,50);}\
												   	QPushButton#searchBtn {border-image:url(:/QQMainWindow/Resources/MainWindow/search/search_icon.png);}").arg(m_colorBackGround.red()).arg(m_colorBackGround.green()).arg(m_colorBackGround.blue()));
		}
	}
	return __super::eventFilter(obj, event);
}

void QQMainWindow::mousePressEvent(QMouseEvent *event)
{
	if (qApp->widgetAt(event->pos()) != ui.lineEdit && ui.lineEdit->hasFocus())
	{
		ui.lineEdit->clearFocus();
	}
	else if (qApp->widgetAt(event->pos()) != ui.searchLineEdit && ui.searchLineEdit->hasFocus())
	{
		ui.searchLineEdit->clearFocus();
	}
	__super::mousePressEvent(event);
}

void QQMainWindow::initContactTree()
{
	//չ��������ʱ�źţ��Դﵽ���������ͼƬ��
	connect(ui.treeWidget, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(onItemClicked(QTreeWidgetItem *, int)));
	connect(ui.treeWidget, SIGNAL(itemExpanded(QTreeWidgetItem *)), this, SLOT(onItemExpanded(QTreeWidgetItem *)));
	connect(ui.treeWidget, SIGNAL(itemCollapsed(QTreeWidgetItem *)), this, SLOT(onItemCollapsed(QTreeWidgetItem *)));
	//����ڵ�
	QTreeWidgetItem *pRootFriendItem = new QTreeWidgetItem();
	pRootFriendItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
	//����Data�������֣�Item�Ƿ���ڵ㻹���ӽڵ㣬0�������ڵ㣬1�����ӽڵ�
	pRootFriendItem->setData(0, Qt::UserRole, 0);
	RootContatItem *pItemName = new RootContatItem(ui.treeWidget);
	
	int nMyFriendNum = 6;
	QString qsGroupName = QString::fromLocal8Bit("�ҵĺ��� %1/%2").arg(0).arg(nMyFriendNum);
	pItemName->setText(qsGroupName);
	//�������ڵ�
	ui.treeWidget->addTopLevelItem(pRootFriendItem);
	ui.treeWidget->setItemWidget(pRootFriendItem, 0, pItemName);

	for (int nIndex = 0; nIndex < nMyFriendNum; ++nIndex)
	{
		//����ӽڵ�
		addMyFriendInfo(pRootFriendItem);
	}
}

void QQMainWindow::addMyFriendInfo(QTreeWidgetItem* pRootGroupItem)
{
	QTreeWidgetItem *pChild = new QTreeWidgetItem();
	//����ӽڵ�
	pChild->setData(0, Qt::UserRole, 1);
	ContactItem* pContactItem = new ContactItem(ui.treeWidget);
	pContactItem->setHeadPixmap(getRoundImage(QPixmap(":/QQMainWindow/Resources/MainWindow/yutiange.jpg"), QPixmap(":/QQMainWindow/Resources/MainWindow/head_mask.png"), pContactItem->getHeadLabelSize()));
	pContactItem->setUserName(QString::fromLocal8Bit("�����-������"));
	pContactItem->setSignName(QString::fromLocal8Bit("��ӭ��������繤����"));
	pRootGroupItem->addChild(pChild);
	ui.treeWidget->setItemWidget(pChild, 0, pContactItem);
}

void QQMainWindow::initStrangerTree()
{
	//����ڵ�
	QTreeWidgetItem *pRootFriendItem = new QTreeWidgetItem();
	pRootFriendItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
	//����Data�������֣�Item�Ƿ���ڵ㻹���ӽڵ㣬0�������ڵ㣬1�����ӽڵ�
	pRootFriendItem->setData(0, Qt::UserRole, 0);
	RootContatItem *pItemName = new RootContatItem(ui.treeWidget);

	int nMyFriendNum = 8;
	QString qsGroupName = QString::fromLocal8Bit("İ���� %1/%2").arg(0).arg(nMyFriendNum);
	pItemName->setText(qsGroupName);
	//�������ڵ�
	ui.treeWidget->addTopLevelItem(pRootFriendItem);
	ui.treeWidget->setItemWidget(pRootFriendItem, 0, pItemName);

	for (int nIndex = 0; nIndex < nMyFriendNum; ++nIndex)
	{
		//����ӽڵ�
		addStarngerInfo(pRootFriendItem);
	}
}

void QQMainWindow::addStarngerInfo(QTreeWidgetItem* pRootGroupItem)
{
	QTreeWidgetItem *pChild = new QTreeWidgetItem();
	//����ӽڵ�
	pChild->setData(0, Qt::UserRole, 1);
	ContactItem* pContactItem = new ContactItem(ui.treeWidget);
	pContactItem->setHeadPixmap(getRoundImage(QPixmap(":/QQMainWindow/Resources/MainWindow/yutiange.jpg"), QPixmap(":/QQMainWindow/Resources/MainWindow/head_mask.png"), pContactItem->getHeadLabelSize()));
	pContactItem->setUserName(QString::fromLocal8Bit("�����-������-İ����"));
	pContactItem->setSignName(QString::fromLocal8Bit("��ӭ��������繤����-İ����"));
	pRootGroupItem->addChild(pChild);
	ui.treeWidget->setItemWidget(pChild, 0, pContactItem);
}

void QQMainWindow::onItemClicked(QTreeWidgetItem * item, int column)
{
	bool bIsChild = item->data(0, Qt::UserRole).toBool();
	if (!bIsChild)
	{
		item->setExpanded(!item->isExpanded());
	}
}

void QQMainWindow::onItemExpanded(QTreeWidgetItem * item)
{
	bool bIsChild = item->data(0, Qt::UserRole).toBool();
	if (!bIsChild)
	{
		RootContatItem *prootItem = dynamic_cast<RootContatItem*>(ui.treeWidget->itemWidget(item, 0));
		if (prootItem)
		{
			prootItem->setExpanded(true);
		}
	}
}

void QQMainWindow::onItemCollapsed(QTreeWidgetItem * item)
{
	bool bIsChild = item->data(0, Qt::UserRole).toBool();
	if (!bIsChild)
	{
		RootContatItem *prootItem = dynamic_cast<RootContatItem*>(ui.treeWidget->itemWidget(item, 0));
		if (prootItem)
		{
			prootItem->setExpanded(false);
		}
	}
}