#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QString>

struct Schedule{
    QString time;
    QString date;
    QString repeat;

    Schedule();
    Schedule(QString time, QString date, QString repeat);
};

#endif // SCHEDULE_H
