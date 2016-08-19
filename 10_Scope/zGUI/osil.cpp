#include "renderarea.h"
#include "osil.h"
#include <QtWidgets>
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

osil::osil(QVector<int> *data)
{
    serial = new QSerialPort(this);
    x = 0;
    openSerialPort();
    turn = find_backR;
    adc_data = data;
    connect(serial,SIGNAL(readyRead()),this,SLOT(readData()));
}

bool osil::openSerialPort()
{
    serial->setPortName(port_name);
    serial->setBaudRate(baud_rate);
    serial->setDataBits(data_bits);
    serial->setParity(parity);
    serial->setStopBits(stop_bits);
    serial->setStopBits(stop_bits);
    serial->setFlowControl(flow_control);
    if (serial->open(QIODevice::ReadWrite))
    {
        return true;
    }
    else
    {
        return false;
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
    switch (turn)
    {
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
            break;
    }
    (*adc_data)[x] = voltage/4096.0 * 350.0;
    if(x>173)
    {
        x=0;
    }
    else
    {
        x++;
    }
}

osil::~osil()
{
    if(serial->isOpen())
        closeSerialPort();
}

