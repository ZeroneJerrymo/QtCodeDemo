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
    
    m_wordDbMap.insert(QString("电动车"),
        QString("40公斤以上、时速20公里以上的电动自行车，称为轻便电动摩托车或电动摩托车，属于机动车范畴。"));
    m_wordDbMap.insert(QString("交强险"),
        QString("交强险的全称是“机动车交通事故责任强制保险”，是由保险公司对被保险机动车发生道路交通事故造成受害人（不包括本车人员和被保险人）的人身伤亡、财产损失，在责任限额内予以赔偿的强制性责任保险。"));
    m_wordDbMap.insert(QString("交通事故认定责任书"),
        QString("道路交通事故责任认定书是公安交通管理部门依照交通法规对交通事故的当事人有无违章行为，以及对违章行为与交通事故损害后果之间的因果关系进行定性、定量评断时所形成的文书材料。"));
    m_wordDbMap.insert(QString("甲基苯丙胺"),
        QString("冰毒，即兴奋剂甲基苯丙胺"));

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
