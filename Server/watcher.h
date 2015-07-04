#ifndef WATCHER_H
#define WATCHER_H

#include <QObject>
#include <QHostAddress>
#include <QMap>

#include "../resources/schedule.h"

class Watcher : public QObject
{
    Q_OBJECT

public:
    Watcher();
    //~Watcher();

signals:
    void sendSchedule(qint32 ip, Schedule find);

public slots:
    void addNewSchedule(qint32 key, Schedule neww);
    void searchSelected(qint32 key, QString date);
    void removeSchedule(qint32 key, Schedule removed);
    void onPostpone(qint32 key);

private:
    QMap <qint32, Schedule> schedules;
    QMap <qint32, qint32> postpones;
};

#endif // WATCHER_H

