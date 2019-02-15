#include "ctreeeditdemo.h"

CTreeLineEdit:: CTreeLineEdit(QWidget *parent)
    : QLineEdit(parent)
{
    m_pBtn = new QPushButton(this);
    m_pMenu = new QMenu(this);
    temp_caseconcepts = new caseConcepts;
    m_widgetAction = new QWidgetAction(this);
    QIcon ico(":/NewCos/Resources/cos_newSch/calendar.png");
    m_pBtn->setIcon(ico);
    m_pBtn->setStyleSheet("QPushButton{border:none;} QPushButton::menu-indicator{image:none;}");//设置按钮的样式：去除边框和向下的箭头
    setTextMargins(0, 0, this->height(), this->width() - m_pBtn->width());
    m_pBtn->setMouseTracking(true);      //设置为不按下鼠标键触发moveEvent

    m_widgetAction->setDefaultWidget(temp_caseconcepts);
    m_pMenu->addAction(m_widgetAction);
    m_widgetAction->installEventFilter(this);
    m_pBtn->setMenu(m_pMenu);
//    connect(this, SIGNAL(textChanged(const QString &)), this, SLOT(slot_textChanged(const QString &)));
    connect(m_pBtn, SIGNAL(clicked()), this, SLOT(slot_m_pBtnClicked()));
    connect(temp_caseconcepts, SIGNAL(inputCaseConcepts(QString)), this, SLOT(slot_inputCaseConcepts(QString)));
    connect(temp_caseconcepts, SIGNAL(deleteCaseConcepts(QString)), this, SLOT(slot_deleteCaseConcepts(QString)));

}

CTreeLineEdit::~CTreeLineEdit()
{

}

void CTreeLineEdit::paintEvent(QPaintEvent * e)
{
    m_pBtn->resize(this->height(), this->height());
    m_pBtn->move(this->width() - m_pBtn->width(), 0);
    QLineEdit::paintEvent(e);
}

void CTreeLineEdit::mouseMoveEvent(QMouseEvent* event)
{
    QPoint mousepos = event->pos();
    //qDebug() << mousepos;
    //在按钮范围内鼠标变成箭头
    if (mousepos.rx() > this->width() - m_pBtn->width()
        && mousepos.rx() <this->width()
        && mousepos.ry() > 0
        && mousepos.ry() < m_pBtn->height())
    {
        this->setCursor(Qt::ArrowCursor);
    }
    else
    {
        this->setCursor(Qt::IBeamCursor); //范围之外变回原来形状
    }
    QLineEdit::mouseMoveEvent(event);
}

void CTreeLineEdit::focusInEvent(QFocusEvent *e)
{
    emit signalFocusIn();
    QLineEdit::focusInEvent(e);
}

void CTreeLineEdit::focusOutEvent(QFocusEvent *e)
{
    setEnabled(false);
    //clearFocus();
    setEnabled(true);
    if (this->text()=="")
    {
        return;
    }
    if (m_pBtn->hasFocus())
    {
        //this->setEnabled(false);
        return;
    }
    QLineEdit::focusOutEvent(e);
}

void CTreeLineEdit::slot_m_pBtnClicked()
{
    m_pMenu->show();//当点击按钮时显示下拉菜单
}

void CTreeLineEdit::slot_inputCaseConcepts(QString str)
{
    list_caseReason.append(str);
    QString inputStr;
    for (int i = 0; i < list_caseReason.length(); i++)
    {
        inputStr = inputStr + list_caseReason.at(i) + ";";
    }
    this->clear();
    this->setText(inputStr);
}

void CTreeLineEdit::slot_deleteCaseConcepts(QString str)
{
    for (int i = 0; i < list_caseReason.length(); i++)
    {
        if (list_caseReason.at(i) == str)
        {
            list_caseReason.removeAt(i);
            QString inputStr;
            for (int j = 0; j < list_caseReason.length(); j++)
            {
                inputStr += list_caseReason.at(j) + ";";
            }
            this->clear();
            this->setText(inputStr);
        }
    }
}
