#include <QCoreApplication>
#include "modbus.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ModBus modbus;

    return a.exec();
}
