#include "clientcode.h"

ClientCode::ClientCode()
{
}

void ClientCode::setComputerCode(QString computerCode) {
    this->computerCode = computerCode;
}

QString ClientCode::getComputerCode() {
    return this->computerCode;
}
