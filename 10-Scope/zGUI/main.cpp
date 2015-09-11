#include "osil.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    osil w;
    w.show();

    return a.exec();
}
