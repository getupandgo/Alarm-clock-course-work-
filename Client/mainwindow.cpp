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
    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    trayMenu->addAction(exitAction);

    trayIcon->setContextMenu(trayMenu);

    trayIcon->setIcon(QIcon(":/trayicon.png"));

    trayIcon->setToolTip("Alarm Clock");

    trayIcon->show();
    trayIcon->showMessage("Alarm Clock", "Program is in the tray now");
}

void MainWindow::onShowSchedulesAction()
{
    showschedules *showSchedulesWidget = new showschedules();
    showSchedulesWidget->show();
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

    connect(newScheduleWidget, SIGNAL(newScheduleCreated(schedule)),
            this, SIGNAL(newSchedule(schedule)));

}

MainWindow::~MainWindow()
{
    //delete newScheduleWidget;
    delete trayIcon;
    delete ui;
}
