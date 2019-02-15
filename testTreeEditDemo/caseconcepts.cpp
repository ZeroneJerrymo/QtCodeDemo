#include "caseconcepts.h"
caseConcepts::caseConcepts(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initItself();
	connect(ui.treeWidget, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(slot_treeItemClicked(QTreeWidgetItem *, int)));
}

caseConcepts::~caseConcepts()
{

}

void caseConcepts::initItself()
{
	setWindowFlags(Qt::FramelessWindowHint);
	

	//初始化树
	//第一根节点
	QTreeWidgetItem *treeItem_civil = new QTreeWidgetItem(ui.treeWidget, QStringList(QString("民事案由")));
	
	QTreeWidgetItem *civil_1 = new QTreeWidgetItem(treeItem_civil, QStringList("适用特殊程序案件案由"));
	QStringList list_civil_1;
	list_civil_1 << "执行异议之诉" << "申请保全";	
	setChildTreeItem(civil_1, list_civil_1);
	setTreeItemCheckState(civil_1);
		
	QTreeWidgetItem *civil_2 = new QTreeWidgetItem(treeItem_civil, QStringList("侵权责任纠纷"));
	QStringList list_civil_2;
	list_civil_2 << "监护人责任纠纷" << "用人单位责任纠纷" << "劳务派遣工作人员侵权责任纠纷" << "机动车交通事故责任纠纷"
		<< "铁路运输损害责任纠纷" << "水上运输损害责任纠纷" << "航空运输损害责任纠纷" << "提供劳务者致害责任纠纷"
		<< "提供劳务者受害责任纠纷" << "网络侵权责任纠纷" << "违反安全保障义务责任纠纷" << "教育机构责任纠纷"
		<< "产品责任纠纷" << "医疗损害责任纠纷" << "环境污染责任纠纷" << "高度危险责任纠纷"
		<< "饲养动物损害责任纠纷" << "物件损害责任纠纷" << "触电人身损害责任纠纷" << "义务帮工人受害责任纠纷"
		<< "见义勇为人受害责任纠纷" << "公证损害责任纠纷";
	setChildTreeItem(civil_2, list_civil_2);
	setTreeItemCheckState(civil_2);

	QTreeWidgetItem *civil_3 = new QTreeWidgetItem(treeItem_civil, QStringList("人格权纠纷"));
	QStringList list_civil_3;
	list_civil_3 << "生命权纠纷权" << "健康权纠纷" << "身体权纠纷";
	setChildTreeItem(civil_3, list_civil_3);
	setTreeItemCheckState(civil_3);
	
	QTreeWidgetItem *civil_4 = new QTreeWidgetItem(treeItem_civil, QStringList("与公司、证券票据等有关的民事纠纷"));
	QStringList list_civil_4;
	list_civil_4 << "信用纠纷" << "票据纠纷" << "保险纠纷";
	setChildTreeItem(civil_4, list_civil_4);
	setTreeItemCheckState(civil_4);

	QTreeWidgetItem *civil_5 = new QTreeWidgetItem(treeItem_civil, QStringList("海事海商纠纷"));
	QStringList list_civil_5;
	list_civil_5 << "海事海商纠纷";
	setChildTreeItem(civil_5, list_civil_5);
	setTreeItemCheckState(civil_5);

	QTreeWidgetItem *civil_6 = new QTreeWidgetItem(treeItem_civil, QStringList("劳动争议、人事争议"));
	QStringList list_civil_6;
	list_civil_6 << "人事争议" << "劳动争议";
	setChildTreeItem(civil_6, list_civil_6);
	setTreeItemCheckState(civil_6);

	QTreeWidgetItem *civil_7 = new QTreeWidgetItem(treeItem_civil, QStringList("知识产权与竞争纠纷"));
	QStringList list_civil_7;
	list_civil_7 << "垄断纠纷" << "不正当竞争纠纷";
	setChildTreeItem(civil_7, list_civil_7);
	setTreeItemCheckState(civil_7);

	QTreeWidgetItem *civil_8 = new QTreeWidgetItem(treeItem_civil, QStringList("合同、无因管理、不当得利纠纷"));
	QTreeWidgetItem *civil_8_1 = new QTreeWidgetItem(civil_8, QStringList("合同纠纷"));
	QTreeWidgetItem *civil_8_1_1 = new QTreeWidgetItem(civil_8_1, QStringList("缔约过失责任纠纷"));
	QTreeWidgetItem *civil_8_1_2 = new QTreeWidgetItem(civil_8_1, QStringList("借款合同纠纷"));
	QStringList list_civil_8_1_2;
	list_civil_8_1_2 << "金融借款合同纠纷" << "同业拆借纠纷"<<"企业借贷纠纷"<<"民间借贷纠纷"
		<<"小额借款合同纠纷"<<"金融不良债权转让合同纠纷"<<"金融不良债权追偿纠纷";
	setChildTreeItem(civil_8_1_2, list_civil_8_1_2);
	setTreeItemCheckState(civil_8_1_2);

	QStringList list_civil_8_1;
	list_civil_8_1 << "确认合同效力纠纷" << "债权人代位权纠纷"<<"债权人撤销权纠纷"<<"债权转让合同纠纷"
		<<"债务转移合同纠纷"<<"债权债务概括转移合同纠纷"<<"悬赏广告纠纷"<<"买卖合同纠纷"
		<< "招标投标买卖合同纠纷" << "拍卖合同纠纷" << "建设用地使用权合同纠纷" << "临时用地合同纠纷"
		<< "探矿权转让合同纠纷" << "采矿权转让合同纠纷" << "房地产开发经营合同纠纷" << "房屋买卖合同纠纷"
		<<"供用电合同纠纷";
	setChildTreeItem(civil_8_1, list_civil_8_1);
	setTreeItemCheckState(civil_8_1);

	QTreeWidgetItem *civil_8_2 = new QTreeWidgetItem(treeItem_civil, QStringList("无因管理纠纷"));
	QStringList list_civil_8_2;
	list_civil_8_2 << "无因管理纠纷";
	setChildTreeItem(civil_8_2, list_civil_8_2);
	setTreeItemCheckState(civil_8_2);

	QTreeWidgetItem *civil_8_3 = new QTreeWidgetItem(treeItem_civil, QStringList("不当得利纠纷"));
	QStringList list_civil_8_3;
	list_civil_8_3 << "不当得利纠纷";
	setChildTreeItem(civil_8_3, list_civil_8_3);
	setTreeItemCheckState(civil_8_3);

	QTreeWidgetItem *civil_9 = new QTreeWidgetItem(treeItem_civil, QStringList("物权纠纷"));
	QStringList list_civil_9;
	list_civil_9 << "所有权确认纠纷" << "用益物权确认纠纷" << "担保物权确认纠纷";
	setChildTreeItem(civil_9, list_civil_9);
	setTreeItemCheckState(civil_9);
	
	QTreeWidgetItem *civil_10 = new QTreeWidgetItem(treeItem_civil, QStringList("婚姻家庭、继承纠纷"));
	QStringList list_civil_10;
	list_civil_10 << "继承纠纷" << "婚姻家庭纠纷" ;
	setChildTreeItem(civil_10, list_civil_10);
	setTreeItemCheckState(civil_10);

	//第二根节点
	QTreeWidgetItem *treeItem_criminal_1 = new QTreeWidgetItem(ui.treeWidget, QStringList(QString("刑事案由")));
	QStringList list_criminal_1;
	list_criminal_1 << "危害国家安全罪" << "背叛国家罪"<<"颠覆国家政权罪";
	setChildTreeItem(treeItem_criminal_1, list_criminal_1);
	setTreeItemCheckState(treeItem_criminal_1);

	//第三根节点
	QTreeWidgetItem *treeItem_administrative_1 = new QTreeWidgetItem(ui.treeWidget, QStringList(QString("行政案由")));
	QStringList list_administrative_1;
	list_administrative_1 << "赔偿类" << "确权类" << "侵权类";
	setChildTreeItem(treeItem_administrative_1, list_administrative_1);
	setTreeItemCheckState(treeItem_administrative_1);

	//第四根节点
	QTreeWidgetItem *treeItem_compensate_1 = new QTreeWidgetItem(ui.treeWidget, QStringList(QString("赔偿案由")));
	QStringList list_compensate_1;
	list_compensate_1 << "违法刑事拘留赔偿" << "超期刑事拘留赔偿" << "无罪逮捕赔偿";
	setChildTreeItem(treeItem_compensate_1, list_compensate_1);
	setTreeItemCheckState(treeItem_compensate_1);
}

void caseConcepts::setChildTreeItem( QTreeWidgetItem *fatherItem,QStringList strList)
{
	for (int i = 0; i < strList.length(); i++)
	{
		QTreeWidgetItem *civil_1_1 = new QTreeWidgetItem(fatherItem, QStringList(strList.at(i)));
	}
}

void caseConcepts::setTreeItemCheckState(QTreeWidgetItem *fatherItem)
{
	for (int i = 0; i < fatherItem->childCount(); i++)
	{		
		if (fatherItem->child(i)->childCount() == 0)
		{
			fatherItem->child(i)->setCheckState(0, fatherItem->checkState(2));
		}		
	}
}

void caseConcepts::slot_treeItemClicked(QTreeWidgetItem *item, int column)
{
	if (item->childCount() == 0)
	{
		if (item->checkState(column) == Qt::Checked)
		{
			emit inputCaseConcepts(item->text(column));
		}
		else
		{
			emit deleteCaseConcepts(item->text(column));
		}	
	}
	else
		return;
}

