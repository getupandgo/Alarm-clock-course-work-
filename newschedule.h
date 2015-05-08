#ifndef NEWSCHEDULE_H
#define NEWSCHEDULE_H

#include <QWidget>

namespace Ui {
class newschedule;
}

class newschedule : public QWidget
{
    Q_OBJECT

public:
    explicit newschedule(QWidget *parent = 0);
    ~newschedule();

private:
    Ui::newschedule *ui;
};

#endif // NEWSCHEDULE_H
