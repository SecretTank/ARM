#-------------------------------------------------
#
# Project created by QtCreator 2015-09-09T15:00:05
#
#-------------------------------------------------

QT       += core gui
QT += widgets serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = oscilloscop
TEMPLATE = app


SOURCES += main.cpp\
        osil.cpp \
    renderarea.cpp

HEADERS  += osil.h \
    renderarea.h
