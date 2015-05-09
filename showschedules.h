#ifndef SHOWSCHEDULES_H
#define SHOWSCHEDULES_H

#include <QWidget>

namespace Ui {
class showschedules;
}

class showschedules : public QWidget
{
    Q_OBJECT

public:
    explicit showschedules(QWidget *parent = 0);
    ~showschedules();

private:
    Ui::showschedules *ui;
};

#endif // SHOWSCHEDULES_H
