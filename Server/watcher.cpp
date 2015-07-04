#include "watcher.h"

Watcher::Watcher()
{
    //work with files
}

void Watcher::addNewSchedule(qint32 key, Schedule neww)
{
    schedules.insert(key, neww);
    //emit startCount()
}

void Watcher::searchSelected(qint32 key, QString date)
{
    QMap <qint32, Schedule>::const_iterator i = schedules.find(key);
    Schedule find;
    while (i != schedules.end() && i.key() == key)
    {
        find = i.value();
        if(find.date == date)
            emit sendSchedule(key, find);
    }
}

void Watcher::removeSchedule(qint32 key, Schedule removed)
{
    //
}

void Watcher::onPostpone(qint32 key)
{
    //
}

//Watcher::~Watcher(){
    //
//}
