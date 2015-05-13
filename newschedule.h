#ifndef NEWSCHEDULE_H
#define NEWSCHEDULE_H

#include <QWidget>
#include <QDate>
#include <QTime>
#include <QDebug>

namespace Ui {
class newschedule;
}

class newschedule : public QWidget
{
    Q_OBJECT

public:
    explicit newschedule(QWidget *parent = 0);
    void setDate(QDate date);
    void setTime(QTime time);
    void setRepeat(QString variant);
    ~newschedule();

private slots:
    void onAcceptButtonClicked();
private:
    Ui::newschedule *ui;
};

#endif // NEWSCHEDULE_H
