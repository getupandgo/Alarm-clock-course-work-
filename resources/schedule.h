#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QString>

struct schedule{
    QString time;
    QString date;
    QString repeat;

    schedule();
    schedule(QString time, QString date, QString repeat);
};

#endif // SCHEDULE_H
