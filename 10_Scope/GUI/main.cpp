#include "mainwindow.h"
#include <pthread.h>
#include <QApplication>
#include <unistd.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    printf("we are inside thread\n");

    w.show();

    return a.exec();
}
