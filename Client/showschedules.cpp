#include "showschedules.h"
#include "newschedule.h"
#include "ui_showschedules.h"

ShowSchedules::ShowSchedules(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowSchedules)
{
    ui->setupUi(this);

    connect(ui->calendarWidget, SIGNAL(selectionChanged()),
            this, SLOT(onSelectionChanged()));

    connect(ui->changeButton, SIGNAL(clicked()),
            this, SLOT(onChangeButtonClicked()));

    connect(ui->deleteButton, SIGNAL(clicked()),
            this, SLOT(onDeleteButtonClicked()));

    ui->dataLabel->setText("Choose date to see schedule");
}

void ShowSchedules::onSelectionChanged()
{
    QDate selected = ui->calendarWidget->selectedDate();

    emit dateRequested(selected.toString(Qt::ISODate));

    ui->dataLabel->setText("No schedules on " + selected.toString(Qt::ISODate) + ".");

    ui->alarmList->clear();

}

void ShowSchedules::onChangeButtonClicked()
{
    QList <QListWidgetItem*> items = ui->alarmList->selectedItems();
    if(items.isEmpty()) return;

    QListWidgetItem *selected;

    foreach(selected, items){
        NewSchedule *newScheduleWidget = new NewSchedule();

        QStringList splittedRepeat = selected->text().split(" ");
        QString stringTime = selected->text().left(5);
        int hh = stringTime.left(2).toUInt();
        int mm = stringTime.right(2).toUInt();

        QDate currentDate = ui->calendarWidget->selectedDate();
        QString currentRepeat = splittedRepeat.at(3);

        newScheduleWidget->setWindowTitle("Change schedule");
        newScheduleWidget->setTime(QTime(hh,mm));
        newScheduleWidget->setDate(currentDate);
        newScheduleWidget->setRepeat(currentRepeat);

        newScheduleWidget->show();
    }

}

void ShowSchedules::onDeleteButtonClicked()
{
    QList <QListWidgetItem*> items = ui->alarmList->selectedItems();
    if(items.isEmpty()) return;

    QListWidgetItem *selected;

    foreach(selected, items)
    {
        QStringList splittedRepeat = selected->text().split(" ");

        QString currentTime = selected->text().left(5);
        QDate currentDate = ui->calendarWidget->selectedDate();
        QString currentRepeat = splittedRepeat.at(3);

        Schedule deleted(currentTime,
                 currentDate.toString(Qt::ISODate),
                 currentRepeat);

        int row = ui->alarmList->row(items.first());
        QListWidgetItem* item = ui->alarmList->takeItem(row);

        delete item;

        emit removeSchedule(deleted);
    }
    //QString name = ui->alarmList->selectedItems();
    //send to server to delete
    /*
    QList <QListWidgetItem*> list = ui->alarmList->findItems(name, Qt::MatchFixedString);

    */
}

void ShowSchedules::onScheduleReceived(Schedule received)
{
    ui->dataLabel->setText("Schedule on " + received.date + ": ");

    ui->alarmList->addItem(received.time + "   " + received.repeat + " repeating");
}


ShowSchedules::~ShowSchedules()
{
    delete ui;
}
