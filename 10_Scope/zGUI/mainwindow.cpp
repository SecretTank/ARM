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
}

void MainWindow::update_osil()
{
    int last_y;
    last_y = adc_data[x];
    adc_data[x] = voltage/4096.0 * 350.0;
    renderArea->setCoordinate(x,adc_data[x],last_y);
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

