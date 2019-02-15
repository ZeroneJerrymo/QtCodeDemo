#ifndef FRIENDPART_H
#define FRIENDPART_H

#include <QMouseEvent>
#include <QToolButton>
#include <QWidget>
#include <QList>
#include <QVBoxLayout>
#include "clientinfo.h"
#include <QRect>

#define HEADSIZE 100
class FriendPart : public QWidget
{
  Q_OBJECT
public:
  FriendPart(QWidget *parent = 0, Qt::WindowFlags f = 0);
  ~FriendPart();

private:    //˽�г�Ա
  QList<QToolButton*> *buttons;//������Ŀ�����еİ�ť
  QList<ClientInfo*> *clients;
  QVBoxLayout *layout; //��Ͽ�
  QWidget* parent;
  QRect tempRect;


private slots:
    void clickFriend();

public:
  void insertNewClient(ClientInfo* client, QString path, bool flag = true);
  void setClientInfo(QList<ClientInfo*> *clients);
  void addMoreWidgets() ;
  void deleteButton(QString hostName);
//protected:
 //void mousePressEvent(QMouseEvent *event);
};




#endif // FRIENDPART_H
