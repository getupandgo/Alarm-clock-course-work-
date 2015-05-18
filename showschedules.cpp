#include "showschedules.h"
#include "newschedule.h"
#include "ui_showschedules.h"

showschedules::showschedules(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::showschedules)
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

void showschedules::onSelectionChanged()
{
    QDate selected = ui->calendarWidget->selectedDate();

    //implement send data to the server/controller

    if(!packet.isNull())
        ui->dataLabel->setText("Schedule on " + selected.toString(Qt::ISODate) + ": ");
    else
        ui->dataLabel->setText("No schedules on " + selected.toString(Qt::ISODate) + ".");
}

void showschedules::onChangeButtonClicked()
{
    if(ui->alarmList->selectedItems().isEmpty()) return;

    newschedule *newScheduleWidget = new newschedule();

    //newScheduleWidget->setTime();
    //newScheduleWidget->setDate();
    //newScheduleWidget->setRepeat();

    newScheduleWidget->show();

    delete newScheduleWidget;
}

void showschedules::onDeleteButtonClicked()
{
    QList <QWidgetItem *> items = ui->alarmList->selectedItems();
    if(items.isEmpty()) return;

    for(int i = 0; i < items.size(); ++i){
        //
    }
    //QString name = ui->alarmList->selectedItems();
    //send to server to delete
    QList <QListWidgetItem*> list = ui->alarmList->findItems(name, Qt::MatchFixedString);
    int row = ui->alarmList->row(list.first());
    QListWidgetItem* item = ui->alarmList->takeItem(row);

    delete item;
}


showschedules::~showschedules()
{
    delete ui;
}
