#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

    QAction *newSheduleAction = new QAction(tr("New schedule"), this);
    //connect(newSheduleAction, SIGNAL(triggered()), this, SLOT(hide()));
    trayMenu->addAction(newSheduleAction);

    QAction *showShedulesAction = new QAction(tr("Show all shedules"), this);
    //connect(showShedulesAction, SIGNAL(triggered()), this, SLOT(hide()));
    trayMenu->addAction(showShedulesAction);

    trayMenu->addSeparator();

    QAction *statisticsAction = new QAction(tr("Statistics"), this);
    //connect(statisticsAction, SIGNAL(triggered()), this, SLOT(hide()));
    trayMenu->addAction(statisticsAction);

    trayMenu->addSeparator();

    QAction *exitAction = new QAction(tr("Exit"), this);
    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    trayMenu->addAction(exitAction);

    trayIcon->setContextMenu(trayMenu);
    trayIcon->setIcon(QIcon("D:/GitHub/course_work_alarm_clock/images/trayicon.png"));
    //trayIcon->setIcon(QIcon(":/images/trayicon.png"));
    //trayIcon->setIcon(QIcon(":/images/colorful.svg"));
    trayIcon->setToolTip("Alarm Clock");

    trayIcon->show();
    trayIcon->showMessage("Alarm Clock", "Program is in the tray now");
}

MainWindow::~MainWindow()
{
    delete ui;
}
