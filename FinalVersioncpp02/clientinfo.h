#ifndef CLIENTINFO_H
#define CLIENTINFO_H
#include <QString>
#include "ymzwidget.h"

class ClientInfo {

private:
    QString userName;
    QString ipHostName;
    QString ipAddress;
    QString imageHead;
    QString imageHead2;
    bool flag;
    Widget* window;

public :
    ClientInfo();
    ClientInfo(QString userName, QString ipHostName
               , QString ipAddress, QString imageHead, QString imageHead2);
    ~ClientInfo();

    void setUserName(QString name);
    void setIpHostName(QString name);
    void setIpAddress(QString name);
    void setImageHead(QString imageHead);
    void setWindow(QString ip, QString hostName, QString userName,  QString imageHead2, bool* flag = NULL,
                   QWidget *parent = 0);
    void setImageHead2(QString imageHead2);


    QString getUserName();
    QString getIpHostName();
    QString getIpAddress();
    Widget* getWindow();
    bool* getFlagPosition();
    QString getImageHead();
    QString getImageHead2();
};

#endif // CLIENTINFO_H
