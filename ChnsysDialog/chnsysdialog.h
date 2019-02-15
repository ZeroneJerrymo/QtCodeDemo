#ifndef CHNSYSDIALOG_H
#define CHNSYSDIALOG_H

#include <QWidget>
#include <QAbstractButton>
#include <QVBoxLayout>
class ChnsysTitleWidget;
class ChnsysAbstractDialog : public QWidget
{
    Q_OBJECT
public:
    explicit ChnsysAbstractDialog(QWidget *parent = nullptr);
protected:
    virtual void InitDialogUI() = 0;
    virtual void retranlateUI() = 0;
};


class ChnsysDialog : public ChnsysAbstractDialog
{
    Q_OBJECT
public:
    explicit ChnsysDialog(QWidget *parent = nullptr);

    //void setLayout(QLayout*) ;
    void InitDialogUI();
    void retranlateUI();
    void LoadStyleSteetFile();
protected:
    virtual void  paintEvent();
protected:
    ChnsysTitleWidget* m_title;
    QWidget* m_centerWidget;
    QVBoxLayout* mainLayout;
};

#endif // CHNSYSDIALOG_H
