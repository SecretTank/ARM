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

LIBS += -lGL\
        -lGLU\
        -lglut

SOURCES += main.cpp\
        osil.cpp \
    line.cpp

HEADERS  += osil.h \
    line.h

LIBS += -lpthread
#INCLUDEPATH +=
