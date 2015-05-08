#include "newschedule.h"
#include "ui_newschedule.h"

newschedule::newschedule(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newschedule)
{
    ui->setupUi(this);
}

newschedule::~newschedule()
{
    delete ui;
}
