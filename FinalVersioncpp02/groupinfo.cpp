#include "groupinfo.h"


GroupInfo::GroupInfo(QString groupName) {
    this->groupName = groupName;
    this->clients = new QList<ClientCode*>();
}

GroupInfo::~GroupInfo() {

    if((this->clients) != NULL) {
        for(int i = 0; i < (this->clients->length()); i++) {
            delete this->clients->at(i);
            this->clients->removeAt(i);
        }
        delete this->clients;
    }

}

void GroupInfo::setGroupName(QString groupName) {
    this->groupName = groupName;
}

QString GroupInfo::getGroupName(void) {
    return this->groupName;
}

void GroupInfo::setClients(QList<ClientCode*>* clients) {
    if(clients == NULL && (this->clients == NULL)) {
        this->clients = new QList<ClientCode*>();
    }else {
        this->clients = clients;
    }
}

QList<ClientCode*>* GroupInfo::getClients(void) {
    return this->clients;
}
