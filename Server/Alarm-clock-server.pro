#-------------------------------------------------
#
# Project created by QtCreator 2015-06-04T18:13:28
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = Alarm-clock-server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    clientconnection.cpp \
    ../resources/schedule.cpp \
    tcp_server.cpp \
    watcher.cpp

HEADERS += \
    clientconnection.h \
    ../resources/packet.h \
    ../resources/schedule.h \
    tcp_server.h \
    watcher.h
