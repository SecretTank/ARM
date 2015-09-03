#-------------------------------------------------
#
# Project created by QtCreator 2015-08-23T11:26:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += bluetooth
TARGET = nushabe
TEMPLATE = app


SOURCES += main.cpp\
        nushabe.cpp

HEADERS  += nushabe.h

FORMS    += nushabe.ui

CONFIG += mobility
MOBILITY = 

