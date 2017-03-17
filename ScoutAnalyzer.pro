#-------------------------------------------------
#
# Project created by QtCreator 2017-03-07T22:25:40
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ScoutAnalyzer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    entry.cpp \
    matchnumber.cpp \
    csvfile.cpp \
    parseexception.cpp \
    messageview.cpp \
    teamlistview.cpp \
    teamlistdatamodel.cpp \
    entrydatastore.cpp

HEADERS  += mainwindow.h \
    entry.h \
    matchnumber.h \
    csvfile.h \
    parseexception.h \
    messageview.h \
    teamlistview.h \
    teamlistdatamodel.h \
    entrydatastore.h

FORMS    += mainwindow.ui \
    messageview.ui \
    teamlistview.ui
