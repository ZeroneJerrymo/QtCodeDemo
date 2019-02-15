#include "readxml.h"
#include <QDebug>
#include <QTextCodec>

    ReadXML::ReadXML(const QString filePath) {
        this->file = new QFile(filePath);
    }

    ReadXML:: ~ReadXML() {
        if(this->file != NULL) {
            delete this->file;
        }
        if(this->doc != NULL) {
            //delete this->doc;
        }
    }


bool ReadXML::getInformation(QList<GroupInfo*>** groups) {

    if(!file->open(QFile::ReadOnly | QFile::Text)) {
   //     qDebug() << "The file is closing";
        return false;
    }

    QString errorStr;
    int errorLine;
    int errorColumn;

    this->doc = new QDomDocument();
    if (!(doc->setContent(file, false, &errorStr, &errorLine, &errorColumn))) {
         return false;
    }

    QDomElement root = doc->documentElement();
    if(root.tagName() != "personalGroup") {
        qDebug() << "���ڵ�������";
    }

    //��ȡϵͳ���룬������ֲ���������
   // QTextCodec *codec = QTextCodec::codecForName("utf-8");

    //���úͶԱ����ļ�ϵͳ��дʱ���Ĭ�ϱ����ʽ
//    QTextCodec::setCodecForLocale(codec);

    //���ô���tr����ʱ��Ĭ���ַ�������
//    QTextCodec::setCodecForTr(codec);

    //�����ַ���������QByteArray����QString����ʱʹ�õ�һ�ֱ��뷽ʽ
  //  QTextCodec::setCodecForCStrings(codec);

 //   QString a = root.attribute("name");
   // qDebug()<<a;

    QDomNodeList list = root.childNodes();

    *groups = new QList<GroupInfo*>[list.length()];
     //*clients = new QList<ClientCode*>*[list.length()];

    for(int i = 0; i < list.length(); i++) {
        QString groupName = list.at(i).toElement().attribute("name");
    //    qDebug() << groupName;
        (*groups)->append(new GroupInfo(groupName));
    }

    for(int i = 0; i < list.length(); i++) {
        QDomNode tempNode = list.at(i);
        QDomNodeList tempLists = tempNode.childNodes();
        for(int loop = 0; loop < tempLists.length(); loop++) {
            QString computerCode = tempLists.at(loop).firstChild().toElement().text();
            qDebug()<< computerCode;
            ClientCode* clientCode = new ClientCode();
            clientCode->setComputerCode(computerCode);
            (*groups)->at(i)->getClients()->append(clientCode);
        }
    }
    //qDebug() << "success";
    file->close();
}
