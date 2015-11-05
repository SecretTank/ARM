#include "transmission.h"
#include <string.h>

#define JOYSTICK_DELAY 1000

Transmission::Transmission(QObject *parent) : QObject(parent)
{
    //init
    charBuffer = '0';
    isBufferEmpty = true;

    connect(&tcpClient, SIGNAL(connected()), this, SLOT(connected()));
    connect(&tcpClient, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
    bufferTimer = new QTimer;
    connect(bufferTimer, SIGNAL(timeout()), this, SLOT(sendBuffer()));
    bufferTimer->setInterval(JOYSTICK_DELAY);
}

void Transmission::morabaaSlot()
{
    message = "morabaa";
    startTransfer(message.toUtf8().data());
}

void Transmission::mosalasSlot()
{
    message = "mosalas";
    startTransfer(message.toUtf8().data());
}

void Transmission::dayereSlot()
{
    message = "dayere";
    startTransfer(message.toUtf8().data());
}

void Transmission::zarbdarSlot()
{
    message = "zarbdar";
    startTransfer(message.toUtf8().data());
}

Transmission::~Transmission()
{
    tcpClient.close();
}

void Transmission::startTransfer(char* command)
{
    int bytesToWrite = tcpClient.write(command);
}

void Transmission::displayError(QAbstractSocket::SocketError socketError)
{
    if (socketError == QTcpSocket::RemoteHostClosedError)
        return;

    qDebug() << tr("Network error") << tr("The following error occurred: %1.").arg(tcpClient.errorString());
    tcpClient.close();
    emit errorConnection();
    //clientStatusLabel->setText(tr("Client ready"));
    //startButton->setEnabled(true);
}

void Transmission::connected()
{
    qDebug() << "connected";
}

void Transmission::start(QString IP)
{
    tcpClient.connectToHost(QHostAddress(IP), 7778 );
    qDebug() << "connecting to " << IP;
}

void Transmission::sendJoystick(QString key)
{
    if (isBufferEmpty)
    {
        charBuffer = key.toUtf8().data()[0];
        isBufferEmpty = false;
        bufferTimer->start();
    }
    else
    {
        charBuffer = key.toUtf8().data()[0];
    }
}

void Transmission::sendBuffer()
{
    char sendBuffer[10];
    qDebug() << "Joystick: " << charBuffer;
    sprintf(sendBuffer,"%c", charBuffer);
    startTransfer(sendBuffer);
}

void Transmission::stopJoystick()
{
    bufferTimer->stop();
    isBufferEmpty = true;
}
