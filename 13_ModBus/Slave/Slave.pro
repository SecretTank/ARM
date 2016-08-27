#-------------------------------------------------
#
# Project created by QtCreator 2016-08-26T15:42:52
#
#-------------------------------------------------

QT += serialbus serialport widgets

TARGET = modbusslave
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
        settingsdialog.cpp

HEADERS  += mainwindow.h settingsdialog.h

FORMS    += mainwindow.ui settingsdialog.ui

RESOURCES += slave.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/serialbus/modbus/slave
INSTALLS += target