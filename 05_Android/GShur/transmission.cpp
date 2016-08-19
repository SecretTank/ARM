#include "transmission.h"
#include <string.h>

#define JOYSTICK_DELAY 100

Transmission::Transmission(QObject *parent) : QObject(parent)
{
    //init
    charBuffer = '0';
    isBufferEmpty = true;
    commandMode=false;

    connect(&tcpClient, SIGNAL(connected()), this, SLOT(connected()));
    connect(&tcpClient, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
    bufferTimer = new QTimer;
    bufferTimer->setSingleShot(true);
    connect(bufferTimer, SIGNAL(timeout()), this, SLOT(sendBuffer()));
    bufferTimer->setInterval(JOYSTICK_DELAY);
}

//If rectangle press controller goes to command mode
//in command mode two key recieve and iterpreted a command
//and generate commandByte as follow list
//Key           Dec Binary
//Triangle  =   1   01
//Circle    =   2   10
//Cross     =   3   11


void Transmission::morabaaSlot()
{
    if(stack.size() == 1)
        return;
    stack.push_back("morabaa");
    code = 0xff0;
    //startTransfer(stack.toUtf8().data());
}

void Transmission::mosalasSlot()
{

    message = "k";
    commandMode=true;
    commandIndex=0;
    startTransfer(message.toUtf8().data());
}

/*void Transmission::mosalasSlot()
{
    message = "s";
    startTransfer(message.toUtf8().data());
    /*if (!commandMode)
    {
        message = "s";
        startTransfer(message.toUtf8().data());
    }
    else
    {
        commandByte |= 3 << commandIndex;
        if (commandIndex < 2)
        {
            commandIndex++;
        }
    }*/
//}

void Transmission::dayereSlot()
{

    message = "z";
    startTransfer(message.toUtf8().data());
}

void Transmission::zarbdarSlot()
{
    message = "t";
    startTransfer(message.toUtf8().data());
}

Transmission::~Transmission()
{
    tcpClient.close();
}

void Transmission::startTransfer(const char* command)
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
        bufferTimer->start(JOYSTICK_DELAY);
    }
    else
    {
        charBuffer = key.toUtf8().data()[0];
    }
}

void Transmission::sendBuffer()
{
    if (!isBufferEmpty)
    {
        char sendBuffer[10];
        qDebug() << "Joystick: " << charBuffer;
        sprintf(sendBuffer,"%c", charBuffer);
        isBufferEmpty = true;
        startTransfer(sendBuffer);
    }
}

void Transmission::stopJoystick()
{
    bufferTimer->stop();
    charBuffer = 't';
    startTransfer("t");
    isBufferEmpty = true;
}
