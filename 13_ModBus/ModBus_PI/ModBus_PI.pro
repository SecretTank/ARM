#-------------------------------------------------
#
# Project created by QtCreator 2016-08-28T10:46:48
#
#-------------------------------------------------

QT       += serialbus serialport core network

QT       -= gui

TARGET = ModBus_PI
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    datalink.cpp \
    modbus.cpp \
    writeregistermodel.cpp

HEADERS += \
    datalink.h \
    define.h \
    modbus.h \
    writeregistermodel.h
