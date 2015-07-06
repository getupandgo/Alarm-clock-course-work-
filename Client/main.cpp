#include <QApplication>

#include "controller.h"
/*
Вариант №19
Программный продукт: "Будильник".

Обеспечить выполнение следующих функций:
•Установка будильника на указанное время с возможностью одноразового включения, ежедневного включения или включения по определенным дням недели.
•Выдача оповещения о наступлении ранее заданного времени с возможностью отключить будильник или отложить время его срабатывания на 10 минут.
•Выбор скниов, включающих в себя картинку, отображаемую в главном окне, и расположение элементов управления (0).
•Ведение и отображение статистики, когда и на какое время устанавливали будильник и сколько раз выбирали опцию
"отложить на 10 минут" (1).

Если значение параметра равно нулю, то соответствующая данному параметру функциональность реализуется полностью на
серверной стороне, т.е. и ввод данных, и их обработка, и их вывод на экран встраиваются непосредственно в
программу-сервер. Если значение параметра равно единице, то соответствующая ему функциональность разделяется между
клиентом и сервером, а именно в клиентской программе осуществляется ввод и вывод данных, а их обработка и получение
дополнительной необходимой информации из файлов осуществляется на сервере.
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Controller cc;

    return a.exec();
}
