#-------------------------------------------------
#
# Project created by QtCreator 2017-03-07T22:25:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ScoutAnalyzer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    entry.cpp \
    matchnumber.cpp \
    row.cpp

HEADERS  += mainwindow.h \
    entry.h \
    matchnumber.h \
    row.h

FORMS    += mainwindow.ui
