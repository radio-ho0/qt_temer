#-------------------------------------------------
#
# Project created by QtCreator 2015-10-10T20:00:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tem_reader
TEMPLATE = app

include(qextserialport/qextserialport.pri)


SOURCES += main.cpp\
        temreader.cpp \
    parsetempr.cpp

HEADERS  += temreader.h \
    parsetempr.h

FORMS    += temreader.ui
