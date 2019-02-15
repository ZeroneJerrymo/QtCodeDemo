#include "writexml.h"

#include <QListIterator>
#include <QDomDocument>
#include <QFile>
#include <QTextStream>
#include <QDebug>
WriteXML::WriteXML()
{
}

void WriteXML::writeInformation(QList<GroupInfo*>* groups) {

    qDebug() <<"WriteXML was calling";
    QDomDocument domDocument;

    QDomProcessingInstruction instruction =
            domDocument.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");

    domDocument.appendChild(instruction);

    QDomElement root = domDocument.createElement("personGroup");
    root.setAttribute("name", "wood");
    domDocument.appendChild(root);

    QListIterator<GroupInfo*> iter(*groups);
    while(iter.hasNext()) {
        GroupInfo* group = iter.next();
        QString groupName = group->getGroupName();
        //QString tagName = groupName.right(groupName.length() - 2);
        QString tagName = groupName;
        QDomElement newElem = domDocument.createElement(tagName);
        newElem.setAttribute("name", groupName);
        root.appendChild(newElem);

        QList<ClientCode*>* clients = group->getClients();
        QListIterator<ClientCode*> iter2(*clients);
        while(iter2.hasNext()) {
            ClientCode* client = iter2.next();
            QDomElement newElem2 = domDocument.createElement("computer");
            newElem.appendChild(newElem2);

            QDomElement newElem3 = domDocument.createElement("computerCode");
            newElem2.appendChild(newElem3);

            const QString ip =client->getComputerCode() ;
            QDomText newElem4 = domDocument.createTextNode(ip);
            newElem3.appendChild(newElem4);
        }

    }



    //QTextStream out(&file);
   // domDocument.save(out,1);
   // file.close();

    QFile file("person.xml");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate |QIODevice::Text))
         return;
    QTextStream out(&file);
    out.setCodec("UTF-8");
    domDocument.save(out,4,QDomNode::EncodingFromTextStream);
    file.close();
}
