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
    status = new QLabel("  Disconnected");
    status->setStyleSheet("color: #fff");
    mainWidget = new QWidget;
    mainWidget->setStyleSheet("background-color: #2f343f");
    mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->addWidget(renderArea);
    mainLayout->addWidget(status);
    mainLayout->addSpacing(5);
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
    setWindowTitle("Osciloscope");
    adc_data.data = QVector<int> (screen_res+10);
    x = 0;
    update_timer = new QTimer;
    adc_data.buffer = 0;
    connect(update_timer,SIGNAL(timeout()),this,SLOT(update_osil()));

    update_timer->start(30);

    connect_timer = new QTimer;
    connect(connect_timer,SIGNAL(timeout()),this,SLOT(try_connect()));
    connect_timer->start(300);


}

void MainWindow::update_osil()
{
    renderArea->update();
}

void MainWindow::try_connect()
{
    if (device->openSerialPort())
    {
        connect_timer->stop();
        status->setText("  Connected");
    }
}

MainWindow::~MainWindow()
{
    device->closeSerialPort();
}

