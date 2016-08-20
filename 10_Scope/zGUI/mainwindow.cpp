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
    renderArea = new RenderArea;
    status = new QLabel("disconnected!");
    mainWidget = new QWidget;
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(renderArea);
    mainLayout->addWidget(status);
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
    setWindowTitle("** MY OSIL **");
    adc_data.data = QVector<int> (200);
    x = 0;
    update_timer = new QTimer;
    adc_data.buffer = 0;
    connect(update_timer,SIGNAL(timeout()),this,SLOT(update_osil()));
    update_timer->start(30);
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

MainWindow::~MainWindow()
{
    //device->closeSerialPort();
}

