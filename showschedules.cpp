#include "showschedules.h"
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
    ui->dataLabel->setText("Schedule on " + selected.toString() + " ");

    //implement send data to the server/controller
    //implement empty schedule
}

void showschedules::onChangeButtonClicked()
{
    if(ui->alarmList->selectedItems().isEmpty()) return;
}

void showschedules::onDeleteButtonClicked()
{
    if(ui->alarmList->selectedItems().isEmpty()) return;

    //QList <QListWidgetItem*> list = ui->alarmList->findItems(name, Qt::MatchFixedString);
    //int row = ui->alarmList->row(list.first());
    //QListWidgetItem* item = ui->alarmList->takeItem(row);

    //delete item;
}


showschedules::~showschedules()
{
    delete ui;
}
