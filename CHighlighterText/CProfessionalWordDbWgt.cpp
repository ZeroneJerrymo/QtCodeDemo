#include "CProfessionalWordDbWgt.h"
#include <QVBoxLayout>
#include <qDebug>
CProfessionalWordDbWgt::CProfessionalWordDbWgt(QWidget *parent)
    : QDialog(parent)
{
    resize(400, 400);
    initUI();
    initLayout();
}

CProfessionalWordDbWgt::~CProfessionalWordDbWgt()
{

}

void CProfessionalWordDbWgt::initUI()
{
    te_wordDb = new QTextEdit(this);
    te_wordDb->setStyleSheet("border: 0; background-color:rgb(255,255,255)");
    
    m_wordDbMap.insert(QString("�綯��"),
        QString("40�������ϡ�ʱ��20�������ϵĵ綯���г�����Ϊ���綯Ħ�г���綯Ħ�г������ڻ��������롣"));
    m_wordDbMap.insert(QString("��ǿ��"),
        QString("��ǿ�յ�ȫ���ǡ���������ͨ�¹�����ǿ�Ʊ��ա������ɱ��չ�˾�Ա����ջ�����������·��ͨ�¹�����ܺ��ˣ�������������Ա�ͱ������ˣ��������������Ʋ���ʧ���������޶��������⳥��ǿ�������α��ա�"));
    m_wordDbMap.insert(QString("��ͨ�¹��϶�������"),
        QString("��·��ͨ�¹������϶����ǹ�����ͨ���������ս�ͨ����Խ�ͨ�¹ʵĵ���������Υ����Ϊ���Լ���Υ����Ϊ�뽻ͨ�¹��𺦺��֮��������ϵ���ж��ԡ���������ʱ���γɵ�������ϡ�"));
    m_wordDbMap.insert(QString("�׻�������"),
        QString("���������˷ܼ��׻�������"));

    addWordDb(m_wordDbMap);
}

void CProfessionalWordDbWgt::addWordDb(QMap<QString, QString> wordDbmap)
{
    QString pHtml;
    QMap<QString, QString> ::Iterator iter;
    for (iter = wordDbmap.begin(); iter != wordDbmap.end(); ++iter)
    {
        pHtml += QString("<div style=\"color:#000000; text - align: left; \">"
            " <div style = \"font-size: 14px;line-height: 40px\">%1< / div>"
            " <div style = \"font-size: 12px;\">%2< / div> < / div>").arg(iter.key()).arg(iter.value());
           // te_wordDb->insertHtml(QString("<div style=\"color:#ff5500; text - align: left; \">"
            //    " <div style = \"font-size: 14px;line-height: 50px\">%1< / div>"
            //    " <div style = \"font-size: 12px;\">%2< / div> < / div>").arg());
        m_wordDbMap.insert(iter.key(), iter.value());
    }
    te_wordDb->insertHtml(pHtml);
}


void CProfessionalWordDbWgt::initLayout()
{
    QVBoxLayout* Vlayout = new QVBoxLayout;
    Vlayout->addWidget(te_wordDb);
    Vlayout->setContentsMargins(0,0,0,0);
    this->setLayout(Vlayout);
}

void CProfessionalWordDbWgt::tryUpdataStyle(QList<QString> speechWordList)
{
    QString pHtml;
    QMap<QString, QString> ::Iterator iter;
    QString  pcolor;
    for (iter = m_wordDbMap.begin(); iter != m_wordDbMap.end(); ++iter)
    {
            pcolor  = QString("#000000");
        if (speechWordList.contains(iter.key()))
        {
            pcolor = QString("#f48f20");
        }
        pHtml += QString("<div style=\"color:%1; text - align: left; \">"
            " <div style = \"font-size: 14px;line-height: 40px\">%2< / div>"
            " <div style = \"font-size: 12px;\">%3< / div> < / div>").arg(pcolor).arg(iter.key()).arg(iter.value());
        // te_wordDb->insertHtml(QString("<div style=\"color:#ff5500; text - align: left; \">"
        //    " <div style = \"font-size: 14px;line-height: 50px\">%1< / div>"
        //    " <div style = \"font-size: 12px;\">%2< / div> < / div>").arg());
        m_wordDbMap.insert(iter.key(), iter.value());
    }
    te_wordDb->clear();
    te_wordDb->insertHtml(pHtml);
}

void CProfessionalWordDbWgt::setSpeedWord(QString speechWord)
{
    QList<QString> speechWordList;
    qDebug()<<speechWord;
    QMap<QString, QString> ::Iterator iter;
    for (iter = m_wordDbMap.begin(); iter != m_wordDbMap.end(); ++iter)
    {
        if (speechWord.contains(iter.key()))
        {
            speechWordList.append(iter.key());
        }
    }
    qDebug()<<"22*****"<<speechWordList;
        tryUpdataStyle(speechWordList);

}
