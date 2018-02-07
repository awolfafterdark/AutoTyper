#-------------------------------------------------
#
# Project created by QtCreator 2014-10-02T20:42:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AutoTyper
TEMPLATE = app


SOURCES += main.cpp\
        autotyperwindow.cpp \
    keyboard.cpp \
    advancedwindow.cpp

HEADERS  += autotyperwindow.h \
    keyboard.h \
    advancedwindow.h

FORMS    += autotyperwindow.ui \
    advancedwindow.ui
