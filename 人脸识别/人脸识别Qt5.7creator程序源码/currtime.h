#ifndef CURRTIME_H
#define CURRTIME_H

#include <QDateTime>
#include <QString>

class CurrTime : public QObject
{
public:
    static QString currentDateTime()
    {
        QDateTime TimeNow;
        return TimeNow.currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+": ";
    }

};

#endif // CURRTIME_H
