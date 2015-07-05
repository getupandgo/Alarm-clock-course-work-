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

}

void ShowSchedules::onChangeButtonClicked()
{
    QList <QListWidgetItem*> items = ui->alarmList->selectedItems();
    if(items.isEmpty()) return;

    QListWidgetItem *selected;

    foreach(selected, items){
        NewSchedule *newScheduleWidget = new NewSchedule();

        QStringList splittedRepeat = selected->text().split(" ");
        QString stringDate = selected->text().left(5);
        int hh = stringDate.left(2).toUInt();
        int mm = stringDate.right(2).toUInt();

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
    QList <QListWidgetItem *> items = ui->alarmList->selectedItems();
    if(items.isEmpty()) return;

    for(int i = 0; i < items.size(); ++i){
        //
    }
    //QString name = ui->alarmList->selectedItems();
    //send to server to delete
    /*
    QList <QListWidgetItem*> list = ui->alarmList->findItems(name, Qt::MatchFixedString);
    int row = ui->alarmList->row(list.first());
    QListWidgetItem* item = ui->alarmList->takeItem(row);

    delete item;
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
