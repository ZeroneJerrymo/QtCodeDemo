#include <QApplication>
#include "widget.h"
#include <QList>
#include "groupinfo.h"
#include <QDebug>
#include <QWidget>
#include "readxml.h"
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
  // QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
//    QTextCodec *codec = QTextCodec::codecForName("System");
//    QTextCodec::setCodecForLocale(codec);
//    QTextCodec::setCodecForCStrings(codec);
//    QTextCodec::setCodecForTr(codec);
    //const QString path = ":/resource/files/personalInformation/person.xml";
   // ReadXML read(path);
    //QList<GroupInfo*>* list;
    //qDebug() <<read.getInformation(&list);
    widget w;
    //w.setWindowFlags(Qt::X11BypassWindowManagerHint);
    w.show();
   //w.setAttribute(Qt::WA_DeleteOnClose);
   //qDebug() << "start!!!";
 //  qDebug() << "list.length" << QString::number(list->length());
/*
    QListIterator<GroupInfo*> iter(*list);
    while(iter.hasNext()) {
         GroupInfo* group = iter.next();
          qDebug() << QObject::tr("组的名字为:", "utf-8") << group->getGroupName();
          QListIterator<ClientCode*> iter2(*(group->getClients()));
          while(iter2.hasNext()) {
              ClientCode* client = iter2.next();
              qDebug() << QObject::tr("成员的ip地址为:") << client->getComputerCode();
         }
      }
      */
    return a.exec();
}
