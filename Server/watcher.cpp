#include "watcher.h"

Watcher::Watcher()
{
    //work with files
}

void Watcher::addNewSchedule(qint32 key, Schedule newSchedule)
{
    if(newSchedule.repeat == "Single")
    {
        schedules.insertMulti(key, newSchedule);
    }
    else if (newSchedule.repeat == "Every day")
   {
        int day = newSchedule.date.right(2).toInt();
        QString s_day;

        for(int i = 0; i < 13; ++i)
        {
            ++day;

            s_day.setNum(day);

            if(day < 10)
                s_day.prepend("0");

            newSchedule.date.chop(2);
            newSchedule.date.append(s_day);
            schedules.insertMulti(key, newSchedule);
        }
    }
    else if(newSchedule.repeat == "On even days")
    {
        int day = newSchedule.date.right(2).toInt();
        QString s_day;

        for(int i = 0; i < 13; ++i)
        {
            ++day;

            if(day%2 == 0)
            {
                s_day.setNum(day);

                if(day < 10)
                    s_day.prepend("0");

                newSchedule.date.chop(2);
                newSchedule.date.append(s_day);
                schedules.insertMulti(key, newSchedule);
            }
        }
    }
    else if(newSchedule.repeat == "On odd days")
    {
        int day = newSchedule.date.right(2).toInt();
        QString s_day;

        for(int i = 0; i < 13; ++i)
        {
            ++day;

            if(day%2 != 0)
            {
                s_day.setNum(day);

                if(day < 10)
                    s_day.prepend("0");

                newSchedule.date.chop(2);
                newSchedule.date.append(s_day);
                schedules.insertMulti(key, newSchedule);
            }
        }
    }

    emit startWatching();
}

void Watcher::searchSelected(qint32 key, QString date)
{
    QMultiMap <qint32, Schedule>::const_iterator i = schedules.find(key);
    Schedule find;
    while (i != schedules.end() && i.key() == key)
    {
        find = i.value();
        if(find.date == date)
            emit sendSchedule(key, find);
        ++i;
    }
}

void Watcher::removeSchedule(qint32 key, Schedule removed)
{
    QList <Schedule> values = schedules.values();
    Schedule val;
    foreach(val, values){
        if(val == removed)
            schedules.remove(key, removed);
    }
}

void Watcher::onPostpone(qint32 key)
{
    ++postpones[key];
}

//Watcher::~Watcher(){
    //
//}
