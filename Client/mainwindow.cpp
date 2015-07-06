#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->createTrayMenu();

    chooseServer = new ConnectionDialog;
    chooseServer->show();

    connect(chooseServer, SIGNAL(newConnection(QString, int)),
            this, SIGNAL(newConnection(QString, int)));

}

void MainWindow::createTrayMenu()
{
    trayIcon = new QSystemTrayIcon(this);

    if(!trayIcon->isSystemTrayAvailable())
    {
        QMessageBox msgBox;
        msgBox.setText(tr("System tray is unavailable!"));
        msgBox.exec();

        trayIcon = NULL;

        return;
    }

    QMenu *trayMenu = new QMenu;

    QAction *newScheduleAction = new QAction(tr("New schedule"), this);
    connect(newScheduleAction, SIGNAL(triggered()),
            this, SLOT(onNewScheduleAction()));
    trayMenu->addAction(newScheduleAction);

    QAction *showSchedulesAction = new QAction(tr("Show all shedules"), this);
    connect(showSchedulesAction, SIGNAL(triggered()),
            this, SLOT(onShowSchedulesAction()));
    trayMenu->addAction(showSchedulesAction);

    trayMenu->addSeparator();

    QAction *statisticsAction = new QAction(tr("Statistics"), this);
    connect(statisticsAction, SIGNAL(triggered()),
            this, SLOT(onStatisticsAction()));
    trayMenu->addAction(statisticsAction);

    trayMenu->addSeparator();

    QAction *exitAction = new QAction(tr("Exit"), this);
    connect(exitAction, SIGNAL(triggered()),
            qApp, SLOT(quit()));
    trayMenu->addAction(exitAction);

    trayIcon->setContextMenu(trayMenu);

    trayIcon->setIcon(QIcon(":/trayicon.png"));

    trayIcon->setToolTip("Alarm Clock");

    trayIcon->show();
    trayIcon->showMessage("Alarm Clock", "Program is in the tray now");
}

void MainWindow::onShowSchedulesAction()
{
    ShowSchedules *showSchedulesWidget = new ShowSchedules();
    showSchedulesWidget->show();

    //signals to pass data to controller from widget through mainwindow
    connect(showSchedulesWidget, SIGNAL(dateRequested(QString)),
            this, SIGNAL(dateRequested(QString)));
    connect(showSchedulesWidget, SIGNAL(removeSchedule(Schedule)),
            this, SIGNAL(scheduleRemoved(Schedule)));

    //signals to pass data from controller to widget through mainwindow
    connect(this, SIGNAL(displaySchedule(Schedule)),
            showSchedulesWidget, SLOT(onScheduleReceived(Schedule)));

}

void MainWindow::onStatisticsAction()
{
    statistics *statisticsWidget = new statistics();
    statisticsWidget->show();
}

void MainWindow::onNewScheduleAction()
{
    NewSchedule *newScheduleWidget = new NewSchedule();
    newScheduleWidget->show();

    connect(newScheduleWidget, SIGNAL(newScheduleCreated(Schedule)),
            this, SIGNAL(newSchedule(Schedule)));
}

void MainWindow::displayAlarm()
{
    AlarmWidget *alarm = new AlarmWidget();
    alarm->show();

    connect(alarm, SIGNAL(postpone()),
            this, SIGNAL(onPostpone()));
}

MainWindow::~MainWindow()
{
    delete trayIcon;
    delete ui;
}
