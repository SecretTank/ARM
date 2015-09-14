#include "renderarea.h"
#include "osil.h"
#include <QtWidgets>
#include <string>
#include <math.h>
#include <QtSerialPort/QSerialPort>
#include <QDebug>

#define port_name "ttyUSB0"
#define baud_rate  QSerialPort::Baud9600
#define data_bits QSerialPort::Data8
#define parity QSerialPort::NoParity
#define stop_bits QSerialPort::OneStop
#define flow_control QSerialPort::NoFlowControl

#define find_backR 0
#define get_first_char 1
#define get_sec_char 2

osil::osil()
{
    serial = new QSerialPort(this);
    renderArea = new RenderArea;
    status = new QLabel("disconnected!");
    QGridLayout *mainLayout = new QGridLayout;
    x = 0;
    y = QVector<int> (200);

    mainLayout->addWidget(renderArea, 0, 0, 1, 4);
    mainLayout->addWidget(status, 3 , 0);
    setLayout(mainLayout);
    setWindowTitle(tr("** MY OSIL **"));
    openSerialPort();
    turn = find_backR;
    connect(serial,SIGNAL(readyRead()),this,SLOT(readData()));
}

void osil::update_osil()
{
    int last_y;
    last_y = y[x];
    y[x] = voltage/4096.0 * 350.0;
    renderArea->setCoordinate(x,y[x],last_y);
    if(x>173)
        x=0;
    else
        x++;
}

void osil::openSerialPort()
{
    serial->setPortName(port_name);
    serial->setBaudRate(baud_rate);
    serial->setDataBits(data_bits);
    serial->setParity(parity);
    serial->setStopBits(stop_bits);
    serial->setStopBits(stop_bits);
    serial->setFlowControl(flow_control);
    if (serial->open(QIODevice::ReadWrite)) {
        status->setText("connected!");
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());
        status->setText("disconnected!");
    }
}

void osil::closeSerialPort()
{
    if (serial->isOpen())
        serial->close();
}

void osil::readData()
{
    QByteArray data;
    data = serial->read(1);
    switch (turn) {
    case find_backR:
        voltage = 0;
        if(data.at(0) == '\r')
            turn = get_first_char;
        break;
    case get_first_char:
        voltage = data.at(0);
        turn = get_sec_char;
        break;
    case get_sec_char:
        voltage += data.at(0)*256;
        turn = find_backR;
        qDebug()<<voltage;
        update_osil();
        break;
    }
}

osil::~osil()
{
    if(serial->isOpen())
        closeSerialPort();
}

