#include "mainwindow.h"
#include "osil.h"
#include <pthread.h>
#include <QApplication>
#include <unistd.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    osil *device = new osil(&(w.adc_data));
    device->openSerialPort();
    printf("we are inside thread\n");

    /*pthread_t serial_thread;
    if(pthread_create(&serial_thread, NULL, serial_main, &(w.adc_data)))
    {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }*/

    w.show();

    return a.exec();
}

void *serial_main(void *arg)
{
    oscope_data *adc_data = (oscope_data *)arg;
    osil *device = new osil(adc_data);
    device->openSerialPort();
    printf("we are inside thread\n");
}
