#include "nushabe.h"
#include "ui_nushabe.h"

Nushabe::Nushabe(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Nushabe)
{
    layout = new QVBoxLayout;
    centralWidget = new QWidget;
    dial = new QDial;
    progressbar = new QProgressBar;
    connect_btn = new QPushButton("Connect");
    exit_btn = new QPushButton("Exit");
    status = new QLabel("boom");
    btn_layout = new QHBoxLayout;

    btn_layout->addWidget(exit_btn);
    btn_layout->addWidget(connect_btn);

    layout->addWidget(dial);
    layout->addWidget(progressbar);
    layout->addWidget(status);
    layout->addLayout(btn_layout);
    setCentralWidget(centralWidget);
    centralWidget->setLayout(layout);


    //resize(200, 300);
    connect(dial,SIGNAL(sliderMoved(int)),this,SLOT(valueChangedSlot(int)));
    //QList<QBluetoothHostInfo> host;
    //QList<QBluetoothDeviceInfo> found_devices;
}

Nushabe::~Nushabe()
{
    delete ui;
}

void Nushabe::valueChangedSlot(int value){
     progressbar->setValue(value);
}

void Nushabe::startDeviceDiscovery()
{
    // Create a discovery agent and connect to its signals
    QBluetoothDeviceDiscoveryAgent *discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    connect(discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
            this, SLOT(deviceDiscovered(QBluetoothDeviceInfo)));
    discoveryAgent->start();
}


void Nushabe::deviceDiscovered(const QBluetoothDeviceInfo &device)
{
    dev_list.push_back(device);
    qDebug() << "Found new device:" << device.name() << '(' << device.address().toString() << ')' ;
    if(device.address().toString() == "98:D3:31:60:30:DF")
    {
        startClient();
    }
}

void Nushabe::startClient()
{
    //rfcommServer->serverType();
    QString uuid("00001101-0000-1000-8000-00805F9B34FB");
    QBluetoothSocket* socket=new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    socket->connectToService(QBluetoothAddress("98:D3:31:60:30:DF"),QBluetoothUuid(uuid));


    // Connection is ready to be used
    qDebug("Debug 1");
    connect(socket, SIGNAL(connected()), this, SLOT(bt_connected()));
    connect(socket, SIGNAL(disconnected()), this,SLOT(bt_disconnected()));
    connect(socket,SIGNAL(error(QBluetoothSocket::SocketError)),this,SLOT(error(QBluetoothSocket::SocketError)));
    qDebug() << "Create socket";
    qDebug() << "ConnectToService done";

    //connect(socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
}


void Nushabe::bt_connected()
{
     qDebug() << "HC-05 Connected\nSending HI!";
     socket->write("Hi\r\n");
}

void Nushabe::bt_disconnected()
{

}

void Nushabe::error(QBluetoothSocket::SocketError error_code)
{
    qDebug() <<"error is : " << error_code;
}

void Nushabe::connect_clicked()
{
    if (localDevice.isValid())
    {
        // Turn Bluetooth on
        localDevice.powerOn();
        status->setText("blue is on");
        // Make it visible to others
        localDevice.setHostMode(QBluetoothLocalDevice::HostDiscoverable);
    }
    else
    {
        status->setText("local device not supported");
    }
    startDeviceDiscovery();
}

void Nushabe::exit_clicked()
{
    exit(0);
}
