#include "nushabe.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Nushabe w;
    w.show();

    return a.exec();
}
