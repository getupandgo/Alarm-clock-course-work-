#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QMessageBox>

#include "connectiondialog.h"
#include "showschedules.h"
#include "newschedule.h"
#include "statistics.h"
#include "alarmwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void newConnection(QString ip, int port);
    //from gui to server
    void newSchedule(Schedule created);
    void dateRequested(QString date);
    void onPostpone();
    void scheduleRemoved(Schedule removed);
    void getStatistic();

    //from server to gui
    void displaySchedule(Schedule received);

public slots:
    void displayAlarm();

private slots:
    void onNewScheduleAction();
    void onShowSchedulesAction();
    void onStatisticsAction();

private:
    void createTrayMenu();

    Ui::MainWindow *ui;
    QSystemTrayIcon *trayIcon = NULL;
    AlarmWidget *alarm = NULL;

public:
    ConnectionDialog *chooseServer = NULL;

};

#endif // MAINWINDOW_H
