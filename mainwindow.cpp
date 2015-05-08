#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    trayIcon  = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon("D:/Studying/all_projects/Cpp_projects/course_work_alarm_clock/resources/trayicon.png"));
    trayIcon->setToolTip("Alarm Clock");

    if(!trayIcon->isSystemTrayAvailable())
    {
        QMessageBox msgBox;
        msgBox.setText("System tray is unavailable!");
        msgBox.exec();
        trayIcon = NULL;
        return;
    }
    QMenu *trayMenu = new QMenu;

    trayMenu->addAction("New schedule");
    trayMenu->addAction("Show all shedules");
    trayMenu->addSeparator();
    trayMenu->addAction("Statistics");
    trayMenu->addSeparator();
    trayMenu->addAction("Exit");

    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();
    trayIcon->showMessage("AlarmClock","Program is in the tray now");
}

MainWindow::~MainWindow()
{
    delete ui;
}
