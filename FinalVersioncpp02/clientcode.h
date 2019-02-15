#ifndef CLIENTCODE_H
#define CLIENTCODE_H
#include <QString>

class ClientCode
{
private:
    QString computerCode;
public:
    ClientCode();
    void setComputerCode(QString computerCode);
    QString getComputerCode();
};

#endif // CLIENTCODE_H
