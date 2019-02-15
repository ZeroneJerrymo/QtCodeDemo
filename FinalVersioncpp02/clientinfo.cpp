#include "clientinfo.h"

/*
    QString userName;
    QString ipHostName;
    QString ipAddress;
*/

    void ClientInfo::setUserName(QString name) {
        this->userName = name;
    }

    void ClientInfo::setIpHostName(QString name) {
        this->ipHostName = name;
    }
    void ClientInfo::setIpAddress(QString name) {
        this->ipAddress = name;
    }

    void ClientInfo::setImageHead(QString imageHead) {
        this->imageHead = imageHead;
    }

    ClientInfo::ClientInfo(QString userName, QString ipHostName, QString ipAddress, QString imageHead, QString imageHead2) {
        this->userName = userName;
        this->ipAddress = ipAddress;
        this->ipHostName = ipHostName;
        this->imageHead = imageHead;
        this->flag = false;
        this->window = NULL;
        this->imageHead2 = imageHead2;
    }

    ClientInfo::ClientInfo() {

        this->userName = "wood";
        this->ipAddress = "127.0.0.1";
        this->ipHostName = "chenchen";
        this->imageHead = "://resource//images//imageForHead//001.png";
        this->window = NULL;
        this->flag = false;
    }

    ClientInfo::~ClientInfo() {

    }

    QString ClientInfo::getIpAddress() {
        return ipAddress;
    }

    QString ClientInfo::getUserName() {
        return userName;
    }

    QString ClientInfo::getIpHostName() {
        return ipHostName;
    }

    QString ClientInfo::getImageHead() {
        return this->imageHead;
    }


    bool* ClientInfo::getFlagPosition() {
        return &(this->flag);
    }


    void ClientInfo::setWindow(QString ip, QString hostName, QString userName,  QString imageHead2, bool* flag,
                               QWidget *parent) {
        this->window = new Widget(ip, hostName,
                                  userName, imageHead2,  flag);
        qDebug()<<"setWindowSuccess";
    }

    Widget* ClientInfo::getWindow() {
        return this->window;
    }

    void ClientInfo::setImageHead2(QString imageHead2) {
        this->imageHead2 = imageHead2;
    }

    QString ClientInfo::getImageHead2() {
        return this->imageHead2;
    }
