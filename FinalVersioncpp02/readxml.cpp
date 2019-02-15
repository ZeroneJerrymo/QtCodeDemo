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
        qDebug() << "根节点有问题";
    }

    //获取系统编码，否则移植会出现乱码
   // QTextCodec *codec = QTextCodec::codecForName("utf-8");

    //设置和对本地文件系统读写时候的默认编码格式
//    QTextCodec::setCodecForLocale(codec);

    //设置传给tr函数时的默认字符串编码
//    QTextCodec::setCodecForTr(codec);

    //用在字符常量或者QByteArray构造QString对象时使用的一种编码方式
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
