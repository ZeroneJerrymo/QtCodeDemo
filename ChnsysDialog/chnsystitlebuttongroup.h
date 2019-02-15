#ifndef CHNSYSTITLEBUTTONGROUP_H
#define CHNSYSTITLEBUTTONGROUP_H

#include <QPushButton>
#include <QWidget>

class ChnsysTitleButtonGroup : public QWidget
{
    Q_OBJECT
public:
    explicit ChnsysTitleButtonGroup(QWidget *parent = nullptr);

    void setMinimizeBtnVisiable(bool b_show);
    void setMaximizeBtnVisiable(bool b_show);
    void setCloseBtnVisiable(bool b_show);

signals:

public slots:

protected slots:
    void slot_TitleBtnClicked();
protected:
    QPushButton *m_pMinimizeButton;
    QPushButton *m_pMaximizeButton;
    QPushButton *m_pCloseButton;

};

#endif // CHNSYSTITLEBUTTONGROUP_H
