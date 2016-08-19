#include "mainwindow.h"
#include "osil.h"
#include <pthread.h>
#include <QApplication>
#include <unistd.h>

void *serial_main(void *arg);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    pthread_t serial_thread;
    if(pthread_create(&serial_thread, NULL, serial_main, &(w.adc_data)))
    {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

    w.show();

    return a.exec();
}

void *serial_main(void *arg)
{
    QVector<int> *adc_data = (QVector<int> *)arg;
    osil *device = new osil(adc_data);
    printf("we are inside thread\n");
    while (true)
    {
        sleep(1);
        printf("we are inside thread\n");
    }
}
