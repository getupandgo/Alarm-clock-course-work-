#ifndef WATCHER_H
#define WATCHER_H

#include <QObject>
#include <QHostAddress>
#include <QMap>
#include <QDateTime>
#include <QTimer>

#include "../resources/schedule.h"

class Watcher : public QObject
{
    Q_OBJECT

public:
    Watcher();
    //~Watcher();

signals:
    void sendSchedule(qint32 ip, Schedule find);
    void startWatching();
    //void sendAlarm(QString ip);
    void sendAlarm();

public slots:
    void addNewSchedule(qint32 key, Schedule newSchedule);
    void searchSelected(qint32 key, QString date);
    void removeSchedule(qint32 key, Schedule removed);
    void onPostpone(qint32 key);

private slots:
    void onStartWatching();

private:
    QMultiMap <qint32, Schedule> schedules;
    QMap <qint32, qint32> postpones;
    QList <QString> alarms;

};

#endif // WATCHER_H

