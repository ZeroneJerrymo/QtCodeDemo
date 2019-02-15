#ifndef GROUPINFO_H
#define GROUPINFO_H
#include "clientcode.h"
#include <QList>
class GroupInfo
{
private:

    QString groupName;
    QList<ClientCode*> *clients;

public:
    GroupInfo(QString groupName = "");
    ~GroupInfo();

    void setGroupName(QString groupName);
    QString getGroupName(void);
    void setClients(QList<ClientCode*>* clients = NULL);
    QList<ClientCode*>* getClients(void);
};

#endif // GROUPINFO_H
