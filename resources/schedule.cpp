#include "schedule.h"

Schedule::Schedule()
{
}

Schedule::Schedule(QString time, QString date, QString repeat) : time(time), date(date), repeat(repeat)
{
}

bool Schedule::operator == (const Schedule rvalue)
{
    if(this->date == rvalue.date &&
       this->time == rvalue.time &&
       this->repeat == rvalue.repeat)
        return 1;
    else
        return 0;
}
