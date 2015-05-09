#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QMessageBox>

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

private slots:
    void onNewScheduleAction();
    void onShowSchedulesAction();
    void onStatisticsAction();

private:
    Ui::MainWindow *ui;
    QSystemTrayIcon *trayIcon;
};

#endif // MAINWINDOW_H
