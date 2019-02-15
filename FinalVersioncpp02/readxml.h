#ifndef READXML_H
#define READXML_H
#include "groupinfo.h"
#include <QList>
#include <QFile>
#include <QDomDocument>

class ReadXML
{
public:
     bool getInformation(QList<GroupInfo*>** groups);
public:
    ReadXML(const QString filePath);
    ~ReadXML();
private:
    QFile* file;
    QDomDocument* doc;
};

#endif // READXML_H
