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
    adc_data = QVector<int> (200);
    x = 0;
    update_timer = new QTimer;
    update_timer->setInterval(1);
    connect(update_timer,SIGNAL(timeout()),this,SLOT(update_osil()));
}

void MainWindow::update_osil()
{
    renderArea->setCoordinate(x,adc_data[x]);
    if(x>173)
    {
        x=0;
    }
    else
    {
        x++;
    }
}

MainWindow::~MainWindow()
{
    //device->closeSerialPort();
}

