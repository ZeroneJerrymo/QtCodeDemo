#ifndef ZO_TREEWIDGETONCECLICKOPEN_H
#define ZO_TREEWIDGETONCECLICKOPEN_H

#include <QWidget>
#include <QTreeWidget>
class Zo_treeWidgetOnceClickOpen : public QTreeWidget
{
    Q_OBJECT
public:
    explicit Zo_treeWidgetOnceClickOpen(QWidget *parent = nullptr);

    void mouseDoubleClickEvent(QMouseEvent *event);
signals:

public slots:
protected slots:
    void slot_expendItem(QTreeWidgetItem *pItem, int colum);
};

#endif // ZO_TREEWIDGETONCECLICKOPEN_H
