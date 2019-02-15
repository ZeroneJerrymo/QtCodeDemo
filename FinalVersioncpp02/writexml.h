#ifndef WRITEXML_H
#define WRITEXML_H
#include <QList>
#include <groupinfo.h>

class WriteXML
{
public:
    WriteXML();
    void writeInformation(QList<GroupInfo*>* groups);
};

#endif // WRITEXML_H
