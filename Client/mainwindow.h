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
    void newSchedule(Schedule created);
    void dateRequested(QString date);

    void displaySchedule(Schedule received);

private slots:
    void onNewScheduleAction();
    void onShowSchedulesAction();
    void onStatisticsAction();

private:
    void createTrayMenu();

    Ui::MainWindow *ui;
    QSystemTrayIcon *trayIcon = NULL;

public:
    ConnectionDialog *chooseServer;

};

#endif // MAINWINDOW_H
