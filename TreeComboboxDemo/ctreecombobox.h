#ifndef CTREECOMBOBOX_H
#define CTREECOMBOBOX_H

#include <QComboBox>
#include <QWidget>
class ItemdelegateTest;
class CTreeComboBox : public QComboBox
{
    Q_OBJECT
public:
    CTreeComboBox(QWidget *parent );
    ~ CTreeComboBox();
    void addTreeData(QMap<QString, QStringList> mp_data, bool b_CheckState = false);
    QWidget* getCurrentWidget();
protected:
//    virtual bool eventFilter(QObject *, QEvent *) Q_DECL_OVERRIDE;
private:
    void ConstructTree();
    void ConstructTable();//表格定制

    QWidget* m_curSetDlg;
};

#endif // CTREECOMBOBOX_H
