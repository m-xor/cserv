#-------------------------------------------------
#
# Project created by QtCreator 2021-01-21T18:34:48
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cserv
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    devicesec.cpp \
    commands.cpp \
    credential.cpp \
    button.cpp \
    config.cpp \
    devicewidg.cpp

HEADERS  += mainwindow.h \
    devicesec.h \
    commands.h \
    credential.h \
    button.h \
    config.h \
    devicewidg.h

FORMS    += mainwindow.ui

