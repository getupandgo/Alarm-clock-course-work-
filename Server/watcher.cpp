#include "watcher.h"

Watcher::Watcher()
{
    //work with files
}

void Watcher::addNewSchedule(qint32 key, Schedule neww)
{
    schedules.insertMulti(key, neww);
    //emit startCount()
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
