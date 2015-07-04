#ifndef NEWSCHEDULE_H
#define NEWSCHEDULE_H

#include <QWidget>
#include <QDate>
#include <QTime>
#include <QDebug>

#include "../resources/schedule.h"

namespace Ui {
class NewSchedule;
}

class NewSchedule : public QWidget
{
    Q_OBJECT

public:
    explicit NewSchedule(QWidget *parent = 0);
    void setDate(QDate date);
    void setTime(QTime time);
    void setRepeat(QString variant);
    ~NewSchedule();

signals:
    void newScheduleCreated(schedule created);

private slots:
    void onAcceptButtonClicked();

private:
    Ui::NewSchedule *ui;
};

#endif // NEWSCHEDULE_H
