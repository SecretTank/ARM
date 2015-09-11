#include "renderarea.h"
#include "osil.h"
#include <unistd.h>
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
    shapeComboBox = new QComboBox;
    shapeComboBox->addItem(tr("Ellipse"), RenderArea::Ellipse);
    shapeComboBox->addItem(tr("Points"), RenderArea::Points);
    shapeLabel = new QLabel(tr("&Shape:"));
    shapeLabel->setBuddy(shapeComboBox);
    status = new QLabel("disconnected!");

    for(int i = 0 ; y.size() ; i++){
        y.push_back(0);
        renderArea->setCoordinate(y);
    }
    connect(shapeComboBox, SIGNAL(activated(int)),
            this, SLOT(shapeChanged()));
    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->addWidget(renderArea, 0, 0, 1, 4);
    mainLayout->addWidget(shapeLabel, 2, 0, Qt::AlignLeft);
    mainLayout->addWidget(shapeComboBox, 2, 1);
    mainLayout->addWidget(status, 3 , 0);
    setLayout(mainLayout);

    shapeChanged();
    brushChanged();
    setWindowTitle(tr("** MY OSIL **"));
    openSerialPort();
    turn = find_backR;
    connect(serial,SIGNAL(readyRead()),this,SLOT(readData()));
}

void osil::shapeChanged()
{
    RenderArea::Shape shape = RenderArea::Shape(shapeComboBox->itemData(
            shapeComboBox->currentIndex(), Qt::UserRole).toInt());
    renderArea->setShape(shape);
}

void osil::brushChanged()
{
        QLinearGradient linearGradient(0, 0, 100, 100);
        linearGradient.setColorAt(0.0, Qt::white);
        linearGradient.setColorAt(0.2, Qt::green);
        linearGradient.setColorAt(1.0, Qt::black);
        renderArea->setBrush(linearGradient);
}

void osil::update_osil()
{
        if(y.size()>175)
            y.pop_front();
        y.push_back(voltage/4096.0 * 350.0);
        renderArea->setCoordinate(y);
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

