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
	

	//��ʼ����
	//��һ���ڵ�
	QTreeWidgetItem *treeItem_civil = new QTreeWidgetItem(ui.treeWidget, QStringList(QString("���°���")));
	
	QTreeWidgetItem *civil_1 = new QTreeWidgetItem(treeItem_civil, QStringList("����������򰸼�����"));
	QStringList list_civil_1;
	list_civil_1 << "ִ������֮��" << "���뱣ȫ";	
	setChildTreeItem(civil_1, list_civil_1);
	setTreeItemCheckState(civil_1);
		
	QTreeWidgetItem *civil_2 = new QTreeWidgetItem(treeItem_civil, QStringList("��Ȩ���ξ���"));
	QStringList list_civil_2;
	list_civil_2 << "�໤�����ξ���" << "���˵�λ���ξ���" << "������ǲ������Ա��Ȩ���ξ���" << "��������ͨ�¹����ξ���"
		<< "��·���������ξ���" << "ˮ�����������ξ���" << "�������������ξ���" << "�ṩ�������º����ξ���"
		<< "�ṩ�������ܺ����ξ���" << "������Ȩ���ξ���" << "Υ����ȫ�����������ξ���" << "�����������ξ���"
		<< "��Ʒ���ξ���" << "ҽ�������ξ���" << "������Ⱦ���ξ���" << "�߶�Σ�����ξ���"
		<< "�������������ξ���" << "��������ξ���" << "�������������ξ���" << "����﹤���ܺ����ξ���"
		<< "������Ϊ���ܺ����ξ���" << "��֤�����ξ���";
	setChildTreeItem(civil_2, list_civil_2);
	setTreeItemCheckState(civil_2);

	QTreeWidgetItem *civil_3 = new QTreeWidgetItem(treeItem_civil, QStringList("�˸�Ȩ����"));
	QStringList list_civil_3;
	list_civil_3 << "����Ȩ����Ȩ" << "����Ȩ����" << "����Ȩ����";
	setChildTreeItem(civil_3, list_civil_3);
	setTreeItemCheckState(civil_3);
	
	QTreeWidgetItem *civil_4 = new QTreeWidgetItem(treeItem_civil, QStringList("�빫˾��֤ȯƱ�ݵ��йص����¾���"));
	QStringList list_civil_4;
	list_civil_4 << "���þ���" << "Ʊ�ݾ���" << "���վ���";
	setChildTreeItem(civil_4, list_civil_4);
	setTreeItemCheckState(civil_4);

	QTreeWidgetItem *civil_5 = new QTreeWidgetItem(treeItem_civil, QStringList("���º��̾���"));
	QStringList list_civil_5;
	list_civil_5 << "���º��̾���";
	setChildTreeItem(civil_5, list_civil_5);
	setTreeItemCheckState(civil_5);

	QTreeWidgetItem *civil_6 = new QTreeWidgetItem(treeItem_civil, QStringList("�Ͷ����顢��������"));
	QStringList list_civil_6;
	list_civil_6 << "��������" << "�Ͷ�����";
	setChildTreeItem(civil_6, list_civil_6);
	setTreeItemCheckState(civil_6);

	QTreeWidgetItem *civil_7 = new QTreeWidgetItem(treeItem_civil, QStringList("֪ʶ��Ȩ�뾺������"));
	QStringList list_civil_7;
	list_civil_7 << "¢�Ͼ���" << "��������������";
	setChildTreeItem(civil_7, list_civil_7);
	setTreeItemCheckState(civil_7);

	QTreeWidgetItem *civil_8 = new QTreeWidgetItem(treeItem_civil, QStringList("��ͬ���������������������"));
	QTreeWidgetItem *civil_8_1 = new QTreeWidgetItem(civil_8, QStringList("��ͬ����"));
	QTreeWidgetItem *civil_8_1_1 = new QTreeWidgetItem(civil_8_1, QStringList("��Լ��ʧ���ξ���"));
	QTreeWidgetItem *civil_8_1_2 = new QTreeWidgetItem(civil_8_1, QStringList("����ͬ����"));
	QStringList list_civil_8_1_2;
	list_civil_8_1_2 << "���ڽ���ͬ����" << "ͬҵ������"<<"��ҵ�������"<<"���������"
		<<"С�����ͬ����"<<"���ڲ���ծȨת�ú�ͬ����"<<"���ڲ���ծȨ׷������";
	setChildTreeItem(civil_8_1_2, list_civil_8_1_2);
	setTreeItemCheckState(civil_8_1_2);

	QStringList list_civil_8_1;
	list_civil_8_1 << "ȷ�Ϻ�ͬЧ������" << "ծȨ�˴�λȨ����"<<"ծȨ�˳���Ȩ����"<<"ծȨת�ú�ͬ����"
		<<"ծ��ת�ƺ�ͬ����"<<"ծȨծ�����ת�ƺ�ͬ����"<<"���͹�����"<<"������ͬ����"
		<< "�б�Ͷ��������ͬ����" << "������ͬ����" << "�����õ�ʹ��Ȩ��ͬ����" << "��ʱ�õغ�ͬ����"
		<< "̽��Ȩת�ú�ͬ����" << "�ɿ�Ȩת�ú�ͬ����" << "���ز�������Ӫ��ͬ����" << "����������ͬ����"
		<<"���õ��ͬ����";
	setChildTreeItem(civil_8_1, list_civil_8_1);
	setTreeItemCheckState(civil_8_1);

	QTreeWidgetItem *civil_8_2 = new QTreeWidgetItem(treeItem_civil, QStringList("����������"));
	QStringList list_civil_8_2;
	list_civil_8_2 << "����������";
	setChildTreeItem(civil_8_2, list_civil_8_2);
	setTreeItemCheckState(civil_8_2);

	QTreeWidgetItem *civil_8_3 = new QTreeWidgetItem(treeItem_civil, QStringList("������������"));
	QStringList list_civil_8_3;
	list_civil_8_3 << "������������";
	setChildTreeItem(civil_8_3, list_civil_8_3);
	setTreeItemCheckState(civil_8_3);

	QTreeWidgetItem *civil_9 = new QTreeWidgetItem(treeItem_civil, QStringList("��Ȩ����"));
	QStringList list_civil_9;
	list_civil_9 << "����Ȩȷ�Ͼ���" << "������Ȩȷ�Ͼ���" << "������Ȩȷ�Ͼ���";
	setChildTreeItem(civil_9, list_civil_9);
	setTreeItemCheckState(civil_9);
	
	QTreeWidgetItem *civil_10 = new QTreeWidgetItem(treeItem_civil, QStringList("������ͥ���̳о���"));
	QStringList list_civil_10;
	list_civil_10 << "�̳о���" << "������ͥ����" ;
	setChildTreeItem(civil_10, list_civil_10);
	setTreeItemCheckState(civil_10);

	//�ڶ����ڵ�
	QTreeWidgetItem *treeItem_criminal_1 = new QTreeWidgetItem(ui.treeWidget, QStringList(QString("���°���")));
	QStringList list_criminal_1;
	list_criminal_1 << "Σ�����Ұ�ȫ��" << "���ѹ�����"<<"�߸�������Ȩ��";
	setChildTreeItem(treeItem_criminal_1, list_criminal_1);
	setTreeItemCheckState(treeItem_criminal_1);

	//�������ڵ�
	QTreeWidgetItem *treeItem_administrative_1 = new QTreeWidgetItem(ui.treeWidget, QStringList(QString("��������")));
	QStringList list_administrative_1;
	list_administrative_1 << "�⳥��" << "ȷȨ��" << "��Ȩ��";
	setChildTreeItem(treeItem_administrative_1, list_administrative_1);
	setTreeItemCheckState(treeItem_administrative_1);

	//���ĸ��ڵ�
	QTreeWidgetItem *treeItem_compensate_1 = new QTreeWidgetItem(ui.treeWidget, QStringList(QString("�⳥����")));
	QStringList list_compensate_1;
	list_compensate_1 << "Υ�����¾����⳥" << "�������¾����⳥" << "��������⳥";
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

