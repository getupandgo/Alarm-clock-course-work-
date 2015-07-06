#-------------------------------------------------
#
# Project created by QtCreator 2015-05-07T01:14:57
#
#-------------------------------------------------

QT       += core gui widgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = course_work_alarm_clock
TEMPLATE = app


SOURCES += main.cpp \
    newschedule.cpp \
    statistics.cpp \
    mainwindow.cpp \
    showschedules.cpp \
    serverconnection.cpp \
    ../resources/schedule.cpp \
    connectiondialog.cpp \
    controller.cpp \
    alarmwidget.cpp

FORMS    += \
    newschedule.ui \
    statistics.ui \
    mainwindow.ui \
    showschedules.ui \
    connectiondialog.ui \
    alarmwidget.ui

HEADERS += \
    newschedule.h \
    statistics.h \
    mainwindow.h \
    showschedules.h \
    serverconnection.h \
    packet.h \
    ../resources/packet.h \
    ../resources/schedule.h \
    connectiondialog.h \
    controller.h \
    alarmwidget.h

RESOURCES += \
    images/images.qrc
