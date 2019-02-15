#ifndef CASECONCEPTS_H
#define CASECONCEPTS_H

#include <QWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QList>
#include "ui_caseconcepts.h"
#pragma  execution_character_set("utf-8")
class caseConcepts : public QWidget
{
	Q_OBJECT

public:
	caseConcepts(QWidget *parent = 0);
	~caseConcepts();
	void initItself();
	void setChildTreeItem(QTreeWidgetItem *fatherItem, QStringList strList);
	void setTreeItemCheckState(QTreeWidgetItem *fatherItem);
private:
	Ui::caseConcepts ui;
private slots:
    void slot_treeItemClicked(QTreeWidgetItem *, int);
signals:
	void deleteCaseConcepts(QString);
	void inputCaseConcepts(QString);	
};

#endif // CASECONCEPTS_H
