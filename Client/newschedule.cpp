#include "newschedule.h"
#include "ui_newschedule.h"

NewSchedule::NewSchedule(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewSchedule)
{
    ui->setupUi(this);

    ui->dateEdit->setDate(QDate::currentDate());
    ui->timeEdit->setTime(QTime::currentTime());

    connect(ui->acceptButton, SIGNAL(clicked()),
            this, SLOT(onAcceptButtonClicked()));

}

void NewSchedule::onAcceptButtonClicked(){
    QString time = ui->timeEdit->time().toString(); //22:30:01
    time.chop(3);
    QString date = ui->dateEdit->date().toString(Qt::ISODate);
    QString repeat = ui->repeatBox->currentText();

    Schedule created(time, date, repeat);

    emit newScheduleCreated(created);
}

void NewSchedule::setDate(QDate date)
{
    ui->dateEdit->setDate(date);
}

void NewSchedule::setTime(QTime time)
{
    ui->timeEdit->setTime(time);
}

void NewSchedule::setRepeat(QString variant)
{
    int index = ui->repeatBox->findData(variant);
    if(index != -1){
       ui->repeatBox->setCurrentIndex(index);
    }
}

NewSchedule::~NewSchedule()
{
    delete ui;
}
