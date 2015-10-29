#-------------------------------------------------
#
# Project created by QtCreator 2015-10-22T11:09:57
#
#-------------------------------------------------

QT       += core gui
QT += network widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = transmission
TEMPLATE = app


SOURCES += main.cpp\
        transmission.cpp \
    client.cpp

HEADERS  += transmission.h \
    client.h

# install
target.path = $/home/esi/project/Qt/transmission
INSTALLS += target
