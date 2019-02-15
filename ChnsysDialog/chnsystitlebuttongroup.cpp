#include "chnsystitlebuttongroup.h"

#include <QHBoxLayout>

ChnsysTitleButtonGroup::ChnsysTitleButtonGroup(QWidget *parent) : QWidget(parent)
{
    m_pMinimizeButton = new QPushButton(this);
    m_pMaximizeButton = new QPushButton(this);
    m_pCloseButton = new QPushButton(this);

    m_pMinimizeButton->setObjectName("minimizeButton");
    m_pMaximizeButton->setObjectName("maximizeButton");
    m_pCloseButton->setObjectName("closeButton");

    m_pMinimizeButton->setToolTip("Minimize");
    m_pMaximizeButton->setToolTip("Maximize");
    m_pCloseButton->setToolTip("Close");

    QHBoxLayout *pLayout = new QHBoxLayout(this);
     pLayout->addWidget(m_pMinimizeButton);
     pLayout->addWidget(m_pMaximizeButton);
     pLayout->addWidget(m_pCloseButton);
     pLayout->setSpacing(0);
     pLayout->setContentsMargins(5, 0, 5, 0);
    setLayout(pLayout);

    connect(m_pMinimizeButton, SIGNAL(clicked(bool)), this, SLOT(slot_TitleBtnClicked()));
    connect(m_pMaximizeButton, SIGNAL(clicked(bool)), this, SLOT(slot_TitleBtnClicked()));
    connect(m_pCloseButton, SIGNAL(clicked(bool)), this, SLOT(slot_TitleBtnClicked()));

}

void ChnsysTitleButtonGroup::setMinimizeBtnVisiable(bool b_show)
{
    m_pMinimizeButton->setVisible(b_show);
}

void ChnsysTitleButtonGroup::setMaximizeBtnVisiable(bool b_show)
{
    m_pMaximizeButton->setVisible(b_show);
}

void ChnsysTitleButtonGroup::setCloseBtnVisiable(bool b_show)
{
    m_pCloseButton->setVisible(b_show);
}

void ChnsysTitleButtonGroup::slot_TitleBtnClicked()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        if (pButton == m_pMinimizeButton)
        {
            pWindow->showMinimized();
        }
        else if (pButton == m_pMaximizeButton)
        {
            pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();
        } else if (pButton == m_pCloseButton)
        {
            pWindow->close();
        }
    }
}

