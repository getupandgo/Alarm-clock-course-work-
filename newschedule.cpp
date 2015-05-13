#include "newschedule.h"
#include "ui_newschedule.h"

newschedule::newschedule(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newschedule)
{
    ui->setupUi(this);

    ui->dateEdit->setDate(QDate::currentDate());
    ui->timeEdit->setTime(QTime::currentTime());

    connect(ui->acceptButton, SIGNAL(clicked()),
            this, SLOT(onAcceptButtonClicked()));
}

void newschedule::onAcceptButtonClicked(){
    QString time = ui->timeEdit->time().toString(); //22:30:01
    QString date = ui->dateEdit->date().toString();
    QString date = ui->dateEdit->date().toString();
    QString repeat = ui->repeatBox->currentText();
    ui->label->setText(time);
    ui->label_2->setText(repeat);
    ui->label_3->setText(date);
}

newschedule::~newschedule()
{
    delete ui;
}
