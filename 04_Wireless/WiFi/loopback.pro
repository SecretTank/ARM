QT += network widgets

HEADERS       = \
    mainwindow.h
SOURCES       = \
                main.cpp \
    mainwindow.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/network/loopback
INSTALLS += target
