#include "mainwindow.h"

#include "renderarea.h"
#include "osil.h"
#include <string>
#include <math.h>
#include <QtSerialPort/QSerialPort>
#include <QDebug>

#define port_name       "ttyUSB0"
#define baud_rate       QSerialPort::Baud9600
#define data_bits       QSerialPort::Data8
#define parity          QSerialPort::NoParity
#define stop_bits       QSerialPort::OneStop
#define flow_control    QSerialPort::NoFlowControl

#define find_backR      0
#define get_first_char  1
#define get_sec_char    2


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    device = new osil(&(adc_data));
    renderArea = new RenderArea(&(adc_data));
    status = new QLabel("Disconnected");
    mainWidget = new QWidget;
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(renderArea);
    mainLayout->addWidget(status);
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
    setWindowTitle("Osciloscope");
    adc_data.data = QVector<int> (200);
    x = 0;
    update_timer = new QTimer;
    adc_data.buffer = 0;
    connect(update_timer,SIGNAL(timeout()),this,SLOT(update_osil()));

    update_timer->start(50);
    connect(update_timer,SIGNAL(timeout()),this,SLOT(try_connect()));

    connect_timer = new QTimer;
    connect_timer->start(300);

}

void MainWindow::update_osil()
{
    for (; adc_data.buffer > 0 ; adc_data.buffer--)
    {
        renderArea->addPoint(x,adc_data.data[x]);
        if(x>sceen_size)
        {
            x=0;
        }
        else
        {
            x++;
        }

    }
    renderArea->update();
}

void MainWindow::try_connect()
{
    if (device->openSerialPort())
    {
        connect_timer->stop();
        status->setText("Connected");
    }
}

MainWindow::~MainWindow()
{
    device->closeSerialPort();
}

