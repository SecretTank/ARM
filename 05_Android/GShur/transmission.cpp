#include "transmission.h"
#include <string.h>

Transmission::Transmission(QObject *parent) : QObject(parent)
{
    connect(&tcpClient, SIGNAL(connected()), this, SLOT(connected()));
    connect(&tcpClient, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
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
    qDebug() << bytesToWrite;
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
